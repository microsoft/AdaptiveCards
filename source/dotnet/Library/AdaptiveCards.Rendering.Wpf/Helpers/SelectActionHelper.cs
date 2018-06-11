using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveRenderContextExtensions
    {
        public static FrameworkElement RenderSelectAction(this AdaptiveRenderContext context, AdaptiveAction selectAction, FrameworkElement uiElement)
        {
            if (context.Config.SupportsInteractivity)
            {
                var uiButton = (Button) context.Render(selectAction);

                // Stretch both the button and button's content to avoid empty spaces
                uiButton.HorizontalAlignment = HorizontalAlignment.Stretch;
                uiButton.HorizontalContentAlignment = HorizontalAlignment.Stretch;

                // Adopt the child element's background to parent and set the child's background
                // to be transparent in order for button's on mouse hover color to work properly
                if (uiElement is Panel p)
                {
                    uiButton.Background = p.Background;
                    p.Background = new SolidColorBrush(Colors.Transparent);
                }
                uiButton.BorderThickness = new Thickness(0);
                uiButton.Content = uiElement;
                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                return uiButton;
            }

            return uiElement;
        }
    }
}