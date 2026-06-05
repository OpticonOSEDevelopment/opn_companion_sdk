namespace Csp2NetMauiDemo
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();
        }

        protected override Window CreateWindow(IActivationState? activationState)
        {
            MauiProgram.Start();

            return new Window(new AppShell());
        }
    }
}
