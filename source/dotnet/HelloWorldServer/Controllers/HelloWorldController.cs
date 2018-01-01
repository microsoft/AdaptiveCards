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
using Newtonsoft.Json;

namespace LiveCardServerSample.Controllers
{
    [Route("api/[controller]")]
    public class HelloWorldController : Controller
    {
        public LiveCard LiveCard { get; private set; }

        [HttpGet]
        public async Task<AdaptiveCard> Get()
        {
            AdaptiveCard helloCard = CreateCard();

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

        private AdaptiveCard CreateCard()
        {
            var helloCard = new AdaptiveCard() { Id = "HelloWorld" };
            var title = new AdaptiveTextBlock() { Id = "Title", Text = "Hello World", Size = AdaptiveTextSize.Large };
            helloCard.Body.Add(title);
            var activatation = new AdaptiveTextBlock() { Id = "Activation", Text = $"Deactivated" };
            helloCard.Body.Add(activatation);

            // hook up code behind
            helloCard.OnCardActivate += OnCardActivated;
            helloCard.OnCardDeactivate += OnCardDeactivated;
            return helloCard;
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
                if (this.LiveCard.Card.TryGetElementById("Title", out AdaptiveTextBlock title))
                {
                    var title2 = JsonConvert.DeserializeObject<AdaptiveTextBlock>(JsonConvert.SerializeObject(title));
                    title2.Text = "Hello World - Click on me";
                    title2.OnClick += Title_OnClick;
                    title2.OnMouseEnter += Title_OnMouseEnter;
                    title2.OnMouseLeave += Title_OnMouseLeave;
                    this.LiveCard.Card.ReplaceElement(title2);
#pragma warning disable CS4014 // Because this call is not awaited, execution of the current method continues before the call is completed
                    Task.Run(async () =>
                    {
                        while (!this.LiveCard.ListeningTask.IsCompleted)
                        {
                            await Task.Delay(500);
                            if (title2.Weight == AdaptiveTextWeight.Default)
                                title2.Weight = AdaptiveTextWeight.Bolder;
                            else
                                title2.Weight = AdaptiveTextWeight.Default;
                        }
                    });
#pragma warning restore CS4014 // Because this call is not awaited, execution of the current method continues before the call is completed
                }
                AdaptiveTextInput input = new AdaptiveTextInput() { Id = "Input", Placeholder = "Enter some stuff" };
                input.OnFocus += Input_OnFocus;
                input.OnBlur += Input_OnBlur;
                input.OnTextChanged += Input_OnTextChanged;
                this.LiveCard.Card.Body.Add(input);
                this.LiveCard.Card.Body.Add(new AdaptiveTextBlock() { Id = "FocusLabel", Text = "Focus" });
                this.LiveCard.Card.Body.Add(new AdaptiveTextBlock() { Id = "TextLabel", Text = "Text" });
                var hover = new AdaptiveTextBlock() { Id = "HoverLabel", Text = $"No mouse" };
                this.LiveCard.Card.Body.Add(hover);

            }
        }

        private async void Input_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                var input = (AdaptiveTextInput)sender;
                Trace.WriteLine($"{input.Id} OnTextChanged");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("TextLabel", out AdaptiveTextBlock label))
                {
                    label.Text = $"Input.Text={e.Text}";
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
                AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{title.Id} MouseLeave");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("HoverLabel", out AdaptiveTextBlock label))
                {
                    label.Text = "Title-Mouse Leave";
                }
            }
        }

        private async void Title_OnMouseEnter(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{title.Id} MouseEnter");
                if (this.LiveCard.Card.TryGetElementById<AdaptiveTextBlock>("HoverLabel", out AdaptiveTextBlock label))
                {
                    label.Text = "Title-Mouse entered";
                }
            }
        }

        private async void Title_OnClick(object sender, EventArgs e)
        {
            using (await new AsyncLock().LockAsync())
            {
                AdaptiveTextBlock title = (AdaptiveTextBlock)sender;
                Trace.WriteLine($"{title.Id} Click");

                if (title.Size == AdaptiveTextSize.ExtraLarge)
                    title.Size = AdaptiveTextSize.Small;
                else
                    title.Size += 1;
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
                    await this.LiveCard.Client.SaveCard(CreateCard());
                }
            }
        }


    }

}