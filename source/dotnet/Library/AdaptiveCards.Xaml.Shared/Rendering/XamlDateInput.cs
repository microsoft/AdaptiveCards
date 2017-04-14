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
                Container container = new Container() { Separation = this.Separation };
                container.Items.Add(new TextBlock() { Text = XamlUtilities.GetFallbackText(this) ?? this.Placeholder });
                if (this.Value != null)
                {
                    container.Items.Add(new TextBlock()
                    {
                        Text = this.Value,
                        Color = TextColor.Accent,
                        Wrap = true
                    });
                }
                return context.Render(container);
            }
        }
    }
}