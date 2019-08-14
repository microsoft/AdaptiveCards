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
using Microsoft.Bot.Connector.DirectLine;
using Newtonsoft.Json.Linq;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;

namespace AdaptiveCards.XamarinForms.BotClient
{
    public partial class MainPage : ContentPage
    {
        private DirectLineClient _client;
        private Conversation _conversation;
        private string _watermark;

        private Action<object, MissingInputEventArgs> _onMissingInput = (s, e) => { };
        private Action<object, ActionEventArgs> _onAction = (s, a) => { };
        private AdaptiveCardRenderer _renderer;

        public MainPage()
        {
            InitializeComponent();
        }



        protected override async void OnAppearing()
        {
            base.OnAppearing();

            var baseUri = new Uri("https://directline.scratch.botframework.com");
            var secret = "b9RlKakMKPk.cwA.HLc.m6lzEenENtMMk2TD_Lh4iGzK3VlP6x_NsRaA-KLhHkk";
            _client = new DirectLineClient(baseUri, new DirectLineClientCredentials(secret));

            _conversation = await _client.Conversations.StartConversationAsync().ConfigureAwait(false);

            _renderer = new AdaptiveCardRenderer(new HostConfig());

            // AdaptiveTestBot
            // d5600769-0c92-4ab3-99f4-61380589a887
            // pass GWGDf3PnKzxLMvi3uo9uNLy


            // dl key b9RlKakMKPk.cwA.HLc.m6lzEenENtMMk2TD_Lh4iGzK3VlP6x_NsRaA-KLhHkk
            // dl b9RlKakMKPk.cwA.dzE.-n6M3jIwaakiWGtA6XX7-m5zn74m3yUzU5k5ANs8WGg
        }

        private void _textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //ChatAgent.Current?.CancelReadingMessages();
        }

        private void SpeechButton_Clicked(object sender, EventArgs e)
        {
            //if (VoiceInputExtension.Current != null)
            //{
            //    if (ChatAgent.Current.IsTakingVoiceInput)
            //    {
            //        ChatAgent.Current.StopVoiceInput();
            //    }
            //    else
            //    {
            //        ChatAgent.Current.StartVoiceInput();
            //    }
            //}
        }

        private async void _itemsLayout_SizeChanged(object sender, EventArgs e)
        {
            //await Task.Delay(50);
            //await MessagesScrollView.ScrollToAsync(0, int.MaxValue, true);
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
            var text = Message.Text;
            Send(text);
        }

        private async Task Send(string message)
        {
            message = message.Replace('"', '\'');
            Message.Text = "";

            var fromProperty = new ChannelAccount("Matt");

            var activity = new Activity(text: message, fromProperty: fromProperty, type: "message");
            try
            {
                await _client.Conversations.PostActivityAsync(_conversation.ConversationId, activity);
                await Task.Delay(2000);
                await GetMessages();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                Debugger.Break();
            }

        }

        public async Task<IList<Activity>> GetMessages()
        {
            var response = await _client.Conversations
                .GetActivitiesAsync(_conversation.ConversationId, _watermark)
                .ConfigureAwait(false);

            var cardAttachments = response.Activities
                .Where(m => m.Attachments != null)
                .SelectMany(m => m.Attachments)
                .Where(m => m.ContentType == "application/vnd.microsoft.card.adaptive");

            foreach (var attachment in cardAttachments)
            {
                var jObject = (JObject)attachment.Content;
                var card = jObject.ToObject<AdaptiveCard>();

                Device.BeginInvokeOnMainThread(() =>
                {
                    var result = _renderer.RenderCard(card);

                    if (result.View != null)
                    {
                        // Wire up click handler
                        result.OnAction += (s, args) =>
                        {
                            _onAction?.Invoke(s, args);
                        };

                        var xaml = result.View;

                        xaml.WidthRequest = 350;
                        xaml.Margin = new Thickness(8);
                        xaml.BackgroundColor = Color.LightGray;

                        Items.Children.Add(xaml);
                    }
                });
            }

            _watermark = response.Watermark;
            return response.Activities;
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
    }
}
