using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public static class ImageExtensions
    {
        public static void ToRadialImage(this Image image)
        {
            Effect item = Effect.Resolve(Xaml.XamarinForms.ControlConstants.CircleEffectResolutionName);
            image.Effects.Add(item);
        }

        public static void SetSource(this Image image, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            image.SetSource(new Uri(url));
        }

        public static void SetBackgroundSource(this Grid grid, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            grid.SetBackgroundImage(new Uri(url));
        }

        public static void SetImageProperties(this Image imageview, AdaptiveImage image, RenderContext context)
        {
            switch (image.Size)
            {
                case AdaptiveImageSize.Auto:
                case AdaptiveImageSize.Stretch:
                    imageview.VerticalOptions = LayoutOptions.FillAndExpand;
                    imageview.HorizontalOptions = LayoutOptions.FillAndExpand;
                    break;
                case AdaptiveImageSize.Small:
                    imageview.WidthRequest = context.Config.ImageSizes.Small;
                    imageview.HeightRequest = context.Config.ImageSizes.Small;
                    break;
                case AdaptiveImageSize.Medium:
                    imageview.WidthRequest = context.Config.ImageSizes.Medium;
                    imageview.HeightRequest = context.Config.ImageSizes.Medium;
                    break;
                case AdaptiveImageSize.Large:
                    imageview.WidthRequest = context.Config.ImageSizes.Large;
                    imageview.HeightRequest = context.Config.ImageSizes.Large;
                    break;
            }
        }
    }
}
