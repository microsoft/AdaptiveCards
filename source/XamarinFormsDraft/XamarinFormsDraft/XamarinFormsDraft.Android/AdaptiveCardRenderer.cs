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

[assembly: ExportRenderer(typeof(AdaptiveCardControl), typeof(AdaptiveCards.Rendering.XamarinForms.Droid.AdaptiveCardRenderer))]
namespace AdaptiveCards.Rendering.XamarinForms.Droid
{
    class AdaptiveCardRenderer : ViewRenderer<AdaptiveCardControl, Android.Views.View>
    {

        Android.Views.View adaptiveCardView;
        Android.Support.V4.App.FragmentManager supportFragmentManager;
        ICardActionHandler cardActionHandler;

        public AdaptiveCardRenderer(Context context) : base(context) { }

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


                    string cardContent = e.NewElement.CardContent;

                    ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardContent, "1.2");

                    var renderedCard = AdaptiveCards.Rendering.Xamarin.Android.Renderer.AdaptiveCardRenderer.Instance.Render(Context, supportFragmentManager, parseResult.AdaptiveCard, cardActionHandler, new HostConfig());
                    adaptiveCardView = renderedCard.View;
                    SetNativeControl(adaptiveCardView);
                }
                                
            }
        }

    }
}