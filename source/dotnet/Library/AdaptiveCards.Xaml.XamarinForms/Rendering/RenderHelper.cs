using System;
using Xamarin.Forms;
using UI = Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    internal static class RenderHelper
    {
        public static void SetBackgroundImage(this Grid grid, Uri uri)
        {
            var source = AdaptiveCards.Rendering.Wpf.ImageExtensions.ImageSourceFromUri(uri);

            grid.Children.Add(new UI.Image() { Source = source, Aspect = Aspect.AspectFill });
        }

        public static void SetSource(this UI.Image image, Uri uri)
        {
            image.Source = ImageSource.FromUri(uri);
        }

        public static void SetHorizontalAlignment(this UI.Image image, AdaptiveHorizontalAlignment alignment)
        {
            switch (alignment)
            {
                case AdaptiveHorizontalAlignment.Left:
                    image.HorizontalOptions = LayoutOptions.StartAndExpand;
                    break;

                case AdaptiveHorizontalAlignment.Center:
                    image.HorizontalOptions = LayoutOptions.CenterAndExpand;
                    break;

                case AdaptiveHorizontalAlignment.Right:
                    image.HorizontalOptions = LayoutOptions.EndAndExpand;
                    break;

                default:
                    image.HorizontalOptions = LayoutOptions.FillAndExpand; //images fill available width
                    break;
            }
        }
    }
}
