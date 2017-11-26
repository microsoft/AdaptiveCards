using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveActionRenderer
    {
        public static FrameworkElement Render(AdaptiveAction action, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity && context.ActionHandlers.IsSupported(action.GetType()))
            {
                var uiButton = CreateActionButton(action, context);
                uiButton.Click += (sender, e) =>
                {
                    context.InvokeAction(uiButton, new AdaptiveActionEventArgs(action));
                };
                return uiButton;
            }
            return null;
        }

        public static Button CreateActionButton(AdaptiveAction action, AdaptiveRenderContext context)
        {
            var uiButton = new Button
            {
                //HorizontalAlignment = HorizontalAlignment.Stretch,
                Style = context.GetStyle($"Adaptive.{action.Type}"),
                Padding = new Thickness(6, 4, 6, 4),
                Content = new TextBlock
                {
                    Text = action.Title,
                    FontSize = context.Config.FontSizes.Default,
                    Style = context.GetStyle($"Adaptive.Action.Title")
                }
            };

            string name = context.GetType().Name.Replace("Action", String.Empty);
            return uiButton;

        }
    }
}