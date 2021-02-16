// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

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

                    // Prevent nested events from triggering
                    e.Handled = true;
                };
                return uiButton;
            }
            return null;
        }

        public static Button CreateActionButton(AdaptiveAction action, AdaptiveRenderContext context)
        {
            var uiButton = new Button
            {
                Style = context.GetStyle($"Adaptive.{action.Type}"),
            };

            if (!String.IsNullOrWhiteSpace(action.Style))
            {
                Style style = context.GetStyle($"Adaptive.Action.{action.Style}");

                if (style == null && String.Equals(action.Style, "positive", StringComparison.OrdinalIgnoreCase))
                {
                    style = context.GetStyle("PositiveActionDefaultStyle");
                }
                else if (style == null && String.Equals(action.Style, "destructive", StringComparison.OrdinalIgnoreCase))
                {
                    style = context.GetStyle("DestructiveActionDefaultStyle");
                }

                uiButton.Style = style;
            }

            var contentStackPanel = new StackPanel();

            if (!context.IsRenderingSelectAction)
            {
                // Only apply padding for normal card actions
                uiButton.Padding = new Thickness(6, 4, 6, 4);
            }
            else
            {
                // Remove any extra spacing for selectAction
                uiButton.Padding = new Thickness(0, 0, 0, 0);
                contentStackPanel.Margin = new Thickness(0, 0, 0, 0);
            }
            uiButton.Content = contentStackPanel;
            FrameworkElement uiIcon = null;

            var uiTitle = new TextBlock
            {
                Text = action.Title,
                FontSize = context.Config.GetFontSize(AdaptiveFontType.Default, AdaptiveTextSize.Default),
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

            if (!context.IsRenderingSelectAction)
            {
                contentStackPanel.Children.Add(uiTitle);
            }
            else
            {
                uiButton.ToolTip = uiTitle;
            }

            string name = context.GetType().Name.Replace("Action", String.Empty);
            return uiButton;
        }

    }
}
