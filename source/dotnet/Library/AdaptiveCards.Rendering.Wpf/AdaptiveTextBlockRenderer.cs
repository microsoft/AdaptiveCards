using System;
using System.Globalization;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using System.Xml;
using Microsoft.MarkedNet;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveTextBlockRenderer
    {
        public static FrameworkElement Render(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            var uiTextBlock = CreateControl(textBlock, context);

            FontColorConfig colorOption;
            switch (textBlock.Color)
            {
                case AdaptiveTextColor.Accent:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Accent;
                    break;
                case AdaptiveTextColor.Attention:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Attention;
                    break;
                case AdaptiveTextColor.Dark:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Dark;
                    break;
                case AdaptiveTextColor.Good:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Good;
                    break;
                case AdaptiveTextColor.Light:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Light;
                    break;
                case AdaptiveTextColor.Warning:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Warning;
                    break;
                case AdaptiveTextColor.Default:
                default:
                    colorOption = context.Config.ContainerStyles.Default.ForegroundColors.Default;
                    break;
            }

            if (textBlock.IsSubtle)
                uiTextBlock.SetColor(colorOption.Subtle, context);
            else
                uiTextBlock.SetColor(colorOption.Default, context);

            switch (textBlock.Size)
            {
                case AdaptiveTextSize.Small:
                    uiTextBlock.FontSize = context.Config.FontSizes.Small;
                    break;
                case AdaptiveTextSize.Medium:
                    uiTextBlock.FontSize = context.Config.FontSizes.Medium;
                    break;
                case AdaptiveTextSize.Large:
                    uiTextBlock.FontSize = context.Config.FontSizes.Large;
                    break;
                case AdaptiveTextSize.ExtraLarge:
                    uiTextBlock.FontSize = context.Config.FontSizes.ExtraLarge;
                    break;
                case AdaptiveTextSize.Default:
                default:
                    uiTextBlock.FontSize = context.Config.FontSizes.Default;
                    break;
            }


            if (textBlock.MaxLines > 0)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });


                // create hidden textBlock with appropriate linebreaks that we can use to measure the ActualHeight
                // using same style, fontWeight settings as original textblock
                var measureBlock = new TextBlock()
                {
                    Style = uiTextBlock.Style,
                    FontWeight = uiTextBlock.FontWeight,
                    FontSize = uiTextBlock.FontSize,
                    Visibility = Visibility.Hidden,
                    TextWrapping = TextWrapping.NoWrap,
                    HorizontalAlignment = System.Windows.HorizontalAlignment.Left,
                    VerticalAlignment = VerticalAlignment.Top,
                    DataContext = textBlock.MaxLines
                };

                measureBlock.Inlines.Add(uiTextBlock.Text);

                // bind the real textBlock's Height => MeasureBlock.ActualHeight
                uiTextBlock.SetBinding(FrameworkElement.MaxHeightProperty, new Binding()
                {
                    Path = new PropertyPath("ActualHeight"),
                    Source = measureBlock,
                    Mode = BindingMode.OneWay,
                    Converter = new MultiplyConverter(textBlock.MaxLines)
                });

                // Add both to a grid so they go as a unit
                uiGrid.Children.Add(measureBlock);

                uiGrid.Children.Add(uiTextBlock);
                return uiGrid;

            }

            return uiTextBlock;
        }

        private static TextBlock CreateControl(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new AdaptiveXamlMarkdownRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string text = RendererUtilities.ApplyTextFunctions(textBlock.Text);
            // uiTextBlock.Text = textBlock.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);

            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = context.GetStyle($"Adaptive.{textBlock.Type}");

            uiTextBlock.FontFamily = new FontFamily(context.Config.FontFamily);
            uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            switch (textBlock.Weight)
            {
                case AdaptiveTextWeight.Bolder:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(700);
                    break;
                case AdaptiveTextWeight.Lighter:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(300);
                    break;
                case AdaptiveTextWeight.Default:
                default:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(400);
                    break;
            }

            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

            if (textBlock.HorizontalAlignment != AdaptiveHorizontalAlignment.Left)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            if (textBlock.Wrap)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;

            return uiTextBlock;
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
