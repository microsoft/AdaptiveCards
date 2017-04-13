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
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderImage(TypedElement element, RenderContext context)
        {
            Image image = (Image)element;
            var uiImage = new UI.Image();
#if WPF
            uiImage.Source = context.ResolveImageSource(image.Url);
#elif XAMARIN
            uiImage.SetSource(new Uri(image.Url));
#endif
            uiImage.SetHorizontalAlignment(image.HorizontalAlignment);


            string style = $"Adaptive.{image.Type}";
            if (image.Style == ImageStyle.Person)
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
#if WPF
            switch (image.Size)
            {
                case ImageSize.Auto:
                    uiImage.Stretch = System.Windows.Media.Stretch.UniformToFill;
                    break;
                case ImageSize.Stretch:
                    uiImage.Stretch = System.Windows.Media.Stretch.Uniform;
                    break;
                case ImageSize.Small:
                    uiImage.Width = context.Options.Image.Size.Small;
                    uiImage.Height = context.Options.Image.Size.Small;
                    break;
                case ImageSize.Medium:
                    uiImage.Width = context.Options.Image.Size.Medium;
                    uiImage.Height = context.Options.Image.Size.Medium;
                    break;
                case ImageSize.Large:
                    uiImage.Width = context.Options.Image.Size.Large;
                    uiImage.Height = context.Options.Image.Size.Large;
                    break;
            }
#elif XAMARIN
            // TODO
#endif

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