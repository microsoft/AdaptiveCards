using System;
using AdaptiveCards.Rendering;
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

namespace AdaptiveCards.Rendering
{
    public static class XamlImage
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveImage image = (AdaptiveImage)element;
            var uiImage = new UI.Image();
            uiImage.SetSource(image.UrlString,context);
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
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#ffffffff"), .9));
                mask.GradientStops.Add(new GradientStop((Color)ColorConverter.ConvertFromString("#00ffffff"), 1.0));
                uiImage.OpacityMask = mask;
#elif XAMARIN
                //TODO
#endif 
            }
            uiImage.Style = context.GetStyle(style);
            uiImage.SetImageProperties(image, context);

            if (image.SelectAction != null)
            {
                var uiButton = (Button)context.Render(image.SelectAction);
                if (uiButton != null)
                {
                    uiButton.Content = uiImage;
                    uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }
            return uiImage;
        }

    }
}
