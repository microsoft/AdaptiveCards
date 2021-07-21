using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using System.Threading.Tasks;
using Windows.Storage;
using AdaptiveCards.Rendering.Uwp;
using System.Collections.ObjectModel;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace UWPUITestApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class CardPresenter : Page
    {
        private static CardPresenter _Instance = null;
        public static CardPresenter Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new CardPresenter();
                }

                return _Instance;
            }
        }

        private string _TestCase = "";

        public string TestCase
        {
            get
            {
                return _TestCase;
            }
            set
            {
                _TestCase = value;
                RenderAdaptiveCardAsync();
            }
        }

        public ObservableCollection<Tuple<string, string>> Inputs = new ObservableCollection<Tuple<string, string>>();

        private MainPage MainPage = null;

        private RenderedAdaptiveCard RenderedCard = null;

        private CardPresenter()
        {
            this.InitializeComponent();
        }

        internal void SetMainWindow(MainPage mainPage)
        {
            MainPage = mainPage;
        }

        internal async Task RenderAdaptiveCardAsync()
        {
            CleanRetrievedInputs();
            

            string adaptiveCardContents = await ReadTestCaseContentsAsync(TestCase);
            var renderer = new AdaptiveCardRenderer();
            AdaptiveCard card = AdaptiveCard.FromJsonString(adaptiveCardContents).AdaptiveCard;
            RenderedCard = renderer.RenderAdaptiveCard(card);

            RenderedCard.Action += RenderedCard_Action;

            GridContainer.Children.Clear();
            GridContainer.Children.Add(RenderedCard.FrameworkElement);
        }

        private void RenderedCard_Action(RenderedAdaptiveCard sender, AdaptiveActionEventArgs args)
        {
            CleanRetrievedInputs();

            if (args.Action.ActionType == ActionType.Submit)
            {
                RetrievedInputs_TextBlock.Text = sender.UserInputs.AsJson().ToString();

                /*
                foreach (var input in sender.UserInputs.AsValueSet())
                {
                    Inputs.Add(new Tuple<string,string>(input.Key, input.Value?.ToString()));
                }
                */
            }

        }

        private void CleanRetrievedInputs()
        {
            RetrievedInputs_TextBlock.Text = "";
        }

        private async Task<string> ReadTestCaseContentsAsync(string testCase)
        {
            var testcasesFolder = await Package.Current.InstalledLocation.GetFolderAsync("LinkedTestCards");
            var testCaseFile = await testcasesFolder.GetFileAsync(testCase + ".json");
            var contents = await FileIO.ReadTextAsync(testCaseFile);
            return contents;
        }
    }
}
