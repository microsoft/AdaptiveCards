using System.Diagnostics;
using System.Text;
using System.Windows;
using AdaptiveCards;
using Newtonsoft.Json;
using AC = AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        private AdaptiveShowCardAction _card;
        private ResourceDictionary _resources;

        public ShowCardWindow(string title, AdaptiveShowCardAction action, ResourceDictionary resources)
        {
            _resources = resources;
            _card = action;

            InitializeComponent();

            this.Title = title;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var renderer = new AdaptiveCardRenderer(new AdaptiveHostConfig())
            {
                Resources = this._resources
            };
            var result = renderer.RenderCard(_card.Card);

            if (result.FrameworkElement != null)
            {
                // Wire up click handler
                result.OnAction += OnAction;

                this.Body.Children.Add(result.FrameworkElement);
            }
        }

        private void OnAction(object sender, AdaptiveActionEventArgs e)
        {
            if (e.Action is AC.AdaptiveOpenUrlAction)
            {
                AC.AdaptiveOpenUrlAction action = (AC.AdaptiveOpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.AdaptiveShowCardAction)
            {
                MessageBox.Show("Action.ShowCard is not alloed from within a sub-card");
            }
            else if (e.Action is AC.AdaptiveSubmitAction)
            {
                AC.AdaptiveSubmitAction action = (AC.AdaptiveSubmitAction)e.Action;
                System.Windows.MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), "SubmitAction");
                this.Close();
            }
        }
    }
}