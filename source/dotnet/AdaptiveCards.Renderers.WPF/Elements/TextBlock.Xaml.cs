using System;
using System.Globalization;
using System.IO;
using System.Xml;
#if WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using MarkedNet;
#elif Xamarin
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Renderers
{

    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {


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

            uiTextBlock.Foreground = this.Resources[$"Adaptive.{textBlock.Color}Brush"] as Brush;
            uiTextBlock.TextWrapping = TextWrapping.NoWrap;

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

            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

            if (textBlock.HorizontalAlignment != HorizontalAlignment.Left)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            if (textBlock.Wrap)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;

#elif Xamarin
            var uiTextBlock = new Label();
            uiTextBlock.Text = Text;
            uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock");
            // TODO: confirm text trimming
            uiTextBlock.LineBreakMode = LineBreakMode.TailTruncation;

            switch (HorizontalAlignment)
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


            if (this.Resources[$"Adaptive.{Color}"] != null)
                uiTextBlock.TextColor = (Color)this.Resources[$"Adaptive.{Color}"];

            if (Weight == TextWeight.Bolder)
                uiTextBlock.FontAttributes = FontAttributes.Bold;

            if (textBlock.Wrap == true)
                uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;

#endif


            switch (textBlock.Size)
            {
                case TextSize.Small:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Small");
                    break;
                case TextSize.Medium:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Medium");
                    break;
                case TextSize.Large:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Large");
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.ExtraLarge");
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.Style = this.GetStyle("Adaptive.TextBlock.Normal");
                    break;
            }

            if (textBlock.IsSubtle == true)
                uiTextBlock.Opacity = (double)this.Resources["Adaptive.IsSubtleOpacity"];


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
