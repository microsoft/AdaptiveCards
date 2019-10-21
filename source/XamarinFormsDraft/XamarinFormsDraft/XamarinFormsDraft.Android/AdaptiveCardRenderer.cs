using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Xamarin.Forms;
using Xamarin.Forms.Platform.Android;
using AdaptiveCards.Rendering.XamarinForms;
using AdaptiveCards.Rendering.XamarinForms.Droid;

using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using System.ComponentModel;

[assembly: ExportRenderer(typeof(AdaptiveCardControl), typeof(AdaptiveCards.Rendering.XamarinForms.Droid.AdaptiveCardRenderer))]
namespace AdaptiveCards.Rendering.XamarinForms.Droid
{

    class CardActionHandler : Java.Lang.Object, ICardActionHandler
    {
        private AdaptiveCardControl newElement;

        public CardActionHandler(AdaptiveCardControl newElement)
        {
            this.newElement = newElement;
        }

        List<AdaptiveWarning> ToList(Java.Util.Vector warnings)
        {
            List<AdaptiveWarning> contractWarnings = new List<AdaptiveWarning>();
            for (int i = 0; i < warnings.Size(); ++i)
            {
                AdaptiveWarning warning = warnings.Get(0) as AdaptiveWarning;
                contractWarnings.Add(warning);
            }

            return contractWarnings;
        }

        // The action is the sender while the erendered card is the event argument
        public void OnAction(BaseActionElement baseAction, RenderedAdaptiveCard renderedCard)
        {
            AdaptiveEventArgs adaptiveEventArgs = new AdaptiveEventArgs();

            // adaptiveRenderArgs.AdaptiveCard = renderedCard.AdaptiveCard.SerializeToJsonValue().ToString();
            // adaptiveRenderArgs.BaseActionElement = baseAction;
            adaptiveEventArgs.Inputs = new Dictionary<string, string>(renderedCard.Inputs);
            // adaptiveRenderArgs.Warnings = ToList(renderedCard.Warnings);
            adaptiveEventArgs.Visual = renderedCard.View;

            // This is how it should work
            newElement.SendActionEvent(adaptiveEventArgs);
            // newElement.SendActionEvent(renderedCard, adaptiveRenderArgs);
        }

        public void OnMediaPlay(BaseCardElement p0, RenderedAdaptiveCard p1)
        {
            throw new NotImplementedException();
        }

        public void OnMediaStop(BaseCardElement p0, RenderedAdaptiveCard p1)
        {
            throw new NotImplementedException();
        }
    }

    class AdaptiveCardRenderer : ViewRenderer<AdaptiveCardControl, Android.Views.View>
    {

        Android.Views.View adaptiveCardView;
        Android.Support.V4.App.FragmentManager supportFragmentManager;
        ICardActionHandler cardActionHandler;

        public AdaptiveCardRenderer(Context context) : base(context) 
        {
            
        }

        private void RenderCard(string cardContent, AdaptiveCardControl cardControl)
        {
            if (cardContent == "") return;

            cardActionHandler = new CardActionHandler(cardControl);

            ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardContent, "1.2");

            var renderedCard = AdaptiveCards.Rendering.Xamarin.Android.Renderer.AdaptiveCardRenderer.Instance.Render(Context, supportFragmentManager, parseResult.AdaptiveCard, cardActionHandler, new HostConfig());
            adaptiveCardView = renderedCard.View;
            SetNativeControl(adaptiveCardView);
        }

        protected override void OnElementChanged(ElementChangedEventArgs<AdaptiveCardControl> e)
        {
            base.OnElementChanged(e);

            if (e.OldElement != null)
            {

            }

            if (e.NewElement != null)
            {
                if (Control == null)
                {
                    RenderCard(e.NewElement.CardContent, e.NewElement);
                }
                                
            }
        }

        protected override void OnElementPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            base.OnElementPropertyChanged(sender, e);

            if (e.PropertyName == "Card")
            {
                AdaptiveCardControl cardControl = sender as AdaptiveCardControl;

                RenderCard(cardControl.CardContent, cardControl);
            }
        }

    }
}
