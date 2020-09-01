// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class ImageExtensions
    {

        public class AdaptiveConverterParameters
        {
            public AdaptiveConverterParameters(Image image, AdaptiveImage adaptiveImage, AdaptiveRenderContext context)
            {
                Image = image;
                AdaptiveImage = adaptiveImage;
                AdaptiveContext = context;
            }
            public Image Image {get; set;}
            public AdaptiveImage AdaptiveImage {get; set;}
            public AdaptiveRenderContext AdaptiveContext {get; set;}
        }

#if WPF
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
#endif

        public static async void SetSource(this Image image, AdaptiveImage adaptiveImage, Uri url, AdaptiveRenderContext context)
        {
            if (url == null)
                return;

#if WPF
            image.Source = await context.ResolveImageSource(url);

            var parameters = new AdaptiveConverterParameters(image, adaptiveImage, context);
            var binding = new Binding
            {
                RelativeSource = RelativeSource.Self,
                Path = new PropertyPath("Parent.ActualWidth"),
                Mode = BindingMode.OneWay,
                Converter = new StretchConverter(),
                ConverterParameter = parameters
            };

            image.SetBinding(Image.StretchProperty, binding);
#else
            image.Source = ImageSourceFromUri(url);

            //var parameters = new AdaptiveConverterParameters(image, adaptiveImage, context);
            //var binding = new Binding
            //{
            //    Source = RelativeBindingSource.Self,
            //    Path = "Parent.WidthRequest",
            //    Mode = BindingMode.OneWay,
            //    Converter = new StretchConverter(),
            //    ConverterParameter = parameters
            //};

#endif
        }

        public static ImageSource ImageSourceFromUri(Uri url)
        {
            ImageSource imageSource;
            if (url.Scheme == "data")
            {
                var bytes = GetBase64FromDataUri(url);
                imageSource = ImageSource.FromStream(() => new MemoryStream(bytes));
            }
            else
            {
                imageSource = ImageSource.FromUri(url);
            }

            return imageSource;
        }

        public class StretchConverter : IValueConverter
        {
            public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
            {
                var parentWidth = (double)value;
                var adaptiveParameters = (AdaptiveConverterParameters)parameter;
                var image = adaptiveParameters.Image;
                var adaptiveImage = adaptiveParameters.AdaptiveImage;
#if WPF
                var imageWidth = ((BitmapImage) image.Source)?.PixelWidth;
                var imageHeight = ((BitmapImage)image.Source)?.PixelHeight;

                if (adaptiveImage.PixelWidth != 0 || adaptiveImage.PixelHeight != 0)
                {
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
                else 
                {
                    return Stretch.Uniform;
                }
#elif XAMARIN
                return null;
#endif
            }

            public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

#if WPF
        public static BitmapImage GetBitmapFromBase64(Uri dataUri)
        {
            byte[] decodedDataUri = GetBase64FromDataUri(dataUri);
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.StreamSource = new MemoryStream(decodedDataUri);
            bitmap.EndInit();

            return bitmap;
        }
#endif

        public static byte[] GetBase64FromDataUri(Uri dataUri)
        {
            var encodedData = dataUri.AbsoluteUri.Substring(dataUri.AbsoluteUri.LastIndexOf(',') + 1);

            var decodedDataUri = Convert.FromBase64String(encodedData);
            return decodedDataUri;
        }



        public static async void SetBackgroundSource(this Grid grid, AdaptiveBackgroundImage adaptiveBackgroundImage, AdaptiveRenderContext context)
        {
            // Try to resolve the image URI
            Uri finalUri = context.Config.ResolveFinalAbsoluteUri(adaptiveBackgroundImage?.Url);
            if (finalUri == null)
            {
                return;
            }
#if XAMARIN
            grid.SetBackgroundImage(finalUri);
#elif WPF
            BitmapImage bi = await context.ResolveImageSource(finalUri);

            if (bi != null)
            {
                // bi.Pixel{Width, Height}: dimensions of image
                // grid.Actual{Width, Height}: dimensions of grid containing background image
                switch (adaptiveBackgroundImage.FillMode)
                {
                    case AdaptiveImageFillMode.Repeat:
                        grid.Background = new ImageBrush(bi)
                        {
                            TileMode = TileMode.Tile,
                            Viewport = new Rect(0, 0, bi.PixelWidth, bi.PixelHeight),
                            ViewportUnits = BrushMappingMode.Absolute
                        };
                        break;
                    case AdaptiveImageFillMode.RepeatHorizontally:
                        grid.Background = new ImageBrush(bi)
                        {
                            TileMode = TileMode.FlipY,
                            Stretch = Stretch.Uniform,
                            AlignmentY = (AlignmentY) adaptiveBackgroundImage.VerticalAlignment,
                            Viewport = new Rect(0, 0, bi.PixelWidth, grid.ActualHeight + 1),
                            ViewportUnits = BrushMappingMode.Absolute
                        };
                        break;
                    case AdaptiveImageFillMode.RepeatVertically:
                        grid.Background = new ImageBrush(bi)
                        {
                            TileMode = TileMode.FlipX,
                            Stretch = Stretch.Uniform,
                            AlignmentX = (AlignmentX)adaptiveBackgroundImage.HorizontalAlignment,
                            Viewport = new Rect(0, 0, grid.ActualWidth + 1, bi.PixelWidth),
                            ViewportUnits = BrushMappingMode.Absolute
                        };
                        break;
                    case AdaptiveImageFillMode.Cover:
                    default:
                        grid.Background = new ImageBrush(bi)
                        {
                            Stretch = Stretch.UniformToFill,
                            AlignmentY = (AlignmentY)adaptiveBackgroundImage.VerticalAlignment,
                            AlignmentX = (AlignmentX)adaptiveBackgroundImage.HorizontalAlignment
                        };
                        break;
                }
            }
#endif
        }

        public static void SetImageProperties(this Image imageview, AdaptiveImage image, AdaptiveRenderContext context)
        {
#if WPF
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
#elif XAMARIN
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
#endif
        }
    }
}