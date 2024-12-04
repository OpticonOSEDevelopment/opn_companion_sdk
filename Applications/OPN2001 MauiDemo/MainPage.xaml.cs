namespace Csp2MauiDemo
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private bool started = false;
        private void OnCounterClicked(object sender, EventArgs e)
        {
            if (!started)
            {
                CounterBtn.Text = $"Started!"; 
                started = true;
                MauiProgram.Start();
            }
            else
            {
                CounterBtn.Text = $"Not started";
                started = false;
                MauiProgram.Stop();
            }

            SemanticScreenReader.Announce(CounterBtn.Text);

            
        }
    }

}
