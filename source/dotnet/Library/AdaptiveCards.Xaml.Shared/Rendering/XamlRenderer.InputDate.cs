using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        /// <summary>
        /// Input.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderInputDate(TypedElement element, RenderContext context)
        {
            DateInput input = (DateInput)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value };
                textBox.Text = input.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.Date");
                textBox.DataContext = input;
                context.InputControls.Add(textBox);
                return textBox;
            }
            else
            {
                Container container = new Container() { Separation = input.Separation };
                container.Items.Add(new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder });
                if (input.Value != null)
                {

                    container.Items.Add(new TextBlock()
                    {
                        Text = input.Value,
                        Color = TextColor.Accent,
                        Wrap = true
                    });
                }
                return context.Render(container);
            }
        }
    }
}