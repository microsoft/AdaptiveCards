using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public class XamlExTextInput : TextInput, IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// this.Text
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public  FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new WatermarkTextBox() { Text = this.Value };
                if (this.IsMultiline == true)
                {
                    textBox.AcceptsReturn = true;
                    textBox.TextWrapping = TextWrapping.Wrap;
                    textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
                }
                if (this.MaxLength > 0)
                    textBox.MaxLength = this.MaxLength;

                textBox.Watermark = this.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.{this.Style}");
                textBox.DataContext = this;
                context.InputBindings.Add(this.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                var textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(this) ?? this.Placeholder;
                return context.Render(textBlock);
            }
        }
    }
}