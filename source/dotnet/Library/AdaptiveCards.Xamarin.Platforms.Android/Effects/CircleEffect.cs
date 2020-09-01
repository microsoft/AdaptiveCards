using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using AdaptiveCards.Xaml.XamarinForms;
using Android.Graphics;
using Android.Views;
using Xamarin.Forms;
using Xamarin.Forms.Internals;
using Xamarin.Forms.Platform.Android;

[assembly: ResolutionGroupName(ControlConstants.CompanyName)]
[assembly: ExportEffect(typeof(AdaptiveCards.XamarinForms.Platforms.Android.Effects.CircleEffect), ControlConstants.CircleEffectName)]
namespace AdaptiveCards.XamarinForms.Platforms.Android.Effects
{
    /// <summary>
    ///     ButtonCircle Renderer
    /// </summary>
    [Preserve(AllMembers = true)]
    public class CircleEffect : PlatformEffect
    {
        [Preserve]
        public CircleEffect() => Console.WriteLine("CircleEffect");

        protected override void OnAttached()
        {
            try
            {
                this.CreateCircle();
            }
            catch (Exception ex)
            {
            }
        }

        protected override void OnDetached()
        {
            try
            {
                var nativeView = this.Control ?? this.Container;
                nativeView.OutlineProvider = ViewOutlineProvider.Background;
            }
            catch (Exception ex)
            {
            }
        }

        /// <summary>
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected override void OnElementPropertyChanged(PropertyChangedEventArgs e)
        {
            base.OnElementPropertyChanged(e);
            if (this.Control == null || this.Element == null)
            {
                return;
            }

            if (e.PropertyName == VisualElement.HeightProperty.PropertyName ||
                e.PropertyName == VisualElement.WidthProperty.PropertyName
            )
            {
                this.CreateCircle();
            }
        }

        private void CreateCircle()
        {
            var nativeView = this.Control ?? this.Container;

            try
            {
                nativeView.ClipToOutline = true;
                nativeView.OutlineProvider = new RoundedCornerViewOutlineProvider();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Unable to create circle image: " + ex);
            }
        }
    }

    public class RoundedCornerViewOutlineProvider : ViewOutlineProvider
    {
        public override void GetOutline(global::Android.Views.View view, Outline outline)
        {
            float min = Math.Min(view.Width, view.Height);
            outline.SetRoundRect(new Rect(0, 0, view.Width, view.Height), min / 2.0f);
        }
    }
}