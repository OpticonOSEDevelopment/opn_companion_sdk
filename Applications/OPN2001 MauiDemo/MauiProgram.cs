using Microsoft.Extensions.Logging;
using Opticon.Csp2Net;

namespace Csp2NetMauiDemo
{
    public static class MauiProgram
    {
        public static MauiApp CreateMauiApp()
        {
            var builder = MauiApp.CreateBuilder();
            builder
                .UseMauiApp<App>()
                .ConfigureFonts(fonts =>
                {
                    fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                    fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                });
#if DEBUG
            builder.Logging.AddDebug();
#endif
            return builder.Build();
        }

        public static void Start()
        {
            MainPage.Instance?.AppendLog($"Csp2 DLL Version = {OpnEnvironment.GetDllVersion()}");

            string logDirectory = Path.Combine(AppContext.BaseDirectory, "Logs");
            Directory.CreateDirectory(logDirectory);

            OpnDevice.StartPolling((device, connected) =>                    {
                try
                {
                    if (connected)
                    {
	                    // device.Connect();		// Not mandatory (port is automatically opened on each request if needed)
	                    // device.Interrogate();	// No longer needed (Interrogate is automatically called when requesting device info)
	
	                    string deviceId = device.GetDeviceId() ?? "Unknown";
	                    string model = device.GetModel() ?? "Unknown";
                            
                        // Handle new connection
                        MainPage.Instance?.AppendLog($"[{model}] [{deviceId}] [{device.PortName}] Connected ({device.GetSoftwareVersion()})");

                        // Read all barcodes from the device AND correct time stamps based on device and system time
                        var barcodes = device.ReadBarcodes(true);

                        MainPage.Instance?.AppendLog($"[{device.GetModel()}] [{deviceId}] [{device.PortName}] {barcodes.Count} Barcode(s) Read");
						string logFile = Path.Combine(logDirectory, $"Barcodes_{deviceId}.txt");

						foreach (var barcode in barcodes)
                        {
                            DateTime ts = barcode.Timestamp;

                            string line = $"{barcode.Data};{ts:HH:mm:ss};{ts:dd-MM-yyyy};{barcode.SymbologyName};{deviceId}";

                            File.AppendAllText(logFile, line + Environment.NewLine);

                            MainPage.Instance?.AppendLog($"[{device.GetModel()}] [{deviceId}] [{device.PortName}] [{barcode.Timestamp}] [{barcode.Data}] [{barcode.SymbologyName}]");
                        }

                        device.ClearBarcodes();
                            
                        // Sync device time AFTER reading barcodes to be able to correct time stamps based on the computer and device time
	                    // Calling device.ReadBarcodes(true) already syncs the time
	                    //device.TryGetTime(out DateTime dTime);
	                    //device.SetTime(DateTime.Now);    
	
	                    // Demonstrates the reading and writing of all parameter types (bool, int, enum and string/byte array)
	                    //device.GetParameter(OpnParameter.Code39, out bool enabled);
	                    //device.GetParameter(OpnParameter.ScannerOnTime, out int time);
	                    //device.GetParameter(OpnParameter.DeleteEnable, out DeleteEnableOptions deleteOptions);
	                    //device.SetParameter(OpnParameter.Code39, true);
	                    //device.SetParameter(OpnParameter.ScannerOnTime, 20);
	                    //device.SetParameter(OpnParameter.Gs1DataBar, Gs1DataBarOptions.Gs1DataBar | Gs1DataBarOptions.Gs1Expanded);
	                    //device.SetParameter(OpnParameter.ScratchPad, "Hello");

                        // Don't disconnect if you want callbacks for detecting new barcodes while connected (only works on Windows and using the USB-VCP driver)
						//device.Disconnect();
                    }
                    else
                    {  	// Handle removal / disconnect
                        if(device.GetDeviceId() != null)
                            MainPage.Instance?.AppendLog($"[{device.GetModel()}] [{device.GetDeviceId()}] [{device.PortName}] Disconnected");
                        else
                            MainPage.Instance?.AppendLog($"[{device.PortName}] Removed");
                    }

                    return 1; // Return 1 to indicate the device was successfully processed
                }
                catch (Exception ex)
                {
                    MainPage.Instance?.AppendLog($"Exception occurred ({device.PortName}): {ex.Message}");
                    return 0; // Return 0 to continue polling, so we can retry later
                }
            });
        }
    }
}
