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
using Adaptive.Schema.Net;
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

        public delegate void ActionEventHandler(object sender, ActionEventArgs e);

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public event ActionEventHandler OnAction;

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
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = resources["Adaptive.TextBlock"] as Style;


            if (textBlock.HorizontalAlignment.HasValue)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            switch (textBlock.TextSize)
            {
                case TextSize.Small:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Small"] as Style;
                    break;
                case TextSize.Medium:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Medium"] as Style;
                    break;
                case TextSize.Large:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Large"] as Style;
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.ExtraLarge"] as Style;
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Normal"] as Style;
                    break;
            }

            switch (textBlock.TextColor)
            {
                case TextColor.Accent:
                    uiTextBlock.Foreground = resources["Adaptive.AccentBrush"] as Brush;
                    break;
                case TextColor.Attention:
                    uiTextBlock.Foreground = resources["Adaptive.AttentionBrush"] as Brush;
                    break;
                case TextColor.Dark:
                    uiTextBlock.Foreground = resources["Adaptive.DarkBrush"] as Brush;
                    break;
                case TextColor.Good:
                    uiTextBlock.Foreground = resources["Adaptive.GoodBrush"] as Brush;
                    break;
                case TextColor.Light:
                    uiTextBlock.Foreground = resources["Adaptive.LightBrush"] as Brush;
                    break;
                case TextColor.Warning:
                    uiTextBlock.Foreground = resources["Adaptive.WarningBrush"] as Brush;
                    break;
                case TextColor.Default:
                default:
                    uiTextBlock.Foreground = resources["Adaptive.DefaultBrush"] as Brush;
                    break;
            }

            switch (textBlock.TextWeight)
            {
                case TextWeight.Bolder:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.BolderFontWeight"];
                    break;
                case TextWeight.Lighter:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.LighterFontWeight"];
                    break;
                case TextWeight.Normal:
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
        public UIElement Render(Adaptive.Schema.Net.Image image)
        {
            var uiImage = new System.Windows.Controls.Image();
            // uiImage.Margin = this.Theme.ImageMargins;

            uiImage.Source = new BitmapImage(new Uri(image.Url));
            System.Windows.HorizontalAlignment alignment;
            if (Enum.TryParse<System.Windows.HorizontalAlignment>(image.HorizontalAlignment.ToString(), out alignment))
                uiImage.HorizontalAlignment = alignment;
            // How do  I figure image size???
            // image.Size = Schema.Net.Size.
            string style = $"Adaptive.Image";
            if (image.Size != null)
                style += $".{image.Size.ToString()}";

            if (image.Style == ImageStyle.Person)
                style += $".{image.Style.ToString()}";
            uiImage.Style = resources[style] as Style;
            return uiImage;
        }

    }

    public class ActionEventArgs : EventArgs
    {
        public ActionEventArgs()
        { }

        /// <summary>
        /// The action that fired
        /// </summary>
        public ActionBase Action { get; set; }

        /// <summary>
        /// Data for Input controls (if appropriate)
        /// </summary>
        public object Data { get; set; }
    }


}