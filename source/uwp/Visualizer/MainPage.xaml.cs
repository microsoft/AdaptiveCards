// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using AdaptiveCards.Rendering.Uwp;
using AdaptiveCardVisualizer.ViewModel;
using System.Threading.Tasks;

using Newtonsoft.Json;
using Windows.Data.Json;
using System.Diagnostics;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AdaptiveCardVisualizer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        // public MainPageViewModel ViewModel { get; set; }

        private AdaptiveCardRenderer _renderer;


        private ScrollViewer _scrollView;
        private StackPanel _layout;
        
        private RenderedAdaptiveCard _renderedAdaptiveCard;
        private List<AdaptiveCard> _parsedAdaptiveCards = new List<AdaptiveCard>();

        public MainPage()
        {
            this.InitializeComponent();

            _scrollView = (ScrollViewer)this.FindName("ScrollViewLayout");
            _layout = (StackPanel)this.FindName("Layout");

            InitializeRenderer(new AdaptiveHostConfig());

            DoEverything();
        }

        private async Task DoEverything()
        {
            await LoadAllCardsAsync();
            RenderCards();
        }

        private async Task LoadAllCardsAsync()
        {
            StorageFolder installationFolder = await Windows.ApplicationModel.Package.Current.InstalledLocation.GetFolderAsync("Samples");
            var files = await installationFolder.GetFilesAsync();

            foreach (var file in files)
            {
                if (File.Exists(file.Path))
                {
                    string contents = File.ReadAllText(file.Path);

                    JsonObject jsonObject;
                    if (JsonObject.TryParse(contents, out jsonObject))
                    {
                        AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(jsonObject);
                        _parsedAdaptiveCards.Add(parseResult.AdaptiveCard);


                    }
                }
            }
        }

        private void RenderCards()
        {

            for (int i = 0; i < 30; ++i)
            {
                AdaptiveCard adaptiveCard = _parsedAdaptiveCards[i % _parsedAdaptiveCards.Count];

                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();
                RenderedAdaptiveCard renderedAdaptiveCard = _renderer.RenderAdaptiveCard(adaptiveCard);
                stopwatch.Stop();
                Debug.WriteLine("Elapsed " + stopwatch.ElapsedMilliseconds);

                FrameworkElement visualAdaptiveCard = renderedAdaptiveCard.FrameworkElement;
                _layout.Children.Add(visualAdaptiveCard);
            }
        }
        
        public string SerializeActionEventArgsToString(AdaptiveActionEventArgs args)
        {
            string answer = "Action invoked!";

            answer += "\nType: " + args.Action.ActionType;

            if (args.Action is AdaptiveSubmitAction)
            {
                answer += "\nData: " + (args.Action as AdaptiveSubmitAction).DataJson?.Stringify();
            }
            else if (args.Action is AdaptiveOpenUrlAction)
            {
                answer += "\nUrl: " + (args.Action as AdaptiveOpenUrlAction).Url;
            }

            answer += "\nInputs: " + args.Inputs.AsJson().Stringify();

            return answer;
        }

        public void InitializeRenderer(AdaptiveHostConfig hostConfig)
        {
            _renderer = new AdaptiveCardRenderer();
            if (hostConfig != null)
            {
                _renderer.HostConfig = hostConfig;
            }
            
            if (Settings.UseFixedDimensions)
            {
                _renderer.SetFixedDimensions(320, 180);
            }

        }
    }
}
