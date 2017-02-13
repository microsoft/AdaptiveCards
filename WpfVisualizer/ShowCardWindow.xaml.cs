using System.Diagnostics;
using System.Windows;
using Adaptive.Renderers;
using Adaptive.Schema.Net;
using Newtonsoft.Json;
using AC = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        private AdaptiveCard _card;
        private AdaptiveXamlRenderer _renderer;
        private ResourceDictionary _resources; 

        public ShowCardWindow(AdaptiveCard card, ResourceDictionary resources)
        {
            _resources = resources;
            _card = card;

            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _renderer = new AdaptiveXamlRenderer(_resources);
            _renderer.OnAction += OnAction;
            this.Body.Children.Add(_renderer.Render(_card));
        }

        private void OnAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.OpenUrlAction)
            {
                AC.OpenUrlAction action = (AC.OpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ShowCardAction)
            {
                AC.ShowCardAction action = (AC.ShowCardAction)e.Action;
                ShowCardWindow dialog = new ShowCardWindow(action.Card, this.Resources);
                dialog.ShowDialog();
            }
            else if (e.Action is AC.SubmitAction)
            {
                AC.SubmitAction action = (AC.SubmitAction)e.Action;
                System.Windows.MessageBox.Show(JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), action.Title);
                this.Close();
            }
            else if (e.Action is AC.CancelAction)
            {
                this.Close();
            }
            else if (e.Action is AC.HttpAction)
            {
                AC.HttpAction action = (AC.HttpAction)e.Action;
            }
        }
    }
}
