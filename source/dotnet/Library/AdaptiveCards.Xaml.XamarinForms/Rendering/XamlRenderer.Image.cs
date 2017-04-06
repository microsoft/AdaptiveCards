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
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(Image image, RenderContext context)
        {
            var uiImage = new UI.Image();
            uiImage.SetSource(image.Url, context);
            uiImage.SetHorizontalAlignment(image.HorizontalAlignment);

            string style = $"Adaptive.{image.Type}";
            if (image.Style == ImageStyle.Person)
            {
                style += $".{image.Style}";
                //TODO
            }
            uiImage.Style = this.GetStyle(style);
            switch (image.Size)
            {
                case ImageSize.Auto:
                case ImageSize.Stretch:
                    uiImage.Aspect = Aspect.AspectFill;
                    break;
                case ImageSize.Small:
                    uiImage.WidthRequest = context.Styling.Image.SizeSmall;
                    uiImage.HeightRequest = context.Styling.Image.SizeSmall;
                    break;
                case ImageSize.Medium:
                    uiImage.WidthRequest = context.Styling.Image.SizeMedium;
                    uiImage.HeightRequest = context.Styling.Image.SizeMedium;
                    break;
                case ImageSize.Large:
                    uiImage.WidthRequest = context.Styling.Image.SizeLarge;
                    uiImage.HeightRequest = context.Styling.Image.SizeLarge;
                    break;
            }
            if (image.SelectAction != null)
            {
                var uiButton = (Button)RenderAction(image.SelectAction, context);
                if (uiButton != null)
                {
                    uiButton.Content = uiImage;
                    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }
            return uiImage;
        }

    }
}