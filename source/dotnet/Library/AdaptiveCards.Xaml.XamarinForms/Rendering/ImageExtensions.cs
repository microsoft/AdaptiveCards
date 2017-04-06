using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering
{
    public static class ImageExtensions
    {
        public static void SetSource(this Xamarin.Forms.Image image, string url, RenderContext context)
        {
            image.SetSource(new Uri(url));
        }
    }
}
