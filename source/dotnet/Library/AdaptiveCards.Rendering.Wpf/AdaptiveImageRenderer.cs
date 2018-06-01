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

            // Try to resolve the image URI
            Uri imageUri = new Uri(image.Url, UriKind.RelativeOrAbsolute);
            if (imageUri.IsAbsoluteUri)
            {
                // If it's an absolute URI, simply set the source
                uiImage.SetSource(imageUri, context);
            }
            else
            {
                // Otherwise, combine with image base URL and try again
                string baseUrl = String.IsNullOrEmpty(context.Config.ImageBaseUrl) ? "" : context.Config.ImageBaseUrl;
                string combined = Path.Combine(baseUrl, image.Url);

                imageUri = new Uri(combined, UriKind.RelativeOrAbsolute);
                if (imageUri.IsAbsoluteUri)
                {
                    uiImage.SetSource(imageUri, context);
                }
                else
                {
                    // If it's still a relative URL, try loading directly from local resource
                    BitmapImage bi = new BitmapImage();
                    bi.BeginInit();
                    bi.UriSource = imageUri;
                    bi.EndInit();

                    uiImage.SetSource(bi);
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