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

[assembly: ExportRenderer(typeof(AdaptiveCardControl), typeof(AdaptiveCards.Rendering.XamarinForms.UWP.AdaptiveCardRenderer2))]
namespace AdaptiveCards.Rendering.XamarinForms.UWP
{
    class AdaptiveCardRenderer2 : ViewRenderer<AdaptiveCardControl, Windows.UI.Xaml.FrameworkElement>
    {

        FrameworkElement adaptiveCardView;
        AdaptiveCardRenderer _renderer = null;

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
            }
            if (e.NewElement != null)
            {
                if (Control == null)
                {
                    string cardContent = e.NewElement.CardContent;
                    JsonObject jsonObject;
                    if (JsonObject.TryParse(cardContent, out jsonObject))
                    {
                        AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(jsonObject);

                        RenderedAdaptiveCard _renderedAdaptiveCard = _renderer.RenderAdaptiveCard(parseResult.AdaptiveCard);

                        adaptiveCardView = _renderedAdaptiveCard.FrameworkElement;

                        SetNativeControl(adaptiveCardView);
                    }
                                        
                }
            }
        }

    }
}
