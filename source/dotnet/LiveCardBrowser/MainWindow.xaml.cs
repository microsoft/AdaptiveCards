using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using LiveCardClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LiveCardBrowser
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static AdaptiveCardRenderer renderer;

        public MainWindow()
        {
            InitializeComponent();
            renderer = new AdaptiveCardRenderer()
            {
                Resources = Resources
            };
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            ((MainWindow)sender).DataContext = new AppViewModel();
        }

        private async void AddButton_Click(object sender, RoutedEventArgs e)
        {
            AppViewModel appViewModel = (AppViewModel)this.DataContext;
            if (!String.IsNullOrWhiteSpace(this.TextBoxUrl.Text))
            {
                var url = new Uri(this.TextBoxUrl.Text.Trim());
                LiveCard liveCard = new LiveCard(url);
                liveCard.OnCardChanged += LiveCard_OnCardChanged;
                liveCard.OnElementChanged += LiveCard_OnElementChanged;

                // load deactivated card
                await liveCard.LoadCard();

                lock (liveCard.Card)
                {
                    RenderedAdaptiveCard renderedCard = renderer.RenderCard(liveCard.Card);

                    var liveCardViewModel = new LiveCardViewModel()
                    {
                        Url = url.ToString(),
                        LiveCard = liveCard,
                        CardContent = renderedCard.FrameworkElement
                    };

                    appViewModel.Cards.Add(liveCardViewModel);
                    appViewModel.SelectedCard = liveCardViewModel;

                    this.TextBoxUrl.Text = null;
                }
            }
        }

        private void LiveCard_OnCardChanged(object sender, CardChangedArgs e)
        {
            this.Dispatcher.InvokeAsync(() =>
            {
                AppViewModel appViewModel = (AppViewModel)this.DataContext;
                lock (appViewModel.SelectedCard.LiveCard.Card)
                {
                    appViewModel.SelectedCard.CardContent = renderer.RenderCard(appViewModel.SelectedCard.LiveCard.Card).FrameworkElement;
                }
            });
        }

        private void LiveCard_OnElementChanged(object sender, ElementChangedArgs e)
        {
            this.Dispatcher.Invoke(() =>
            {
                AppViewModel appViewModel = (AppViewModel)this.DataContext;
                lock (appViewModel.SelectedCard.LiveCard.Card)
                {
                    appViewModel.SelectedCard.CardContent = renderer.RenderCard(appViewModel.SelectedCard.LiveCard.Card).FrameworkElement;
                }
            });
        }

        private async void ActivateButton_Click(object sender, RoutedEventArgs e)
        {
            AppViewModel appViewModel = (AppViewModel)this.DataContext;
            if (appViewModel.SelectedCard != null)
            {
                await appViewModel.SelectedCard.LiveCard.StartListening();
                await appViewModel.SelectedCard.LiveCard.Activate();
            }
        }

    }
}
