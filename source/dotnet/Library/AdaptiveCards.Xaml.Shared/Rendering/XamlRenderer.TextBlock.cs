using System;
using System.Globalization;
using System.IO;
using System.Xml;
using MarkedNet;
using System.Collections.Generic;
#if WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{

    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
#if WPF
        private static Dictionary<string, SolidColorBrush> colors = new Dictionary<string, SolidColorBrush>();

        public SolidColorBrush GetColorBrush(string color)
        {
            lock(colors)
            {
                if (colors.TryGetValue(color, out var brush))
                    return brush;
                brush = new SolidColorBrush((Color)ColorConverter.ConvertFromString(color));
                colors[color] = brush;
                return brush;
            }
        }
#elif XAMARIN
        // TODO
        public object GetColorBrush(string color)
        {
            return null;
        }
#endif

        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(TextBlock textBlock, RenderContext context)
        {

#if WPF
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
            uiTextBlock.Style = this.GetStyle($"Adaptive.{textBlock.Type}");

            uiTextBlock.FontFamily = new FontFamily(context.Styling.TextBlock.FontFamily);

            switch (textBlock.Color)
            {
                case TextColor.Accent:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorAccent);
                    break;
                case TextColor.Attention:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorAttention);
                    break;
                case TextColor.Dark:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorDark);
                    break;
                case TextColor.Default:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorDefault);
                    break;
                case TextColor.Good:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorGood);
                    break;
                case TextColor.Light:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorLight);
                    break;
                case TextColor.Warning:
                    uiTextBlock.Foreground = GetColorBrush(context.Styling.TextBlock.ColorWarning);
                    break;
            }
            uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            switch (textBlock.Weight)
            {
                case TextWeight.Bolder:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(context.Styling.TextBlock.FontWeightBolder);
                    break;
                case TextWeight.Lighter:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(context.Styling.TextBlock.FontWeightLighter);
                    break;
                case TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(context.Styling.TextBlock.FontWeightNormal);
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

#elif XAMARIN
            var uiTextBlock = new Xamarin.Forms.TextBlock();
            uiTextBlock.Text = RendererUtilities.ApplyTextFunctions(textBlock.Text);
            uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock");
            // TODO: confirm text trimming
            uiTextBlock.LineBreakMode = LineBreakMode.TailTruncation;

            switch (textBlock.HorizontalAlignment)
            {
                case HorizontalAlignment.Left:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Start;
                    break;

                case HorizontalAlignment.Center:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Center;
                    break;

                case HorizontalAlignment.Right:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.End;
                    break;
            }


            if (this.Resources[$"Adaptive.{textBlock.Color}"] != null)
                uiTextBlock.TextColor = (Color)this.Resources[$"Adaptive.{textBlock.Color}"];

            if (textBlock.Weight == TextWeight.Bolder)
                uiTextBlock.FontAttributes = FontAttributes.Bold;

            if (textBlock.Wrap == true)
                uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;
#endif


            switch (textBlock.Size)
            {
                case TextSize.Small:
                    uiTextBlock.FontSize = context.Styling.TextBlock.FontSizeSmall;
                    break;
                case TextSize.Medium:
                    uiTextBlock.FontSize = context.Styling.TextBlock.FontSizeMedium;
                    break;
                case TextSize.Large:
                    uiTextBlock.FontSize = context.Styling.TextBlock.FontSizeLarge;
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.FontSize = context.Styling.TextBlock.FontSizeExtraLarge;
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.FontSize = context.Styling.TextBlock.FontSizeNormal;
                    break;
            }

            if (textBlock.IsSubtle == true)
                uiTextBlock.Opacity = context.Styling.TextBlock.IsSubtleOpacity;


            if (textBlock.MaxLines > 0)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

#if WPF
                // create hidden textBlock with appropriate linebreaks that we can use to measure the ActualHeight
                // using same style, fontWeight settings as original textblock
                var measureBlock = new System.Windows.Controls.TextBlock()
                {
                    Style = uiTextBlock.Style,
                    FontWeight = uiTextBlock.FontWeight,
                    Visibility = Visibility.Hidden,
                    TextWrapping = TextWrapping.NoWrap,
                    HorizontalAlignment = System.Windows.HorizontalAlignment.Left,
                    VerticalAlignment = VerticalAlignment.Top,
                    DataContext = textBlock.MaxLines
                };

                measureBlock.Inlines.Add(uiTextBlock.Text);

                // bind the real textBlock's Height => MeasureBlock.ActualHeight
                uiTextBlock.SetBinding(Control.MaxHeightProperty, new Binding()
                {
                    Path = new PropertyPath("ActualHeight"),
                    Source = measureBlock,
                    Mode = BindingMode.OneWay,
                    Converter = new MultiplyConverter(textBlock.MaxLines)
                });

                // Add both to a grid so they go as a unit
                uiGrid.Children.Add(measureBlock);
#elif XAMARIN
                // TODO 
#endif
                uiGrid.Children.Add(uiTextBlock);
                return uiGrid;

            }

            return uiTextBlock;
        }
    }

    class MultiplyConverter : IValueConverter
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
