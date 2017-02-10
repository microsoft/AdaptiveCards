using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;
using AC = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    public partial class AdaptiveXamlRenderer
    {
        private ResourceDictionary resources;

        public AdaptiveXamlRenderer(ResourceDictionary resources)
        {
            this.resources = resources;
        }


        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
        public UIElement Render(AC.TextBlock textBlock)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new XamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            // uiTextBlock.Text = textBlock.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(textBlock.Text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);
            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = resources["Adaptive.TextBlock"] as Style;


            if (textBlock.HorizontalAlignment.HasValue)
            {
                HorizontalAlignment alignment;
                if (Enum.TryParse<HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            switch (textBlock.TextSize)
            {
                case AC.TextSize.Small:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Small"] as Style;
                    break;
                case AC.TextSize.Medium:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Medium"] as Style;
                    break;
                case AC.TextSize.Large:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Large"] as Style;
                    break;
                case AC.TextSize.ExtraLarge:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.ExtraLarge"] as Style;
                    break;
                case AC.TextSize.Normal:
                default:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Normal"] as Style;
                    break;
            }

            switch (textBlock.TextColor)
            {
                case AC.TextColor.Accent:
                    uiTextBlock.Foreground = resources["Adaptive.AccentBrush"] as Brush;
                    break;
                case AC.TextColor.Attention:
                    uiTextBlock.Foreground = resources["Adaptive.AttentionBrush"] as Brush;
                    break;
                case AC.TextColor.Dark:
                    uiTextBlock.Foreground = resources["Adaptive.DarkBrush"] as Brush;
                    break;
                case AC.TextColor.Good:
                    uiTextBlock.Foreground = resources["Adaptive.GoodBrush"] as Brush;
                    break;
                case AC.TextColor.Light:
                    uiTextBlock.Foreground = resources["Adaptive.LightBrush"] as Brush;
                    break;
                case AC.TextColor.Warning:
                    uiTextBlock.Foreground = resources["Adaptive.WarningBrush"] as Brush;
                    break;
                case AC.TextColor.Default:
                default:
                    uiTextBlock.Foreground = resources["Adaptive.DefaultBrush"] as Brush;
                    break;
            }

            switch (textBlock.TextWeight)
            {
                case AC.TextWeight.Bolder:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.BolderFontWeight"];
                    break;
                case AC.TextWeight.Lighter:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.LighterFontWeight"];
                    break;
                case AC.TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.NormalFontWeight"];
                    break;
            }

            if (textBlock.Wrap.HasValue && textBlock.Wrap == true)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            if (textBlock.IsSubtle.HasValue && textBlock.IsSubtle == true)
                uiTextBlock.Opacity = (double)resources["Adaptive.IsSubtleOpacity"];
            return uiTextBlock;
        }


        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        public UIElement Render(AC.Image image)
        {
            var uiImage = new Image();
            // uiImage.Margin = this.Theme.ImageMargins;

            uiImage.Source = new BitmapImage(new Uri(image.Url));
            HorizontalAlignment alignment;
            if (Enum.TryParse<HorizontalAlignment>(image.HorizontalAlignment.ToString(), out alignment))
                uiImage.HorizontalAlignment = alignment;
            // How do  I figure image size???
            // image.Size = AC.Schema.Net.Size.
            string style = $"Adaptive.Image";
            if (image.Size != null)
                style += $".{image.Size.ToString()}";

            if (image.Style == AC.ImageStyle.Person)
                style += $".{image.Style.ToString()}";
            uiImage.Style = resources[style] as Style;
            return uiImage;
        }

    }
}