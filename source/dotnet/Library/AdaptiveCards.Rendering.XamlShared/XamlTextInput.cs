using System.Windows;
using System.Windows.Controls;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlTextInput
    {
        public static FrameworkElement Render(TextInput input, RenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value };
                if (input.IsMultiline == true)
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
                if (input.MaxLength > 0)
                    textBox.MaxLength = input.MaxLength;
#elif XAMARIN 
                    // TODO 
#endif
                textBox.SetPlaceholder (input.Placeholder);
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.{input.Style}");
                textBox.SetContext(input);
                context.InputBindings.Add(input.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                Container container = TypedElementConverter.CreateElement<Container>();
                container.Separation = input.Separation;
                TextBlock textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                container.Items.Add(textBlock);
                if (input.Value != null)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = input.Value;
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }

        }
    }
}