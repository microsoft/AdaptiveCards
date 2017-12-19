using AdaptiveCards;
using System;
using System.Diagnostics;
using System.Net.Http;
using LiveCardAPI;
using LiveCardServer;

namespace LiveCardServerSample.Controllers
{

    public class HelloWorldController : LiveCardController
    {
        public HttpResponseMessage Get()
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

            // start with deactivated card, but if client hooks up WebSocket then it becomes activated live card
            return ServiceLiveCard(helloCard);
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
        }
    }

}