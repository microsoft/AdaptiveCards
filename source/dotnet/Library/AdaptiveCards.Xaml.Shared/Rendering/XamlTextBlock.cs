using System;
using System.Globalization;
using System.IO;
using System.Xml;
using Microsoft.MarkedNet;
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
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{

    public static partial class XamlTextBlock
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveTextBlock textBlock = (AdaptiveTextBlock)element;
            var uiTextBlock = CreateControl(textBlock, context);

            /*
            TextBlockConfig colorOption;
            switch (textBlock.Color)
            {
                case AdaptiveTextColor.Accent:
                    colorOption = context.Config.ContainerStyles.T   .Colors.Accent;
                    break;
                case AdaptiveTextColor.Attention:
                    colorOption = context.Config.Colors.Attention;
                    break;
                case AdaptiveTextColor.Dark:
                    colorOption = context.Config.Colors.Dark;
                    break;
                case AdaptiveTextColor.Good:
                    colorOption = context.Config.Colors.Good;
                    break;
                case AdaptiveTextColor.Light:
                    colorOption = context.Config.Colors.Light;
                    break;
                case AdaptiveTextColor.Warning:
                    colorOption = context.Config.Colors.Warning;
                    break;
                case AdaptiveTextColor.Default:
                default:
                    colorOption = context.Config.Colors.Default;
                    break;
            }

            if (textBlock.IsSubtle == true)
                uiTextBlock.SetColor(colorOption.Subtle, context);
            else
                uiTextBlock.SetColor(colorOption.Normal, context);
            */

            uiTextBlock.FontSize = context.Config.GetFontSize(textBlock.FontType, textBlock.Size);

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
