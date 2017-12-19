using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardClient
{
    public class EventBinder : AdaptiveVisitor
    {
        private ILiveCardServerAPI server;

        public EventBinder(ILiveCardServerAPI server)
        {
            this.server = server;
        }

        public static void Bind(ILiveCardServerAPI server, AdaptiveCard card)
        {
            new EventBinder(server).Visit(card);
        }

        public static void Bind(ILiveCardServerAPI server, AdaptiveElement element)
        {
            new EventBinder(server).Visit(null, element);
        }

        public override void Visit(AdaptiveTypedElement parent, AdaptiveElement adaptiveElement)
        {
            bind(adaptiveElement);
            base.Visit(parent, adaptiveElement);
        }

        private void bind(AdaptiveElement element)
        {
            if (element.Events != null)
            {
                foreach (var eventName in element.Events)
                {
                    switch (eventName)
                    {
                        case "OnClick":
                            element.OnClick += Element_OnClick;
                            break;
                        case "OnDoubleClick":
                            element.OnDoubleClick += Element_OnDoubleClick;
                            break;
                        case "OnMouseEnter":
                            element.OnMouseEnter += Element_OnMouseEnter;
                            break;
                        case "OnMouseLeave":
                            element.OnMouseLeave += Element_OnMouseLeave;
                            break;
                        default:
                            if (element is AdaptiveInput)
                            {
                                AdaptiveInput input = element as AdaptiveInput;
                                switch (eventName)
                                {
                                    case "OnKey":
                                        input.OnKey += Input_OnKey;
                                        break;
                                    case "OnTextchanged":
                                        input.OnTextChanged += Input_OnTextChanged;
                                        break;
                                    case "OnSelectionChanged":
                                        input.OnSelectionChanged += Input_OnSelectionChanged;
                                        break;
                                    case "OnFocus":
                                        input.OnFocus += Input_OnFocus;
                                        break;
                                    case "OnBlur":
                                        input.OnBlur += Input_OnBlur;
                                        break;
                                }
                            }
                            break;
                    }
                }
            }
        }

        private async void Input_OnBlur(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnBlur(element.Id);
        }

        private async void Input_OnFocus(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnFocus(element.Id);
        }

        private async void Input_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnSelectionChanged(element.Id, e.Selection);
        }

        private async void Input_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnTextChanged(element.Id, e.Text);
        }

        private async void Input_OnKey(object sender, KeyEventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnKey(element.Id, e.Key);
        }

        private async void Element_OnMouseLeave(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnMouseLeave(element.Id);
        }

        private async void Element_OnMouseEnter(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnMouseEnter(element.Id);
        }

        private async void Element_OnDoubleClick(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnDoubleClick(element.Id);
        }

        private async void Element_OnClick(object sender, EventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            await this.server.OnClick(element.Id);
        }

    }
}
