using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;

namespace Adaptive
{
    public partial class Image
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<Image, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            var uiImage = new System.Windows.Controls.Image();
            // uiImage.Margin = this.Theme.ImageMargins;

            uiImage.Source = new BitmapImage(new Uri(this.Url));
            System.Windows.HorizontalAlignment alignment;
            if (Enum.TryParse<System.Windows.HorizontalAlignment>(this.HorizontalAlignment.ToString(), out alignment))
                uiImage.HorizontalAlignment = alignment;
            string style = $"Adaptive.Image";
            if (this.Size != ImageSize.Auto)
                style += $".{this.Size.ToString()}";

            if (this.Style == ImageStyle.Person)
                style += $".{this.Style.ToString()}";
            uiImage.Style = context.GetStyle(style);
            if (this.SelectAction != null)
            {
                var uiButton = (Button)this.SelectAction.Render(context.NewActionContext());
                uiButton.Content = uiImage;
                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                return uiButton;
            }
            return uiImage;
        }
    }
}