using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveImageRenderer
    {
        public static FrameworkElement Render(AdaptiveImage image, AdaptiveRenderContext context)
        {
            var uiImage = new Image();

            // Handle URL depending on its type
            if (image.Url.IsAbsoluteUri)
            {
                // If it's an absolute URI, simply set the source
                uiImage.SetSource(image.Url, context);
            }
            else
            {
                // Otherwise, combine with image base URL and try again of specified
                if (!String.IsNullOrEmpty(context.Config.ImageBaseUrl))
                {
                    try
                    {
                        Uri baseUri = new Uri(context.Config.ImageBaseUrl);
                        Uri uri = new Uri(baseUri, image.Url);
                        if (uri.IsAbsoluteUri)
                        {
                            uiImage.SetSource(uri, context);
                        }
                    }
                    catch (UriFormatException) { }
                }
            }

            uiImage.SetHorizontalAlignment(image.HorizontalAlignment);

            string style = $"Adaptive.{image.Type}";
            if (image.Style == AdaptiveImageStyle.Person)
            {
                style += $".{image.Style}";

                var mask = new RadialGradientBrush()
                {
                    GradientOrigin = new Point(0.5, 0.5),
                    Center = new Point(0.5, 0.5),
                    RadiusX = 0.5,
                    RadiusY = 0.5,
                    GradientStops = new GradientStopCollection()
                };
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#ffffffff"), .9));
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#00ffffff"), 1.0));
                uiImage.OpacityMask = mask;
            }
            uiImage.Style = context.GetStyle(style);
            uiImage.SetImageProperties(image, context);

            if (image.SelectAction != null)
            {
                return context.RenderSelectAction(image.SelectAction, uiImage);
            }
            return uiImage;
        }

    }
}