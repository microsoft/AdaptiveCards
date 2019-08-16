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

using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using AdaptiveCards.Rendering.Xamarin.Android;
using Android.Support.V4.App;
using Android.Graphics;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom
{
    class CustomElementRenderer : Java.Lang.Object, IBaseCardElementRenderer
    {

        public View Render(RenderedAdaptiveCard adaptiveCard, Context context, global::Android.Support.V4.App.FragmentManager fragmentManager, ViewGroup viewGroup, BaseCardElement cardElement, ICardActionHandler cardActionHandler, HostConfig hostConfig, RenderArgs renderArgs)
        {
            CustomElement customElement = (CustomElement)cardElement.FindImplObj();


            TextView textView = new TextView(context)
            {
                Text = " This is a custom element: " + customElement + "!!"
            };
            textView.SetTextColor(Color.Purple);

            viewGroup.AddView(textView);

            return textView;
        }

    }
}
