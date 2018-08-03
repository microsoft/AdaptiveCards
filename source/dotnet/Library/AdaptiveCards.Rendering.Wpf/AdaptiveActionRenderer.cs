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
            };

            var contentStackPanel = new StackPanel();
            uiButton.Content = contentStackPanel;
            FrameworkElement uiIcon = null;

            var uiTitle = new TextBlock
            {
                Text = action.Title,
                FontSize = context.Config.FontSizes.Default,
                Style = context.GetStyle($"Adaptive.Action.Title")
            };

            if (action.IconUrl != null)
            {
                var actionsConfig = context.Config.Actions;

                var image = new AdaptiveImage(action.IconUrl)
                {
                    HorizontalAlignment = AdaptiveHorizontalAlignment.Center
                };
                uiIcon = AdaptiveImageRenderer.Render(image, context);
                if (actionsConfig.IconPlacement == IconPlacement.AboveTitle)
                {
                    contentStackPanel.Orientation = Orientation.Vertical;
                    uiIcon.Height = (double)actionsConfig.IconSize;
                }
                else
                {
                    contentStackPanel.Orientation = Orientation.Horizontal;
                    //Size the image to the textblock, wait until layout is complete (loaded event)
                    uiIcon.Loaded += (sender, e) =>
                    {
                        uiIcon.Height = uiTitle.ActualHeight;
                    };
                }
                contentStackPanel.Children.Add(uiIcon);

                // Add spacing for the icon for horizontal actions
                if (actionsConfig.IconPlacement == IconPlacement.LeftOfTitle)
                {
                    int spacing = context.Config.GetSpacing(AdaptiveSpacing.Default);
                    var uiSep = new Grid
                    {
                        Style = context.GetStyle($"Adaptive.VerticalSeparator"),
                        VerticalAlignment = VerticalAlignment.Stretch,
                        Width = spacing,
                    };
                    contentStackPanel.Children.Add(uiSep);
                }
            }

            contentStackPanel.Children.Add(uiTitle);

            string name = context.GetType().Name.Replace("Action", String.Empty);
            return uiButton;
        }
    }
}