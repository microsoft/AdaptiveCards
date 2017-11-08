using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class ImageExtensions
    {

        /// <summary>
        /// Renders the element to a bitmap
        /// </summary>
        public static MemoryStream RenderToImage(this FrameworkElement element, int width)
        {
            element.Measure(new Size(width, int.MaxValue));
            element.Arrange(new Rect(new Size(width, element.DesiredSize.Height)));
            element.UpdateLayout();

            var bitmapImage = new RenderTargetBitmap((int)width, (int)element.DesiredSize.Height, 96, 96,
                PixelFormats.Default);
            bitmapImage.Render(element);

            var encoder = new PngBitmapEncoder();
            var metadata = new BitmapMetadata("png");
            // TODO: Should we set the image metadata?
            //metadata.SetQuery("/tEXt/{str=Description}", JsonConvert.SerializeObject(OriginatingCard));
            var pngFrame = BitmapFrame.Create(bitmapImage, null, metadata, null);
            encoder.Frames.Add(pngFrame);

            var stream = new MemoryStream();
            encoder.Save(stream);
            stream.Seek(0, SeekOrigin.Begin);
            return stream;
        }

        public static async void SetSource(this Image image, Uri url, AdaptiveRenderContext context)
        {
            if (url == null)
                return;

            image.Source = await context.ResolveImageSource(url);
        }

        public static async void SetBackgroundSource(this Grid grid, Uri url, AdaptiveRenderContext context)
        {
            if (url == null)
                return;

            grid.Background = new ImageBrush(await context.ResolveImageSource(url))
            {
                Stretch = Stretch.UniformToFill,
                AlignmentX = AlignmentX.Left,
                AlignmentY = AlignmentY.Top
            };
        }

        public static void SetImageProperties(this Image imageview, AdaptiveImage image, AdaptiveRenderContext context)
        {
            switch (image.Size)
            {
                case AdaptiveImageSize.Auto:
                    imageview.Stretch = System.Windows.Media.Stretch.Uniform;
                    break;
                case AdaptiveImageSize.Stretch:
                    imageview.Stretch = System.Windows.Media.Stretch.Uniform;
                    break;
                case AdaptiveImageSize.Small:
                    imageview.Width = context.Config.ImageSizes.Small;
                    imageview.Height = context.Config.ImageSizes.Small;
                    break;
                case AdaptiveImageSize.Medium:
                    imageview.Width = context.Config.ImageSizes.Medium;
                    imageview.Height = context.Config.ImageSizes.Medium;
                    break;
                case AdaptiveImageSize.Large:
                    imageview.Width = context.Config.ImageSizes.Large;
                    imageview.Height = context.Config.ImageSizes.Large;
                    break;
            }
        }
    }
}
