using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering
{
    public static class ImageExtensions
    {
        public static void SetSource(this System.Windows.Controls.Image image, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            image.Source = context.ResolveImageSource(url);
        }

        public static void SetBackgroundSource(this Grid grid, string url, RenderContext context)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;
            grid.Background = new ImageBrush(context.ResolveImageSource(url));
        }

        public static void SetImageProperties(this System.Windows.Controls.Image imageview, Image image, RenderContext context)
        {
            switch (image.Size)
            {
                case ImageSize.Auto:
                    imageview.Stretch = System.Windows.Media.Stretch.UniformToFill;
                    break;
                case ImageSize.Stretch:
                    imageview.Stretch = System.Windows.Media.Stretch.Uniform;
                    break;
                case ImageSize.Small:
                    imageview.Width = context.Config.ImageSizes.Small;
                    imageview.Height = context.Config.ImageSizes.Small;
                    break;
                case ImageSize.Medium:
                    imageview.Width = context.Config.ImageSizes.Medium;
                    imageview.Height = context.Config.ImageSizes.Medium;
                    break;
                case ImageSize.Large:
                    imageview.Width = context.Config.ImageSizes.Large;
                    imageview.Height = context.Config.ImageSizes.Large;
                    break;
            }
        }
    }
}
