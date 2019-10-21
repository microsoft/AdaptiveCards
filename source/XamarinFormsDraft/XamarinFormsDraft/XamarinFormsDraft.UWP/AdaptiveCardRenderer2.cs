using Xamarin.Forms.Platform.UWP;
using AdaptiveCards.Rendering.Uwp;
using AdaptiveCards.Rendering.XamarinForms;
using AdaptiveCards.Rendering.XamarinForms.UWP;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Windows.UI.Xaml;
using Windows.Data.Json;
using Windows.Foundation;
using Windows.Foundation.Collections;
using System.ComponentModel;

[assembly: ExportRenderer(typeof(AdaptiveCardControl), typeof(AdaptiveCards.Rendering.XamarinForms.UWP.AdaptiveCardRenderer2))]
namespace AdaptiveCards.Rendering.XamarinForms.UWP
{
    class AdaptiveCardRenderer2 : ViewRenderer<AdaptiveCardControl, Windows.UI.Xaml.FrameworkElement>
    {

        FrameworkElement adaptiveCardView;
        AdaptiveCardRenderer _renderer = null;
        RenderedAdaptiveCard renderedAdaptiveCard = null;

        private RenderedAdaptiveCard RenderCard(string card, AdaptiveCardControl cardControl)
        {
            JsonObject jsonObject;
            RenderedAdaptiveCard _renderedAdaptiveCard = null;
            if (JsonObject.TryParse(card, out jsonObject))
            {
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(jsonObject);
                _renderedAdaptiveCard = _renderer.RenderAdaptiveCard(parseResult.AdaptiveCard);

                _renderedAdaptiveCard.Action += new TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs>(
                    delegate (RenderedAdaptiveCard renderedCard, AdaptiveActionEventArgs eventArgs)
                    {
                        AdaptiveEventArgs adaptiveEventArgs = new AdaptiveEventArgs();
                        ValueSet valueSet = eventArgs.Inputs.AsValueSet();

                        adaptiveEventArgs.Inputs = new Dictionary<string, string>();
                        foreach (KeyValuePair<string, object> keyValuePair in valueSet)
                        {
                            adaptiveEventArgs.Inputs.Add(keyValuePair.Key, keyValuePair.Value.ToString());
                        }

                        adaptiveEventArgs.Visual = renderedCard.FrameworkElement;

                        cardControl.SendActionEvent(adaptiveEventArgs);
                    });
            }

            return _renderedAdaptiveCard;
        }

        protected override void OnElementChanged(ElementChangedEventArgs<AdaptiveCardControl> e)
        {
            base.OnElementChanged(e);

            if (_renderer == null)
            {
                _renderer = new AdaptiveCardRenderer();
            }

            if (e.OldElement != null)
            {
                // Unsubscribe
                adaptiveCardView = null;
                e.OldElement.PropertyChanged -= OnElementPropertyChanged;
            }

            if (e.NewElement != null)
            {
                e.NewElement.PropertyChanged += OnElementPropertyChanged;

                if (Control == null)
                {
                    string cardContent = e.NewElement.CardContent;

                    renderedAdaptiveCard = RenderCard(cardContent, e.NewElement);
                    adaptiveCardView = renderedAdaptiveCard.FrameworkElement;

                    SetNativeControl(adaptiveCardView);
                }

            }
        }


        protected override void OnElementPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            base.OnElementPropertyChanged(sender, e);

            if (e.PropertyName == "Card")
            {
                AdaptiveCardControl cardControl = sender as AdaptiveCardControl;

                string cardContent = cardControl.CardContent;

                renderedAdaptiveCard = RenderCard(cardContent, cardControl);
                adaptiveCardView = renderedAdaptiveCard.FrameworkElement;

                SetNativeControl(adaptiveCardView);
            }
        }
    }
}
