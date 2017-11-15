using System.Windows;
using System.Windows.Controls;
using AdaptiveCards;
using AdaptiveCards.Rendering.Wpf;

namespace WpfVisualizer
{
    public class MyCustomRating : AdaptiveElement
    {
        public override string Type => "Rating";

        public double Rating { get; set; }

        public AdaptiveTextSize Size { get; set; }

        public AdaptiveTextColor Color { get; set; }

        public static FrameworkElement Render(MyCustomRating rating, AdaptiveRenderContext context)
        {
            var textBlock = new AdaptiveTextBlock
            {
                Size = rating.Size,
                Color = rating.Color
            };
            for (int i = 0; i < rating.Rating; i++)
            {
                textBlock.Text += "\u2605";
            }
            textBlock.Text += $" ({rating.Rating})";
            return context.Render(textBlock);
        }
    }

    public class MyCustomInput : AdaptiveInput
    {
        public override string Type => "MyCustomInput";    

        public static FrameworkElement Render(MyCustomInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox();

            context.InputBindings.Add(input.Id, () =>
            {
                return textBox.Text;
            });

            return textBox;
        }
    }
}