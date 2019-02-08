using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class ImageExtensions
    {

        public class AdaptiveConverterParameters
        {
            public AdaptiveConverterParameters(Image image, AdaptiveImage adaptiveImage)
            {
                Image = image;
                AdaptiveImage = adaptiveImage;
            }
            public Image Image {get; set;}
            public AdaptiveImage AdaptiveImage {get; set;}
        }
        /// <summary>
        /// Renders the element to a bitmap
        /// </summary>
        public static MemoryStream RenderToImage(this FrameworkElement element, int width)
        {
            element.Measure(new Size(width, int.MaxValue));
            // Add 100 to the height to give it some buffer. This addressed some bugs with maxlines getting clipped
            element.Arrange(new Rect(new Size(width, element.DesiredSize.Height + 100)));
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

        public static async void SetSource(this Image image, AdaptiveImage adaptiveImage, Uri url, AdaptiveRenderContext context)
        {
            if (url == null)
                return;

            image.Source = await context.ResolveImageSource(url);

            var parameters = new AdaptiveConverterParameters(image, adaptiveImage);
            var binding = new Binding
            {
                RelativeSource = RelativeSource.Self,
                Path = new PropertyPath("Parent.ActualWidth"),
                Mode = BindingMode.OneWay,
                Converter = new StretchConverter(),
                ConverterParameter = parameters
            };

            image.SetBinding(Image.StretchProperty, binding);
        }

        public class StretchConverter : IValueConverter
        {
            public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
            {
                var parentWidth = (double)value;
                var adaptiveParameters = (AdaptiveConverterParameters)parameter;
                var image = adaptiveParameters.Image;
                var adaptiveImage = adaptiveParameters.AdaptiveImage;
                var imageWidth = ((BitmapImage) image.Source)?.PixelWidth;

                if(adaptiveImage.PixelWidth != 0 || adaptiveImage.PixelHeight != 0)
                {
                    var imageHeight = ((BitmapImage) image.Source)?.PixelHeight;

                    if(adaptiveImage.PixelWidth == 0)
                    {
                        adaptiveImage.PixelWidth = (uint) ((imageWidth / (float)imageHeight) * adaptiveImage.PixelHeight);
                    }

                    if(adaptiveImage.PixelHeight == 0)
                    {
                        adaptiveImage.PixelHeight = (uint) ((imageHeight / (float)imageWidth) * adaptiveImage.PixelWidth);
                    }

                    image.Width = adaptiveImage.PixelWidth;
                    image.Height = adaptiveImage.PixelHeight;

                    return Stretch.Fill;
                }
                else if (imageWidth >= parentWidth)
                {
                    return Stretch.Uniform;
                }
                else
                {
                    return Stretch.None;
                }
            }

            public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public static BitmapImage GetBitmapFromBase64(Uri dataUri)
        {
            var encodedData = dataUri.AbsoluteUri.Substring(dataUri.AbsoluteUri.LastIndexOf(',') + 1);

            var decodedDataUri = Convert.FromBase64String(encodedData);
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.StreamSource = new MemoryStream(decodedDataUri);
            bitmap.EndInit();

            return bitmap;
        }

        public static async void SetBackgroundSource(this Grid grid, Uri uri, AdaptiveRenderContext context)
        {
            // Try to resolve the image URI
            Uri finalUri = context.Config.ResolveFinalAbsoluteUri(uri);
            if (finalUri == null)
            {
                return;
            }

            BitmapImage bi = await context.ResolveImageSource(finalUri);

            if (bi != null)
            {
                grid.Background = new ImageBrush(bi)
                {
                    Stretch = Stretch.UniformToFill,
                    AlignmentX = AlignmentX.Left,
                    AlignmentY = AlignmentY.Top
                };
            }
        }

        public static void SetImageProperties(this Image imageview, AdaptiveImage image, AdaptiveRenderContext context)
        {
            switch (image.Size)
            {
                case AdaptiveImageSize.Auto:
                    imageview.Stretch = Stretch.Uniform;
                    break;
                case AdaptiveImageSize.Stretch:
                    imageview.Stretch = Stretch.Uniform;
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
