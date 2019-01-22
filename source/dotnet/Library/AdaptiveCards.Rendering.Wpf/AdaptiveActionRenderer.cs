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
                    if (action is AdaptiveToggleVisibilityAction toggleVisibilityAction)
                    {
                        foreach (object targetElement in toggleVisibilityAction.TargetElements)
                        {
                            string targetElementId = "";
                            bool? targetElementIsVisible = null;

                            if (targetElement is string targetElementString)
                            {
                                targetElementId = targetElementString;
                            }
                            else if (targetElement is AdaptiveTargetElement targetElementObject)
                            {
                                targetElementId = targetElementObject.ElementId;
                                targetElementIsVisible = targetElementObject.IsVisible;
                            }

                            var element = LogicalTreeHelper.FindLogicalNode(context.CardRoot, targetElementId);

                            if (element != null && element is FrameworkElement elementFrameworkElement)
                            {
                                Visibility visibility = elementFrameworkElement.Visibility;
                                // if we read something with the format {"elementId": <id>", "isVisible": true} or we just read the id and the element is not visible
                                if ((targetElementIsVisible.HasValue && targetElementIsVisible.Value) || (!targetElementIsVisible.HasValue && visibility != Visibility.Visible))
                                {
                                    elementFrameworkElement.Visibility = Visibility.Visible;
                                }
                                // otherwise if we read something with the format {"elementId": <id>", "isVisible": false} or we just read the id and the element is visible
                                else if ((targetElementIsVisible.HasValue && !targetElementIsVisible.Value) || (!targetElementIsVisible.HasValue && visibility == Visibility.Visible))
                                {
                                    elementFrameworkElement.Visibility = Visibility.Collapsed;
                                }

                            }

                        }
                    }
                    else
                    {
                        context.InvokeAction(uiButton, new AdaptiveActionEventArgs(action));
                    }

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

            if (!String.IsNullOrWhiteSpace(action.Sentiment))
            {
                Style sentimentStyle = context.GetStyle($"Adaptive.{action.Type}.{action.Sentiment}");

                if (sentimentStyle == null && String.Equals(action.Sentiment, "positive", StringComparison.OrdinalIgnoreCase))
                {
                    sentimentStyle = context.GetStyle("PositiveActionDefaultStyle");
                }
                else if (sentimentStyle == null && String.Equals(action.Sentiment, "destructive", StringComparison.OrdinalIgnoreCase))
                {
                    sentimentStyle = context.GetStyle("DestructiveActionDefaultStyle");
                }

                uiButton.Style = sentimentStyle;
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
                FontSize = context.Config.GetFontSize(AdaptiveFontStyle.Default, AdaptiveTextSize.Default),
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
