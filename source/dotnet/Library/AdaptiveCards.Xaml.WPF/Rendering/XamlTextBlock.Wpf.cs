using System;
using System.IO;
using System.Xml;
using MarkedNet;
using System.Windows;
using System.Windows.Markup;
using System.Windows.Media;

namespace AdaptiveCards.Rendering
{

    public static partial class XamlTextBlock
    {
        public static System.Windows.Controls.TextBlock CreateControl(TextBlock textBlock, RenderContext context)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new MarkedXamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string text = RendererUtilities.ApplyTextFunctions(textBlock.Text);
            // uiTextBlock.Text = textBlock.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);

            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = context.GetStyle($"Adaptive.{textBlock.Type}");

            uiTextBlock.FontFamily = new FontFamily(context.Options.FontFamily);

            uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            switch (textBlock.Weight)
            {
                case TextWeight.Bolder:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(700);
                    break;
                case TextWeight.Lighter:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(300);
                    break;
                case TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(400);
                    break;
            }

            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

            if (textBlock.HorizontalAlignment != HorizontalAlignment.Left)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            if (textBlock.Wrap)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            
            return uiTextBlock;
        }
    }
}
