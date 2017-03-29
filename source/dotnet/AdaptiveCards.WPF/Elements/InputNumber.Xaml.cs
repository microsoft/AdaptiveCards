using System.Windows;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// Input.Number
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(InputNumber input, RenderContext context)
        {
            if (this.Options.SupportInteraction)
            {
                var textBox = new TextBox() { Text = input.Value };
                textBox.Text = input.Placeholder;
                textBox.Style = this.GetStyle($"Adaptive.Input.Text.Number");
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
                return Render(container, context);
            }
        }
    }
}