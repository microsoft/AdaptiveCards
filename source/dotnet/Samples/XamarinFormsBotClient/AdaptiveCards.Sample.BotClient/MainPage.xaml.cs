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
using AdaptiveCards.Rendering.Config;
using System.Xml.Serialization;

namespace AdaptiveCards.XamarinForms.BotClient
{
    public partial class MainPage : ContentPage
    {
        // private DirectLineClient _client;
        // private Conversation _conversation;
        private string _watermark;

        private Action<object, MissingInputEventArgs> _onMissingInput = (s, e) => { };
        private Action<object, ActionEventArgs> _onAction = (s, a) => { };
        private XamlRenderer _renderer;
        AdaptiveCard _card;

        StackLayout _cardContainer = null;

        public MainPage()
        {
            InitializeComponent();
        }



        protected override async void OnAppearing()
        {
            base.OnAppearing();

            _card = new AdaptiveCard
            {
                Body = new List<CardElement> { 
                    new TextBlock
                    {
                        Text = "This is a textblock",
                    },
                    new TextBlock
                    {
                        Text = "This textblock is subtle",
                        Separation = SeparationStyle.Strong,
                        IsSubtle = true
                    }
                }
            };

            _card = new AdaptiveCard
            {
                Body = new List<CardElement>
                {
                    new TextBlock
                    {
                        Text = "Publish Adaptive Card schema",
                        Weight = TextWeight.Bolder,
                        Size = TextSize.Medium
                    },
                    new ColumnSet
                    {
                        Columns = new List<Column>
                        {
                            new Column
                            {
                                Items = new List<CardElement>
                                {
                                    new Image
                                    {
                                        Url = "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
                                        Size = ImageSize.Small,
                                        Style = ImageStyle.Person
                                    }
                                }
                            },
                            new Column
                            {
                                Items = new List<CardElement>
                                {
                                    new TextBlock
                                    {
                                        Text = "Matt Hidinger",
                                        Weight = TextWeight.Bolder,
                                        Wrap = true
                                    },
                                    new TextBlock
                                    {
                                        Text = "Created <a random date>",
                                        IsSubtle = true,
                                        Wrap = true
                                    }
                                }
                            }
                        }
                    },
                    new TextBlock
                    {
                        Text = "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
                        Wrap = true
                    },
                    new FactSet
                    {
                        Facts = new List<Fact>
                        {
                            new Fact
                            {
                                Title = "Board: ",
                                Value = "Adaptive Card"
                            },
                            new Fact
                            {
                                Title = "List: ",
                                Value = "Backlog"
                            },
                            new Fact
                            {
                                Title = "Assigned to: ",
                                Value = "Matt Hidinger"
                            },
                            new Fact
                            {
                                Title = "Due date: ",
                                Value = "Not set"
                            }
                        }
                    }
                },
                Actions = new List<ActionBase>
                {
                    new ShowCardAction
                    {
                        Title = "Set due date",
                        Card = new AdaptiveCard
                        {
                            Body = new List<CardElement>
                            {
                                new DateInput
                                {
                                    Id = "dueDate"
                                }
                            },
                            Actions = new List<ActionBase>
                            {
                                new SubmitAction
                                {
                                    Title = "Ok!"
                                }
                            }
                        }
                    }, 
                    new ShowCardAction
                    {
                        Title = "Comment",
                        Card = new AdaptiveCard
                        {
                            Body = new List<CardElement>
                            {
                                new TextInput
                                {
                                    Id = "comment",
                                    IsMultiline = true,
                                    Placeholder = "Enter your comment"
                                }
                            },
                            Actions = new List<ActionBase>
                            {
                                new SubmitAction
                                {
                                    Title = "Ok!"
                                }
                            }
                        }
                    }
                }
            };

            _renderer = new XamlRenderer(new HostConfig(), Application.Current.Resources, _onAction, _onMissingInput);
            _renderer = new AdaptiveCardRenderer(new HostConfig());

            _cardContainer = this.FindByName<StackLayout>("Items");
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
            View v = _renderer.RenderAdaptiveCard(_card, null, new HostConfig());
            _cardContainer.Children.Add(v);
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
    }
}
