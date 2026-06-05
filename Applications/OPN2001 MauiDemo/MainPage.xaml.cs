using Csp2NetMauiDemo;

namespace Csp2NetMauiDemo
{
    public partial class MainPage : ContentPage
    {
        public static MainPage? Instance { get; private set; }

        public MainPage()
        {
            InitializeComponent();
            Instance = this;

            MauiProgram.Start();
        }

        public void AppendLog(string text)
        {
            MainThread.BeginInvokeOnMainThread(() =>
            {
                LogEditor.Text = $"{LogEditor.Text}{text}{Environment.NewLine}";
            });
        }
    }
}
