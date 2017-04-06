using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering
{
    public static class ImageExtensions
    {
        public static void SetSource(this System.Windows.Controls.Image image, string url, RenderContext context )
        {
            image.Source = context.ResolveBitmapImage(url);
        }
        public static BitmapImage ResolveBitmapImage( this RenderContext context, string url)
        {
            BitmapImage source = null;
            if (context.ImageResolver != null)
            {
                // off screen rendering can pass already loaded image to us so we can render immediately
                var stream = context.ImageResolver(url);
                if (stream != null)
                {
                    source = new BitmapImage();
                    source.BeginInit();
                    source.StreamSource = stream;
                    source.EndInit();
                }
            }
            return source ?? new BitmapImage(new Uri(url));
        }
    }
}
