using System;
using System.Globalization;
using System.IO;
using System.Xml;
using MarkedNet;
using System.Collections.Generic;
using System.Linq;
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

    public class XamlTextBlock : TextBlock, IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
#if WPF
            Marked marked = new Marked();
            marked.Options.Renderer = new MarkedXamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string text = RendererUtilities.ApplyTextFunctions(this.Text);
            // uiTextBlock.Text = this.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);

            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = context.GetStyle($"Adaptive.{this.Type}");

            uiTextBlock.FontFamily = new FontFamily(context.Options.AdaptiveCard.FontFamily);

            ColorOption colorOption;
            switch (this.Color)
            {
                case TextColor.Accent:
                    colorOption = context.Options.Colors.Accent;
                    break;
                case TextColor.Attention:
                    colorOption = context.Options.Colors.Attention;
                    break;
                case TextColor.Dark:
                    colorOption = context.Options.Colors.Dark;
                    break;
                case TextColor.Good:
                    colorOption = context.Options.Colors.Good;
                    break;
                case TextColor.Light:
                    colorOption = context.Options.Colors.Light;
                    break;
                case TextColor.Warning:
                    colorOption = context.Options.Colors.Warning;
                    break;
                case TextColor.Default:
                default:
                    colorOption = context.Options.Colors.Default;
                    break;
            }
            if (this.IsSubtle == true)
                uiTextBlock.Foreground = context.GetColorBrush(colorOption.Subtle);
            else 
                uiTextBlock.Foreground = context.GetColorBrush(colorOption.Normal);

            uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            switch (this.Weight)
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

            if (this.HorizontalAlignment != HorizontalAlignment.Left)
            {
                System.Windows.HorizontalAlignment alignment;
                if (Enum.TryParse<System.Windows.HorizontalAlignment>(this.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            if (this.Wrap)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;

#elif XAMARIN
            var uiTextBlock = new Xamarin.Forms.TextBlock();
            uiTextBlock.Text = RendererUtilities.ApplyTextFunctions(this.Text);
            uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock");
            // TODO: confirm text trimming
            uiTextBlock.LineBreakMode = LineBreakMode.TailTruncation;

            switch (this.HorizontalAlignment)
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

            


            uiTextBlock.TextColor = context.Resources.TryGetValue<Color>($"Adaptive.{this.Color}");

            if (this.Weight == TextWeight.Bolder)
                uiTextBlock.FontAttributes = FontAttributes.Bold;

            if (this.Wrap == true)
                uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;
#endif


            switch (this.Size)
            {
                case TextSize.Small:
                    uiTextBlock.FontSize = context.Options.TextBlock.FontSize.Small;
                    break;
                case TextSize.Medium:
                    uiTextBlock.FontSize = context.Options.TextBlock.FontSize.Medium;
                    break;
                case TextSize.Large:
                    uiTextBlock.FontSize = context.Options.TextBlock.FontSize.Large;
                    break;
                case TextSize.ExtraLarge:
                    uiTextBlock.FontSize = context.Options.TextBlock.FontSize.ExtraLarge;
                    break;
                case TextSize.Normal:
                default:
                    uiTextBlock.FontSize = context.Options.TextBlock.FontSize.Normal;
                    break;
            }


            if (this.MaxLines > 0)
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
