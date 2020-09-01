// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.IO;
#if WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using UI = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using UI = Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveImageRenderer
    {
        public static FrameworkElement Render(AdaptiveImage image, AdaptiveRenderContext context)
        {
            FrameworkElement uiBorder = null;
            var uiImage = new Image();

            // Try to resolve the image URI
            Uri finalUri = context.Config.ResolveFinalAbsoluteUri(image.Url);
            if (finalUri == null)
            {
                return uiImage;
            }

            uiImage.SetSource(image, finalUri, context);

            uiImage.SetHorizontalAlignment(image.HorizontalAlignment);

            string style = $"Adaptive.{image.Type}";
            if (image.Style == AdaptiveImageStyle.Person)
            {
                style += $".{image.Style}";
#if WPF
                var mask = new RadialGradientBrush()
                {
                    GradientOrigin = new Point(0.5, 0.5),
                    Center = new Point(0.5, 0.5),
                    RadiusX = 0.5,
                    RadiusY = 0.5,
                    GradientStops = new GradientStopCollection()
                };
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#ffffffff"), 1.0));
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#00ffffff"), 1.0));
                uiImage.OpacityMask = mask;
#elif XAMARIN
                //TODO
                uiImage.ToRadialImage();

#endif
            }
            uiImage.Style = context.GetStyle(style);

            if (image.PixelHeight == 0 && image.PixelWidth == 0)
            {
                uiImage.SetImageProperties(image, context);
            }

#if WPF
            // If we have a background color, we'll create a border for the background and put the image on top
            if (!string.IsNullOrEmpty(image.BackgroundColor))
            {
                Color color = (Color)ColorConverter.ConvertFromString(image.BackgroundColor);
                if (color.A != 0)
                {
                    uiBorder = new Border()
                    {
                        Background = new SolidColorBrush(color),
                        Child = uiImage,
                        Width = uiImage.Width,
                        Height = uiImage.Height,
                        HorizontalAlignment = uiImage.HorizontalAlignment,
                        VerticalAlignment = uiImage.VerticalAlignment,
                        OpacityMask = uiImage.OpacityMask
                    };
                }
            }

            return RendererUtil.ApplySelectAction(uiBorder ?? uiImage, image, context);
#elif XAMARIN
            // If we have a background color, we'll create a border for the background and put the image on top
            if (!string.IsNullOrEmpty(image.BackgroundColor))
            {
                Color color = (Color)context.GetColor(image.BackgroundColor);
                if (color.A != 0)
                {
                    uiBorder = new Frame()
                    {
                        Padding = 0,
                        BackgroundColor = color,
                        Content = uiImage,
                        WidthRequest = uiImage.Width,
                        HeightRequest = uiImage.Height,
                        HorizontalOptions = uiImage.HorizontalOptions,
                        VerticalOptions = uiImage.HorizontalOptions,
                        Opacity = uiImage.Opacity
                    };
                }
            }

            return RendererUtil.ApplySelectAction(uiBorder ?? uiImage, image, context);
#endif
        }

    }
}
