using System;
using System.Globalization;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using Microsoft.MarkedNet;
using System.IO;
using System.Xml;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveRichTextBlockRenderer
    {
        public static FrameworkElement Render(AdaptiveRichTextBlock richTB, AdaptiveRenderContext context)
        {
            var uiRichTB = CreateControl(richTB, context);

            foreach (var inlineElement in richTB.Inlines)
            {
                AdaptiveTextRun textRun = inlineElement as AdaptiveTextRun;
                Inline uiInlineText = FormatInlineTextRun(textRun, context);
                uiRichTB.Inlines.Add(uiInlineText);
            }
            uiRichTB.Inlines.Add(new LineBreak());

            return uiRichTB;
        }

        private static Inline FormatInlineTextRun(AdaptiveTextRun textRun, AdaptiveRenderContext context)
        {
            // Handle Date/Time parsing
            string text = RendererUtilities.ApplyTextFunctions(textRun.Text, context.Lang);

            Span uiInlineElement = new Span();
            uiInlineElement.Inlines.Add(text);

            uiInlineElement.Style = context.GetStyle($"Adaptive.{textRun.Type}");

            uiInlineElement.FontFamily = new FontFamily(context.Config.GetFontFamily(textRun.FontStyle));
            uiInlineElement.FontWeight = FontWeight.FromOpenTypeWeight(context.Config.GetFontWeight(textRun.FontStyle, textRun.Weight));
            uiInlineElement.FontSize = context.Config.GetFontSize(textRun.FontStyle, textRun.Size);

            if (textRun.Italic)
            {
                uiInlineElement.FontStyle = FontStyles.Italic;
            }

            if (textRun.Strikethrough)
            {
                uiInlineElement.TextDecorations = TextDecorations.Strikethrough;
            }

            uiInlineElement.SetColor(textRun.Color, textRun.IsSubtle, context);

            return uiInlineElement;
        }

        private static TextBlock CreateControl(AdaptiveRichTextBlock richTB, AdaptiveRenderContext context)
        {
            TextBlock uiTextBlock = new TextBlock();
            uiTextBlock.Style = context.GetStyle($"Adaptive.{richTB.Type}");
            uiTextBlock.TextWrapping = TextWrapping.Wrap;
            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

            if (richTB.HorizontalAlignment != AdaptiveHorizontalAlignment.Left)
            {
                System.Windows.TextAlignment alignment;
                if (Enum.TryParse<System.Windows.TextAlignment>(richTB.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.TextAlignment = alignment;
            }

            return uiTextBlock;
        }

        private static FontWeight SelectMaxTextWeight(FontWeight first, FontWeight second)
        {
            return (first > second) ? first : second;
        }

        private class MultiplyConverter : IValueConverter
        {
            private int multiplier;

            public MultiplyConverter(int multiplier)
            {
                this.multiplier = multiplier;
            }

            public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
            {
                return (double)value * this.multiplier;
            }

            public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
            {
                return (double)value * this.multiplier;
            }
        }
    }
}
