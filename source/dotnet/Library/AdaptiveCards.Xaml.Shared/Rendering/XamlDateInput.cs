using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlDateInput : DateInput, IRender<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// this.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = this.Value };
                textBox.Text = this.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.this.Text.Date");
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
                if (this.Value != null)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = this.Value;
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }
        }
    }
}