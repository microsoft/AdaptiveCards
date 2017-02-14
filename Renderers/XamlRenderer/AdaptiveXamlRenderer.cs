using System;
using System.IO;
using System.Windows;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Adaptive.Schema.Net;
using AC = Adaptive.Schema.Net;
using System.Text.RegularExpressions;
using System.Windows.Controls;
using System.Collections.Generic;

namespace Adaptive.Renderers
{

    public partial class AdaptiveXamlRenderer
    {
        public AdaptiveXamlRenderer(ResourceDictionary resources)
        {
            this.Resources = resources;
        }

        public delegate void ActionEventHandler(object sender, ActionEventArgs e);

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public event ActionEventHandler OnAction;

        protected ResourceDictionary Resources { get; set; }

        private static Regex _regexDateTime = new Regex(@"\{\{(?<func>DATE|TIME){1}\((?<date>.+?){1}(?:,\s*(?<hint>Short|Long){1}\s*)??\)\}\}", RegexOptions.Compiled | RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase);

        private enum Functions { DATE, TIME };

        private enum TimeHints { LONG, SHORT };

        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
        protected virtual UIElement Render(AC.TextBlock textBlock)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new MarkedXamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string text = textBlock.Text;
            foreach (Match match in _regexDateTime.Matches(text))
            {
                Functions function;
                if (Enum.TryParse<Functions>(match.Groups[1].Value.ToUpper(), out function))
                {
                    DateTime date;
                    if (DateTime.TryParse(match.Groups[2].Value, out date))
                    {
                        TimeHints timeHint;
                        if (!Enum.TryParse<TimeHints>(match.Groups[3].Value.ToUpper(), out timeHint))
                            timeHint = TimeHints.LONG;

                        string dateTimeFormat = "D";
                        if (function == Functions.DATE)
                        {
                            dateTimeFormat = (timeHint == TimeHints.LONG) ? "D" : "d";
                        }
                        else if (function == Functions.TIME)
                        {
                            dateTimeFormat = (timeHint == TimeHints.LONG) ? "T" : "t";
                        }
                        text = text.Replace(match.Value, date.ToString(dateTimeFormat));
                    }
                }
            }

            // uiTextBlock.Text = textBlock.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);
            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock");

            if (textBlock.HorizontalAlignment.HasValue)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            switch (textBlock.Size)
            {
                case TextSize.Small:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Small"); ;
                    break;
                case TextSize.Medium:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Medium"); ;
                    break;
                case TextSize.Large:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Large"); ;
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.ExtraLarge"); ;
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Normal"); ;
                    break;
            }

            switch (textBlock.Color)
            {
                case TextColor.Accent:
                    uiTextBlock.Foreground = this.Resources["Adaptive.AccentBrush"] as Brush;
                    break;
                case TextColor.Attention:
                    uiTextBlock.Foreground = this.Resources["Adaptive.AttentionBrush"] as Brush;
                    break;
                case TextColor.Dark:
                    uiTextBlock.Foreground = this.Resources["Adaptive.DarkBrush"] as Brush;
                    break;
                case TextColor.Good:
                    uiTextBlock.Foreground = this.Resources["Adaptive.GoodBrush"] as Brush;
                    break;
                case TextColor.Light:
                    uiTextBlock.Foreground = this.Resources["Adaptive.LightBrush"] as Brush;
                    break;
                case TextColor.Warning:
                    uiTextBlock.Foreground = this.Resources["Adaptive.WarningBrush"] as Brush;
                    break;
                case TextColor.Default:
                default:
                    uiTextBlock.Foreground = this.Resources["Adaptive.DefaultBrush"] as Brush;
                    break;
            }

            switch (textBlock.Weight)
            {
                case TextWeight.Bolder:
                    uiTextBlock.FontWeight = (FontWeight)this.Resources["Adaptive.BolderFontWeight"];
                    break;
                case TextWeight.Lighter:
                    uiTextBlock.FontWeight = (FontWeight)this.Resources["Adaptive.LighterFontWeight"];
                    break;
                case TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = (FontWeight)this.Resources["Adaptive.NormalFontWeight"];
                    break;
            }

            if (textBlock.Wrap.HasValue && textBlock.Wrap == true)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            if (textBlock.IsSubtle.HasValue && textBlock.IsSubtle == true)
                uiTextBlock.Opacity = (double)this.Resources["Adaptive.IsSubtleOpacity"];
            return uiTextBlock;
        }


        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        protected virtual UIElement Render(Adaptive.Schema.Net.Image image)
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
            uiImage.Style = this.GetStyle(style);
            if (image.Action != null)
            {
                return _renderAction(image.Action, new List<FrameworkElement>(), uiImage);
            }

            return uiImage;
        }

        protected virtual Style GetStyle(string styleName)
        {
            while (!String.IsNullOrEmpty(styleName))
            {
                Style style = this.Resources[styleName] as Style;
                if (style != null)
                    return style;
                var iPos = styleName.LastIndexOf('.');
                if (iPos <= 0)
                    break;
                styleName = styleName.Substring(0, iPos);
            }
            return null;
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