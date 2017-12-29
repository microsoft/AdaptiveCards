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
            // title.OnClick += Title_OnClick;
            var activatation = new AdaptiveTextBlock() { Id = "Activation", Text = $"Deactivated" };
            helloCard.Body.Add(title);
            helloCard.Body.Add(activatation);

            // hook up code behind
            helloCard.OnCardActivate += OnCardActivated;
            helloCard.OnCardDeactivate += OnCardDeactivated;

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
            using (await new AsyncLock().LockAsync())
            {
                var input = (AdaptiveTextInput)sender;
                Trace.WriteLine($"{input.Id} OnTextChanged");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("TextLabel", out AdaptiveTextBlock label))
                {
                    label.Text = e.Text;
                }
            }
        }

        private async void Input_OnBlur(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                var input = (AdaptiveElement)sender;
                Trace.WriteLine($"{input.Id} OnBlur");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("FocusLabel", out AdaptiveTextBlock label))
                {
                    label.Text = "input does not have focus";
                }
            }
        }

        private async void Input_OnFocus(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                var input = (AdaptiveInput)sender;
                Trace.WriteLine($"{input.Id} OnFocus");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("FocusLabel", out AdaptiveTextBlock label))
                {
                    label.Text = "Input has focus";
                }
            }
        }

        private async void Title_OnMouseLeave(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock hover = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{hover.Id} MouseLeave");
                hover.Text = "No Mouse";
            }
        }

        private async void Title_OnMouseEnter(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock hover = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{hover.Id} MouseEnter");
                hover.Text = "Mouse Mouse Mouse";
            }
        }

        private async void Title_OnClick(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{title.Id} Click");
                if (title.Weight == AdaptiveTextWeight.Default)
                    title.Weight = AdaptiveTextWeight.Bolder;
                else
                    title.Weight = AdaptiveTextWeight.Default;
            }
        }
        private async void Title_OnDoubleClick(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{title.Id} Double Click");
                if (title.Color == AdaptiveTextColor.Attention)
                    title.Color = AdaptiveTextColor.Default;
                else
                    title.Color = AdaptiveTextColor.Attention;
            }
        }

        private async void OnCardDeactivated(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                Trace.WriteLine("Card Deactivated");
                if (this.LiveCard.Card.TryGetElementById("Activation", out AdaptiveTextBlock activation))
                {
                    activation.Text = "Deactivated";
                    await this.LiveCard.Client.SaveCard();
                }
            }
        }

        private async void OnCardActivated(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                Trace.WriteLine("Card Activate");

                if (this.LiveCard.Card.TryGetElementById("Activation", out AdaptiveTextBlock activation))
                {
                    activation.Text = "Activated";
                }
                AdaptiveTextInput input = new AdaptiveTextInput() { Id = "Input", Placeholder = "Enter some stuff" };
                input.OnFocus += Input_OnFocus;
                input.OnBlur += Input_OnBlur;
                input.OnTextChanged += Input_OnTextChanged;
                var hover = new AdaptiveTextBlock() { Id = "Hover", Text = $"No mouse" };
                this.LiveCard.Card.Body.Add(hover);
                this.LiveCard.Card.Body.Add(input);
                this.LiveCard.Card.Body.Add(new AdaptiveTextBlock() { Id = "FocusLabel", Text = "Focus" });
                this.LiveCard.Card.Body.Add(new AdaptiveTextBlock() { Id = "TextLabel", Text = "Text" });
            }
        }
    }

}