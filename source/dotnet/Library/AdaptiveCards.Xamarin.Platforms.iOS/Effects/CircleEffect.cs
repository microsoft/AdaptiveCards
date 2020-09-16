using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using AdaptiveCards.Xaml.XamarinForms;
using Foundation;
using UIKit;
using Xamarin.Forms;
using Xamarin.Forms.Platform.iOS;

[assembly: ResolutionGroupName(ControlConstants.CompanyName)]
[assembly: ExportEffect(typeof(AdaptiveCards.XamarinForms.Platforms.iOS.Effects.CircleEffect), ControlConstants.CircleEffectName)]
namespace AdaptiveCards.XamarinForms.Platforms.iOS.Effects
{
    /// <summary>
    ///     ButtonCircle Renderer
    /// </summary>
    [Preserve(AllMembers = true)]
    public class CircleEffect : PlatformEffect
    {
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
                UIView nativeView = this.Control ?? this.Container;
                nativeView.Layer.CornerRadius = 0;
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
            UIView nativeView = this.Control ?? this.Container;
            View formsView = this.Element as View;

            try
            {
                double min = Math.Min(formsView.WidthRequest, formsView.HeightRequest);
                nativeView.Layer.CornerRadius = (nfloat)(min / 2.0);
                nativeView.Layer.MasksToBounds = false;
                nativeView.ClipsToBounds = true;
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Unable to create circle image: " + ex);
            }
        }
    }
}
