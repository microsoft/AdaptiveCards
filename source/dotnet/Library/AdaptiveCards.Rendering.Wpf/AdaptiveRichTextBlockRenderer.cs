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
            // used to define MaxLines
            StringBuilder totalText = new StringBuilder();
            FontWeight maxTextWeight = FontWeight.FromOpenTypeWeight(context.Config.GetFontWeight(AdaptiveFontStyle.Default, AdaptiveTextWeight.Lighter));
            double maxTextSize = context.Config.GetFontSize(AdaptiveFontStyle.Default, AdaptiveTextSize.Small);

            var uiRichTB = CreateControl(richTB, context);

            foreach (var paragraph in richTB.Paragraphs)
            {
                foreach (var inlineElement in paragraph.Inlines)
                {
                    Inline uiInlineText = FormatInlineTextRun(inlineElement, context);
                    uiRichTB.Inlines.Add(uiInlineText);

                    // Extract data for MaxLines
                    totalText.Append(inlineElement.Text);
                    maxTextWeight = SelectMaxTextWeight(maxTextWeight, uiInlineText.FontWeight);
                    maxTextSize = Math.Max(maxTextSize, uiInlineText.FontSize);
                }
                uiRichTB.Inlines.Add(new LineBreak());
            }

            if (richTB.MaxLines > 0)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                // create hidden textBlock with appropriate linebreaks that we can use to measure the ActualHeight
                // using same style, fontWeight settings as original textblock
                var measureBlock = new TextBlock()
                {
                    Style = uiRichTB.Style,
                    FontWeight = maxTextWeight,
                    FontSize = maxTextSize,
                    Visibility = Visibility.Hidden,
                    TextWrapping = TextWrapping.NoWrap,
                    HorizontalAlignment = System.Windows.HorizontalAlignment.Left,
                    VerticalAlignment = VerticalAlignment.Top,
                    DataContext = richTB.MaxLines
                };

                measureBlock.Inlines.Add(totalText.ToString());

                // bind the real textBlock's Height => MeasureBlock.ActualHeight
                uiRichTB.SetBinding(FrameworkElement.MaxHeightProperty, new Binding()
                {
                    Path = new PropertyPath("ActualHeight"),
                    Source = measureBlock,
                    Mode = BindingMode.OneWay,
                    Converter = new MultiplyConverter(richTB.MaxLines)
                });

                // Add both to a grid so they go as a unit
                uiGrid.Children.Add(measureBlock);

                uiGrid.Children.Add(uiRichTB);
                return uiGrid;

            }

            if (!richTB.IsVisible)
            {
                uiRichTB.Visibility = Visibility.Collapsed;
            }

            return uiRichTB;
        }

        private static Inline FormatInlineTextRun(AdaptiveTextRun textRun, AdaptiveRenderContext context)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new AdaptiveXamlMarkdownRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            // Handle Date/Time parsing
            string text = RendererUtilities.ApplyTextFunctions(textRun.Text, context.Lang);

            // Handle markdown
            string xaml = $"<Span  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"  xml:space=\"preserve\">{marked.Parse(text)}</Span>";
            StringReader stringReader = new StringReader(xaml);
            XmlReader xmlReader = XmlReader.Create(stringReader);

            Span uiInlineElement = XamlReader.Load(xmlReader) as Span;
            uiInlineElement.Style = context.GetStyle($"Adaptive.{textRun.Type}");

            uiInlineElement.FontFamily = new FontFamily(context.Config.GetFontFamily(textRun.FontStyle));
            uiInlineElement.FontWeight = FontWeight.FromOpenTypeWeight(context.Config.GetFontWeight(textRun.FontStyle, textRun.Weight));
            uiInlineElement.FontSize = context.Config.GetFontSize(textRun.FontStyle, textRun.Size);

            uiInlineElement.SetColor(textRun.Color, textRun.IsSubtle, context);

            return uiInlineElement;
        }

        private static TextBlock CreateControl(AdaptiveRichTextBlock richTB, AdaptiveRenderContext context)
        {
            TextBlock uiTextBlock = new TextBlock();
            uiTextBlock.Style = context.GetStyle($"Adaptive.{richTB.Type}");
            uiTextBlock.TextWrapping = richTB.Wrap ? TextWrapping.Wrap : TextWrapping.NoWrap;
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
