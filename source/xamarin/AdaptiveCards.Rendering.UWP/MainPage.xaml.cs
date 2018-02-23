using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using AdaptiveCards.Rendering.UWP;
using AdaptiveCards.Rendering.UWP.Helpers;
using AdaptiveCards.Rendering.UWP.ResourceResolvers;
using Windows.Storage;
using Windows.Data.Json;
using AdaptiveCards.Rendering.UWP.ViewModel;
using AdaptiveCards.BotConnection;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AdaptiveCards.Rendering.UWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPageViewModel m_viewModel { get; set; }
        private PayloadRetriever m_payloadRetriever = null;
        public MainPage()
        {
            this.InitializeComponent();

            m_viewModel = new MainPageViewModel();
            DataContext = m_viewModel;
            m_payloadRetriever = new PayloadRetriever();
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            string messageToSend = Input.Text;
            m_viewModel.AdaptiveCard.Payload = m_payloadRetriever.RequestAdaptiveCard(messageToSend);
        }
    }
}
