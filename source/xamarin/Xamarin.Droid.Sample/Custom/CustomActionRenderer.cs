using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V4.App;
using Android.Views;
using Android.Widget;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom
{
    class CustomActionRenderer : Java.Lang.Object, IBaseActionElementRenderer
    {
        public Button Render(RenderedAdaptiveCard p0, Context p1, global::Android.Support.V4.App.FragmentManager p2, ViewGroup p3, BaseActionElement p4, ICardActionHandler p5, HostConfig p6, RenderArgs p7)
        {
            Button actionButton = new Button(p1);

            CustomAction action = (CustomAction)p4.FindImplObj();

            actionButton.Text = action.SomeData;
            actionButton.SetBackgroundColor(global::Android.Graphics.Color.Red);
            actionButton.SetAllCaps(false);
            actionButton.SetOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(p0, p4, p5));

            p3.AddView(actionButton);

            return actionButton;
        }
    }
}
