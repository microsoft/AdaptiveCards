// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Xamarin.Forms;
using Newtonsoft.Json.Linq;
using AdaptiveCards.Rendering;
using System.Xml.Serialization;
using AdaptiveCards.Rendering.Wpf;

using AdaptiveCards.Sample.BotClient;

namespace AdaptiveCards.XamarinForms.BotClient
{
    public partial class MainPage : ContentPage
    {
        // private DirectLineClient _client;
        // private Conversation _conversation;
        private string _watermark;

        // private Action<object, MissingInputEventArgs> _onMissingInput = (s, e) => { };
        private Action<object, ActionEventArgs> _onAction = (s, a) => { };
        private AdaptiveCards.Rendering.Wpf.AdaptiveCardRenderer _renderer;

        CardStorage CardsReader = new CardStorage();

        StackLayout _cardContainer = null;

        string[] cardFileNames = { "ActivityUpdate.json", "CalendarReminder.json", "FlightItinerary.json", "FlightUpdate.json", "FoodOrder.json",
                                       "ImageGallery.json", "InputForm.json", "Inputs.json", "Restaurant.json", "Solitaire.json", "SportingEvent.json",
                                       "StockUpdate.json", "WeatherCompact.json", "WeatherLarge.json" };

    string[] configFileNames =
        {
            "cortana-beta-dark.json", "cortana-beta-light.json", "cortana-skills.json", "microsoft-teams-dark.json", "microsoft-teams-light.json",
            "outlook-desktop.json", "render-to-image.json", "sample.json", "skype.json", "testVariantHostConfig.json",
            "webchat.json", "windows-notification.json", "windows-timeline.json"
        };

        public MainPage()
        {
            InitializeComponent();
        }

        protected override async void OnAppearing()
        {
            base.OnAppearing();

            ReadHostConfig();

            _renderer = new AdaptiveCards.Rendering.Wpf.AdaptiveCardRenderer(this.CardsReader.HostConfig);
            // _renderer = new XamlRenderer(new AdaptiveHostConfig());

            _cardContainer = this.FindByName<StackLayout>("Items");

            ReadCards();
            Send();
        }

        private void _textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //ChatAgent.Current?.CancelReadingMessages();
        }

        private void SpeechButton_Clicked(object sender, EventArgs e)
        {
        }

        private async void _itemsLayout_SizeChanged(object sender, EventArgs e)
        {
        }

        private void Button_Clicked(object sender, System.EventArgs e)
        {
            Send();
        }

        private void TextBox_Completed(object sender, System.EventArgs e)
        {
            Send();
        }

        private void Send()
        {
            
            _cardContainer.Children.Clear();
            for (int i = 0; i < cardFileNames.Count(); ++i)
            {
                AdaptiveCard adaptiveCard = CardsReader.Get(i);
                Stopwatch stopwatch = Stopwatch.StartNew();
                RenderedAdaptiveCard renderedCard = _renderer.RenderCard(adaptiveCard);
                _cardContainer.Children.Add(renderedCard.FrameworkElement);
                stopwatch.Stop();

                renderedCard.OnAction += RenderedCard_OnAction;
                renderedCard.OnMediaClicked += RenderedCard_OnMediaClicked;

                System.Diagnostics.Debug.WriteLine("Card: " + cardFileNames[i % cardFileNames.Length] + " - Time elapsed: " + stopwatch.ElapsedMilliseconds);
            }
        }

        private void RenderedCard_OnMediaClicked(RenderedAdaptiveCard sender, AdaptiveMediaEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(sender.OriginatingCard.Speak))
            {
                Xamarin.Essentials.TextToSpeech.SpeakAsync(sender.OriginatingCard.Speak);
            }
        }

        private void RenderedCard_OnAction(RenderedAdaptiveCard sender, AdaptiveActionEventArgs e)
        {
            if(e.Action is AdaptiveOpenUrlAction openUrlAction)
            {
                Xamarin.Essentials.Browser.OpenAsync(openUrlAction.Url);
            }
        }

        private async Task Send(string message)
        {
        }

        public async Task<IList<object>> GetMessages()
        {
            return null;
        }

        private void Current_VoiceInputCompleted(object sender, string e)
        {
            Message.Text = "";
            Message.IsEnabled = true;
        }

        private void Current_VoiceHypothesisGenerated(object sender, string e)
        {
            Device.BeginInvokeOnMainThread(delegate
            {
                Message.Text = e;
            });
        }

        private void Current_VoiceInputStarted(object sender, EventArgs e)
        {
            Message.IsEnabled = false;
        }

        private void ReadCards()
        {
            CardsReader.ReadAdaptiveCards(cardFileNames);
        }

        private void ReadHostConfig()
        {
            CardsReader.ReadHostConfig(configFileNames[7]);
        }
    }
}
