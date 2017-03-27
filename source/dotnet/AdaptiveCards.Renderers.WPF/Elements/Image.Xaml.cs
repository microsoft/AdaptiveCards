using System;
using System.Windows.Controls;

#if WPF
using System.Windows;
using UI = System.Windows.Controls;
using System.Windows.Media.Imaging;

#elif Xamarin
using Xamarin.Forms;
using UI = Xamarin.Forms;
#endif

namespace AdaptiveCards.Renderers
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

            uiImage.Source = new BitmapImage(new Uri(image.Url));
            System.Windows.HorizontalAlignment alignement;
            if (Enum.TryParse(image.HorizontalAlignment.ToString(), out alignement))
                uiImage.HorizontalAlignment = alignement;

            string style = $"Adaptive.Image";
            if (image.Size != ImageSize.Auto)
                style += $".{image.Size}";

            if (image.Style == ImageStyle.Person)
                style += $".{image.Style}";
            uiImage.Style = this.GetStyle(style);

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