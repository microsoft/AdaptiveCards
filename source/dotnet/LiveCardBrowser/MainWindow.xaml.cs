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

        public MainWindow()
        {
            InitializeComponent();
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

                // load deactivated card
                await liveCard.LoadCard();

                lock (liveCard.Card)
                {
                    var liveCardViewModel = new LiveCardViewModel(this.Dispatcher, this.Resources)
                    {
                        Url = url.ToString(),
                        LiveCard = liveCard
                    };

                    appViewModel.Cards.Add(liveCardViewModel);
                    appViewModel.SelectedCard = liveCardViewModel;

                    this.TextBoxUrl.Text = null;
                }
            }
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

        private void DectivateButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
