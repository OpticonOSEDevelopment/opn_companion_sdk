using Microsoft.Extensions.Logging;
using System.Diagnostics;
using System.Text;

namespace Csp2MauiDemo
{
    public class ParamInfo
    {
        public ParamInfo(String Par, int Num)
        {
            _Parameter = Par;
            _ParamNumber = Num;
            _ParamValue = -1;

        }
        private String _Parameter;
        public String Parameter
        {
            get { return _Parameter; }
            set { _Parameter = value; }
        }

        private int _ParamNumber;
        public int ParamNumber
        {
            get { return _ParamNumber; }
            set { _ParamNumber = value; }
        }

        private int _ParamValue;
        public int ParamValue
        {
            get { return _ParamValue; }
            set { _ParamValue = value; }
        }
    }

    public static class MauiProgram
    {
        public delegate void Action();

        public static ParamInfo[] Description = {
            new ParamInfo( "Code 39", 0x1f ),
            new ParamInfo( "UPC", 0x09 ),
            new ParamInfo( "Code128",  0x08),
            new ParamInfo( "Code 39 Full ASCII", 0x36 ),
            new ParamInfo( "UPC Supps", 0x35 ),
            new ParamInfo( "Convert  UPC E to A", 0x29 ),
            new ParamInfo( "Convert EAN8 to EAN13",     0x2a ),
            new ParamInfo( "Convert EAN8 to EAN13 Type", 0x37 ),
            new ParamInfo( "Send UPC A Check Digit",    0x2b ),
            new ParamInfo( "Send UPC E Check Digit", 0x2c ),
            new ParamInfo( "Code 39 Check Digit", 0x2e ),
            new ParamInfo( "Xmit Code 39 Check Digit", 0x2d ),
            new ParamInfo( "UPCE_ Preamble", 0x25 ),
            new ParamInfo( "UPCA_ Preamble", 0x24 ),
            new ParamInfo( "EAN 128", 0x34 ),
            new ParamInfo( "Coupon Code", 0x38),
            new ParamInfo( "I 2of5", 0x3A ),
            new ParamInfo( "I 2of5 Check Digit", 0x41 ),
            new ParamInfo( "Xmit I 2of5 Check Digit", 0x40 ),
            new ParamInfo( "Convert ITF14 to EAN 13", 0x3F ),
            new ParamInfo( "I 2of5 Length 1",0x3B ),
            new ParamInfo( "I 2of5 Length 2",0x3C ),
            new ParamInfo( "D 2of5", 0x39 ),
            new ParamInfo( "D 2of5  Length 1" ,0x3D ),
            new ParamInfo( "D 2of5  Length 2", 0x3E ),
            new ParamInfo( "Upcean Security Level", 0x2f ),
            new ParamInfo( "UPC/EAN Supplemental Redundancy", 0x30 ),
            new ParamInfo( "Scanner On-Time",0x11 ),
            new ParamInfo( "Comm Awake Time", 0x20 ),
            new ParamInfo( "Baud Rate ",0x0d ),
            new ParamInfo( "Baud Switch Delay", 0x1d),
            new ParamInfo( "Reset Baud Rates", 0x1c ),
            new ParamInfo( "Reject Redundant Barcode", 0x04 ),
            new ParamInfo( "Host Connect Beep ", 0x0a ),
            new ParamInfo( "Host Complete Beep", 0x0b ),
            new ParamInfo( "Low-Battery Indication", 0x07),
            new ParamInfo( "Auto_Clear", 0x0f),
            new ParamInfo( "Delete_Enable",0x21),
            new ParamInfo( "Data Protection", 0x31 ),
            new ParamInfo( "Memory Full Indication", 0x32 ),
            new ParamInfo( "Memory Low Indication", 0x33 ),
            new ParamInfo( "Max Barcode Len", 0x22 ),
            new ParamInfo( "Good Decode LED On Time", 0x1e ),
            new ParamInfo( "Store_RTC ", 0x23 ),
            new ParamInfo( "ASCII mode", 0x4f ),
            new ParamInfo( "Buzzer Volume",0x02 ),
            new ParamInfo( "Buzzer On",0x57 ),
            new ParamInfo( "Buzzer Toggle", 0x55 ),
            new ParamInfo( "Buzzer Auto On", 0x56 ),
            new ParamInfo( "RSS", 0x14 ),
            new ParamInfo( "Scratch Pad", 0x26 ),
        };


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

        public static int ReadBarcodes = 0;
        public static List<Int32> Ports = new List<Int32>();

        static void CallbackFunction(Int32 nComport)
        {
            int iRet = -1;

            if (Opticon.csp2.DataAvailable(nComport) > 0)
            {
                iRet = Opticon.csp2.ReadData(nComport);
            }
            else if (Opticon.csp2.GetDSR(nComport) > 0)     // Is Connected?
            {
                iRet = Opticon.csp2.Interrogate(nComport);
            }

            if (iRet >= 0)
            {
                if (Ports.Contains(nComport) == false)
                    Ports.Add(nComport);
            }
            else
            {
                if (Ports.Contains(nComport) == true)
                    Ports.Remove(nComport);
            }

            /*BeginInvoke((Action)delegate ()
            {
                labelConnected.Text = "Connected: " + Ports.Count;
            });*/

            if (iRet >= 0L)
            {
                Trace.WriteLine("OPN-2001 Connected at " + nComport);

                Int32 iCount = iRet;
                Trace.WriteLine(String.Format("Number of barcodes = {0}", iCount));

                ReadBarcodes += iCount;

                /*BeginInvoke((Action)delegate ()
                {
                    labelBarcodes.Text = "Barcodes: " + ReadBarcodes;
                });*/

                String szDeviceId;
                iRet = Opticon.csp2.GetDeviceId(out szDeviceId, nComport);
                Trace.WriteLine(String.Format("Device Id: {0}", szDeviceId));

                Trace.WriteLine(String.Format("Protocol: {0}", Opticon.csp2.GetProtocol(nComport)));

                Trace.WriteLine(String.Format("SystemStatus: {0}", Opticon.csp2.GetSystemStatus(nComport)));

                StringBuilder szSoftwareVersion = new StringBuilder(256);
                Opticon.csp2.GetSwVersion(szSoftwareVersion, 256, nComport);

                Trace.WriteLine(String.Format("Software version: {0}", szSoftwareVersion));

                if (iCount > 0)
                {
                    Trace.WriteLine("Barcodes");

                    StringBuilder sbBarcodes = new StringBuilder(1000);

                    for (Int32 i = 0; i < iCount; i++)
                    {
                        Opticon.csp2.BarCodeDataPacket aPacket;
                        iRet = Opticon.csp2.GetPacket(out aPacket, i, nComport);
                        sbBarcodes.AppendLine(String.Format("{0}, {1}, {2}, {3}", i + 1, aPacket.strBarData, aPacket.dtTimestamp, aPacket.strId));
                    }
                    Trace.WriteLine(sbBarcodes);

                    if (Opticon.csp2.ClearData(nComport) != 0)
                    {
                        Trace.WriteLine("Erasing Failed!");
                    }
                }

                /* Trace.WriteLine("csp2.GetParameter()");

                Byte[] value = new Byte[32];
                foreach (ParamInfo p in Description)
                {
                    iRet = Opticon.csp2.GetParam(p.ParamNumber, value, value.Length, nComport);
                    if (iRet == 0)
                        Trace.WriteLine(String.Format(" Param {0:X02}, {1} = {2}", p.ParamNumber, p.Parameter, value[0]));
                    else
                        Trace.WriteLine(String.Format(" Param {0:X02}, {1} Failed!", p.ParamNumber, p.Parameter));
                }*/

                DateTime T;

                iRet = Opticon.csp2.GetTime(out T, nComport);
                if (iRet == 0)
                {
                    Trace.WriteLine(String.Format("Current Time: {0}", T.ToString()));
                }
                else
                {
                    Trace.WriteLine(" Fail!");
                }

                iRet = Opticon.csp2.SetTime(DateTime.Now, nComport);

                if (iRet == 0)
                {
                    Trace.WriteLine(String.Format("Set time to {0}", T));
                }
                else
                {
                    Trace.WriteLine(" Fail!");
                }
            }
            else
            {
                Trace.WriteLine("OPN-2001 Disconnected from " + nComport);
            }
        }

        public static bool Started = false;

        public static Opticon.csp2.csp2CallBackFunctionAll Csp2Callback = new Opticon.csp2.csp2CallBackFunctionAll(CallbackFunction);   // Make global to avoid garbage collector from disgarding the call-back

        public static void Start()
        {
            if (!Started)
            {
                Int32 iRet;

                Trace.WriteLine("csp2.SetDebugMode(...)");
                iRet = Opticon.csp2.SetDebugMode(1);
                if (iRet != 0)
                {
                    Trace.WriteLine(" Fail!");
                }

                Trace.WriteLine("csp2.GetDLLVersion(...)");

                StringBuilder szDLLVersion = new StringBuilder(256);
                iRet = Opticon.csp2.GetDllVersion(szDLLVersion, 100);
                if (iRet < 0)
                {
                    Trace.WriteLine(String.Format(" Fail! {0} ", iRet));
                }
                else
                {
                    Trace.WriteLine(String.Format("DLL Version = {0}", szDLLVersion));
                }

                Int32[] ports = new Int32[100];

                int Count = Opticon.csp2.GetOpnCompatiblePorts(ports);

                Trace.WriteLine("csp2.StartPollingAll()");

                iRet = Opticon.csp2.StartPollingAll(Csp2Callback);

                if (iRet != 0)
                {
                    Trace.WriteLine(String.Format(" Fail! {0} ", iRet));
                    return;
                }

                Started = true;
            }
            else
            {
                Opticon.csp2.EnablePolling();
            }
        }

        public static void Stop()
        {
            Opticon.csp2.DisablePolling();
        }
    }
           
}
