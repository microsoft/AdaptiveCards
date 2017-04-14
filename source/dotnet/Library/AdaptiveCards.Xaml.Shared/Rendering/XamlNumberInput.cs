using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlNumberInput : NumberInput, IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// this.Number
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = this.Value.ToString() };
                textBox.Text = this.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.this.Text.Number");
                textBox.DataContext = this;
                context.InputBindings.Add(this.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                Container container = TypedElementConverter.CreateElement<Container>();
                container.Separation = this.Separation;
                TextBlock textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(this) ?? this.Placeholder;
                container.Items.Add(textBlock);
                if (this.Value != double.NaN)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = this.Value.ToString();
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }
        }
    }
}