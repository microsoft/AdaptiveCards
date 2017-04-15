using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering
{
    public static class ImageExtensions
    {
        public static void SetSource(this Xamarin.Forms.Image image, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            image.SetSource(new Uri(url));
        }

        public static void SetBackgroundSource(this Xamarin.Forms.Grid grid, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            grid.SetBackgroundImage(new Uri(url));
        }
    }
}
