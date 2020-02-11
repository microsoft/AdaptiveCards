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

        public MainPage()
        {
            InitializeComponent();
        }

        protected override async void OnAppearing()
        {
            base.OnAppearing();

            /*
            _card = new AdaptiveCard("1.0")
            {
                Body = new List<AdaptiveElement> {
                    new AdaptiveTextBlock
                    {
                        Text = "This is a textblock",
                    },
                    new AdaptiveTextBlock
                    {
                        Text = "This textblock is subtle",
                        Spacing = AdaptiveSpacing.Default,
                        Separator = true,
                        IsSubtle = true
                    }
                }
            };

            _card = new AdaptiveCard("1.0")
            {
                Body = new List<AdaptiveElement>
                {
                    new AdaptiveTextBlock
                    {
                        Text = "Publish Adaptive Card schema",
                        Weight = AdaptiveTextWeight.Bolder,
                        Size = AdaptiveTextSize.Medium
                    },
                    new AdaptiveColumnSet
                    {
                        Columns = new List<AdaptiveColumn>
                        {
                            new AdaptiveColumn
                            {
                                Items = new List<AdaptiveElement>
                                {
                                    new AdaptiveImage
                                    {
                                        Url = new Uri("https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"),
                                        Size = AdaptiveImageSize.Small,
                                        Style = AdaptiveImageStyle.Person
                                    }
                                }
                            },
                            new AdaptiveColumn
                            {
                                Items = new List<AdaptiveElement>
                                {
                                    new AdaptiveTextBlock
                                    {
                                        Text = "Matt Hidinger",
                                        Weight = AdaptiveTextWeight.Bolder,
                                        Wrap = true
                                    },
                                    new AdaptiveTextBlock
                                    {
                                        Text = "Created <a random date>",
                                        IsSubtle = true,
                                        Wrap = true
                                    }
                                }
                            }
                        }
                    },
                    new AdaptiveTextBlock
                    {
                        Text = "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
                        Wrap = true
                    },
                    new AdaptiveFactSet
                    {
                        Facts = new List<AdaptiveFact>
                        {
                            new AdaptiveFact
                            {
                                Title = "Board: ",
                                Value = "Adaptive Card"
                            },
                            new AdaptiveFact
                            {
                                Title = "List: ",
                                Value = "Backlog"
                            },
                            new AdaptiveFact
                            {
                                Title = "Assigned to: ",
                                Value = "Matt Hidinger"
                            },
                            new AdaptiveFact
                            {
                                Title = "Due date: ",
                                Value = "Not set"
                            }
                        }
                    }
                },
                Actions = new List<AdaptiveAction>
                {
                    new AdaptiveShowCardAction
                    {
                        Title = "Set due date",
                        Card = new AdaptiveCard("1.0")
                        {
                            Body = new List<AdaptiveElement>
                            {
                                new AdaptiveDateInput
                                {
                                    Id = "dueDate"
                                }
                            },
                            Actions = new List<AdaptiveAction>
                            {
                                new AdaptiveSubmitAction
                                {
                                    Title = "Ok!"
                                }
                            }
                        }
                    }, 
                    new AdaptiveShowCardAction
                    {
                        Title = "Comment",
                        Card = new AdaptiveCard("1.0")
                        {
                            Body = new List<AdaptiveElement>
                            {
                                new AdaptiveTextInput
                                {
                                    Id = "comment",
                                    IsMultiline = true,
                                    Placeholder = "Enter your comment"
                                }
                            },
                            Actions = new List<AdaptiveAction>
                            {
                                new AdaptiveSubmitAction
                                {
                                    Title = "Ok!"
                                }
                            }
                        }
                    }
                }
            };
            */
            _renderer = new AdaptiveCards.Rendering.Wpf.AdaptiveCardRenderer(new AdaptiveHostConfig());
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
            for (int i = 0; i < 30; ++i)
            {
                AdaptiveCard adaptiveCard = CardsReader.Get(i);
                Stopwatch stopwatch = Stopwatch.StartNew();
                RenderedAdaptiveCard renderedCard = _renderer.RenderCard(adaptiveCard);
                _cardContainer.Children.Add(renderedCard.FrameworkElement);
                stopwatch.Stop();
                System.Diagnostics.Debug.WriteLine(stopwatch.ElapsedMilliseconds);
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
            String[] cardFileNames = { "ActivityUpdate.json", "CalendarReminder.json", "FlightItinerary.json", "FlightUpdate.json", "FoodOrder.json",
                                       "ImageGallery.json", "InputForm.json", "Inputs.json", "Restaurant.json", "Solitaire.json", "SportingEvent.json",
                                       "StockUpdate.json", "WeatherCompact.json", "WeatherLarge.json" };

            CardsReader.ReadAdaptiveCards(cardFileNames);
        }
    }
}
