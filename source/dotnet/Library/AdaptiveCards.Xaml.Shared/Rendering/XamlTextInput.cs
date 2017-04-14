using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlTextInput : TextInput , IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// this.Text
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = this.Value };
                if (this.IsMultiline == true)
                {
                    textBox.AcceptsReturn = true;
#if WPF
                    textBox.TextWrapping = TextWrapping.Wrap;
                    textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
#elif XAMARIN 
                    // TODO 
#endif
                }
#if WPF
                if (this.MaxLength > 0)
                    textBox.MaxLength = this.MaxLength;
#elif XAMARIN 
                    // TODO 
#endif
                textBox.Text = this.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.this.Text.{this.Style}");
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