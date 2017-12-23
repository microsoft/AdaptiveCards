using AdaptiveCards;
using System;
using System.Diagnostics;
using System.Net.Http;
using LiveCardAPI;
using LiveCardServer;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System.Threading.Tasks;
using StreamJsonRpc;
using System.Net;

namespace LiveCardServerSample.Controllers
{
    [Route("api/[controller]")]
    public class HelloWorldController : Controller
    {
        public LiveCard LiveCard { get; private set; }

        [HttpGet]
        public async Task<AdaptiveCard> Get()
        {
            var helloCard = new AdaptiveCard();
            var title = new AdaptiveTextBlock() { Id = "Title", Text = "Hello World", Size = AdaptiveTextSize.Large };
            var activatation = new AdaptiveTextBlock() { Id = "Activation", Text = $"Deactivated" };
            var hover = new AdaptiveTextBlock() { Id = "Hover", Text = $"No mouse" };
            helloCard.Body.Add(title);
            helloCard.Body.Add(activatation);
            helloCard.Body.Add(hover);

            // hook up code behind
            helloCard.OnCardActivate += OnCardActivated;
            helloCard.OnCardDeactivate += OnCardDeactivated;

            title.OnClick += Title_OnClick;
            title.OnMouseEnter += Title_OnMouseEnter;
            title.OnMouseLeave += Title_OnMouseLeave;
            title.OnDoubleClick += Title_OnDoubleClick;

            // update events collection, ust be smarter way to do this
            new SetEventsVisitor().VisitCard(helloCard);

            // start with deactivated card, but if client hooks up WebSocket then it becomes activated live card
            if (this.HttpContext.WebSockets.IsWebSocketRequest)
            {
                // Response.StatusCode = (int)HttpStatusCode.SwitchingProtocols;
                var webSocket = await HttpContext.WebSockets.AcceptWebSocketAsync("json-rpc");

                // initialize livecard on RPC channel
                this.LiveCard = new LiveCard(helloCard, webSocket);

                // start listening
                await this.LiveCard.StartListening();

                // wait as long as client keeps connection open
                await this.LiveCard.ListeningTask;
            }
            return helloCard;
        }

        private async void Input_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            var input = (AdaptiveTextInput)sender;
            Trace.WriteLine($"{input.Id} OnTextChanged");
            if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("TextLabel", out AdaptiveTextBlock label))
            {
                label.Text = e.Text;
                await this.LiveCard.ReplaceElement(label);
            }
        }

        private async void Input_OnBlur(object sender, EventArgs e)
        {
            var input = (AdaptiveElement)sender;
            Trace.WriteLine($"{input.Id} OnBlur");
            if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("FocusLable", out AdaptiveTextBlock label))
            {
                label.Text = "input does not have focus";
                await this.LiveCard.ReplaceElement(label);

            }
        }

        private async void Input_OnFocus(object sender, EventArgs e)
        {
            var element = (AdaptiveInput)sender;
            Trace.WriteLine($"{element.Id} OnFocus");
            if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("FocusLable", out AdaptiveTextBlock label))
            {
                label.Text = "Input has focus";
                await this.LiveCard.ReplaceElement(label);
            }
        }

        private async void Title_OnMouseLeave(object sender, EventArgs e)
        {
            AdaptiveTextBlock hover = (AdaptiveTextBlock)sender;
            Trace.WriteLine($"{hover.Id} MouseLeave");
            hover.Text = "No mouse";
            await this.LiveCard.ReplaceElement(hover);
        }

        private async void Title_OnMouseEnter(object sender, EventArgs e)
        {
            AdaptiveTextBlock hover = (AdaptiveTextBlock)sender;
            Trace.WriteLine($"{hover.Id} MouseEnter");
            hover.Text = "Mouse Mouse Mouse";
            await this.LiveCard.ReplaceElement(hover);
        }

        private async void Title_OnClick(object sender, EventArgs e)
        {
            AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
            Trace.WriteLine($"{title.Id} Click");
            if (title.Weight == AdaptiveTextWeight.Default)
                title.Weight = AdaptiveTextWeight.Bolder;
            else
                title.Weight = AdaptiveTextWeight.Default;
            await this.LiveCard.ReplaceElement(title);
        }

        private async void Title_OnDoubleClick(object sender, EventArgs e)
        {
            AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
            Trace.WriteLine($"{title.Id} Double Click");
            if (title.Color == AdaptiveTextColor.Attention)
                title.Color = AdaptiveTextColor.Default;
            else
                title.Color = AdaptiveTextColor.Attention;
            await this.LiveCard.ReplaceElement(title);
        }

        private async void OnCardDeactivated(object sender, EventArgs e)
        {
            Trace.WriteLine("Card Deactivated");
            if (this.LiveCard.Card.TryGetElementById("Activation", out AdaptiveTextBlock activation))
            {
                activation.Text = "Deactivated";
                await this.LiveCard.ReplaceElement(activation);
                await this.LiveCard.SaveCard();
            }
        }

        private async void OnCardActivated(object sender, EventArgs e)
        {
            Trace.WriteLine("Card Activate");
            if (this.LiveCard.Card.TryGetElementById("Activation", out AdaptiveTextBlock activation))
            {
                activation.Text = "Activated";
                await this.LiveCard.ReplaceElement(activation);
            }
            AdaptiveTextInput input = new AdaptiveTextInput() { Id = "Input", Placeholder = "Enter some stuff" };
            input.OnFocus += Input_OnFocus;
            input.OnBlur += Input_OnBlur;
            input.OnTextChanged += Input_OnTextChanged;
            await this.LiveCard.InsertElement(InsertPosition.After, "Hover", input);
            await this.LiveCard.InsertElement(InsertPosition.After, "Hover", new AdaptiveTextBlock() { Id = "FocusLabel", Text = "Focus" });
            await this.LiveCard.InsertElement(InsertPosition.After, "Hover", new AdaptiveTextBlock() { Id = "TextLabel", Text = "Text" });
        }
    }

}