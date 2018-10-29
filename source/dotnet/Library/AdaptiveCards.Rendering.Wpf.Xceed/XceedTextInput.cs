using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedTextInput
    {
        public static FrameworkElement Render(AdaptiveTextInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new WatermarkTextBox() { Text = input.Value };
                if (input.IsMultiline == true)
                {
                    textBox.AcceptsReturn = true;
                    textBox.TextWrapping = TextWrapping.Wrap;
                    textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
                }
                if (input.MaxLength > 0)
                    textBox.MaxLength = input.MaxLength;

                textBox.Watermark = input.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.{input.Style}");
                textBox.DataContext = input;
                context.InputBindings.Add(input.Id, () => textBox.Text);
                if (input.InlineAction != null)
                {
                    if (context.Config.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline &&
                        input.InlineAction.GetType() == typeof(AdaptiveShowCardAction))
                    {
                        context.Warnings.Add(new AdaptiveWarning(-1, "Inline ShowCard not supported for InlineAction"));
                    }
                    else
                    {
                        if (input.InlineAction.Title.Length != 0 && input.InlineAction.IconUrl != null && input.InlineAction.IconUrl.Length != 0)
                        {
                            // need to create tool tip
                            input.InlineAction.Title = null;
                        }
                        var actionRenderer = context.ElementRenderers.Get(input.InlineAction.GetType());
                        bool temp = context.IsRenderingSelectAction;
                        context.IsRenderingSelectAction = true;
                        var actionRendered = actionRenderer.Invoke(input.InlineAction, context);
                        var parentView = new Grid();
                        parentView.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                        context.IsRenderingSelectAction = temp;

                        Grid.SetColumn(textBox, 0);
                        
                        parentView.Children.Add(textBox);

                        textBox.Loaded += (sender, e) => 
                        {
                            actionRendered.Height = textBox.ActualHeight;
                        };

                        parentView.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        Grid.SetColumn(actionRendered, 1);
                        parentView.Children.Add(actionRendered);
                        return parentView;
                    }
                }

                return textBox;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }
        }
    }
}
