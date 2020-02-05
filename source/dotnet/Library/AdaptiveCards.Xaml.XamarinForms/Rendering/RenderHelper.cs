using System;
using Xamarin.Forms;
using UI = Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    internal static class RenderHelper
    {
        public static void SetBackgroundImage(this Grid grid, Uri uri)
        {
            grid.Children.Add(new UI.Image() { Source = ImageSource.FromUri(uri) });
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
                    image.HorizontalOptions = LayoutOptions.Start;
                    break;

                case AdaptiveHorizontalAlignment.Center:
                    image.HorizontalOptions = LayoutOptions.Center;
                    break;

                case AdaptiveHorizontalAlignment.Right:
                    image.HorizontalOptions = LayoutOptions.End;
                    break;

                default:
                    image.HorizontalOptions = LayoutOptions.FillAndExpand; //images fill available width
                    break;
            }
        }
    }
}
