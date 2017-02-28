using System;
using System.Globalization;
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
    public partial class TextBlock
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<TextBlock, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            Marked marked = new Marked();
            marked.Options.Renderer = new MarkedXamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string text = Utilities.ApplyTextFunctions(this.Text);

            // uiTextBlock.Text = this.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);
            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock");
            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

            if (this.HorizontalAlignment != HorizontalAlignment.Left)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(this.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            switch (this.Size)
            {
                case TextSize.Small:
                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Small"); ;
                    break;
                case TextSize.Medium:
                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Medium"); ;
                    break;
                case TextSize.Large:
                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Large"); ;
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.ExtraLarge"); ;
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Normal"); ;
                    break;
            }

            switch (this.Color)
            {
                case TextColor.Accent:
                    uiTextBlock.Foreground = context.Resources["Adaptive.AccentBrush"] as Brush;
                    break;
                case TextColor.Attention:
                    uiTextBlock.Foreground = context.Resources["Adaptive.AttentionBrush"] as Brush;
                    break;
                case TextColor.Dark:
                    uiTextBlock.Foreground = context.Resources["Adaptive.DarkBrush"] as Brush;
                    break;
                case TextColor.Good:
                    uiTextBlock.Foreground = context.Resources["Adaptive.GoodBrush"] as Brush;
                    break;
                case TextColor.Light:
                    uiTextBlock.Foreground = context.Resources["Adaptive.LightBrush"] as Brush;
                    break;
                case TextColor.Warning:
                    uiTextBlock.Foreground = context.Resources["Adaptive.WarningBrush"] as Brush;
                    break;
                case TextColor.Default:
                default:
                    uiTextBlock.Foreground = context.Resources["Adaptive.DefaultBrush"] as Brush;
                    break;
            }

            switch (this.Weight)
            {
                case TextWeight.Bolder:
                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.BolderFontWeight"];
                    break;
                case TextWeight.Lighter:
                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.LighterFontWeight"];
                    break;
                case TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.NormalFontWeight"];
                    break;
            }

            if (this.IsSubtle == true)
                uiTextBlock.Opacity = (double)context.Resources["Adaptive.IsSubtleOpacity"];

            if (this.Wrap == true)
            {
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
                if (this.MaxLines > 0)
                {
                    var uiGrid = new Grid();
                    uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

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
                        DataContext = this.MaxLines
                    };

                    measureBlock.Inlines.Add(uiTextBlock.Text);

                    // bind the real textBlock's Height => MeasureBlock.ActualHeight
                    uiTextBlock.SetBinding(Control.MaxHeightProperty, new Binding()
                    {
                        Path = new PropertyPath("ActualHeight"),
                        Source = measureBlock,
                        Mode = BindingMode.OneWay,
                        Converter = new MultiplyConverter(this.MaxLines)
                    });

                    // Add both to a grid so they go as a unit
                    uiGrid.Children.Add(measureBlock);
                    uiGrid.Children.Add(uiTextBlock);
                    return uiGrid;
                }
            }
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;
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
