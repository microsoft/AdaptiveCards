// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Windows.ApplicationModel;
using Windows.UI.Xaml.Controls;

using System.Threading.Tasks;
using Windows.Storage;
using AdaptiveCards.Rendering.Uwp;
using System.Collections.ObjectModel;
using AdaptiveCards.ObjectModel.Uwp;

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
