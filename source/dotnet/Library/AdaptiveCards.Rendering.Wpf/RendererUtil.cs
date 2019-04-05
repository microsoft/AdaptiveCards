using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AdaptiveCards.Rendering.Wpf
{
    static class RendererUtil
    {
        public static void ApplyMinHeight(FrameworkElement uiElement, AdaptiveElement element)
        {
            if (element.PixelMinHeight > 0)
            {
                uiElement.MinHeight = element.PixelMinHeight;
            }
        }

        public static void ApplyIsVisible(FrameworkElement uiElement, AdaptiveElement element)
        {
            if (!element.IsVisible)
            {
                uiElement.Visibility = Visibility.Collapsed;
            }
        }

        public static void ApplyVerticalContentAlignment(FrameworkElement uiElement, AdaptiveCollectionElement element)
        {
            switch (element.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiElement.VerticalAlignment = VerticalAlignment.Center;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiElement.VerticalAlignment = VerticalAlignment.Bottom;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }
        }

        public static FrameworkElement ApplySelectAction(FrameworkElement uiElement, AdaptiveElement element, AdaptiveRenderContext context)
        {
            if (element is AdaptiveCollectionElement)
            {
                AdaptiveCollectionElement collectionElement = element as AdaptiveCollectionElement;
                if (collectionElement.SelectAction != null)
                {
                    return context.RenderSelectAction(collectionElement.SelectAction, uiElement);
                }
            }
            else if (element is AdaptiveImage)
            {
                AdaptiveImage image = element as AdaptiveImage;
                if (image.SelectAction != null)
                {
                    return context.RenderSelectAction(image.SelectAction, uiElement);
                }
            }

            return uiElement;
        }

    }
}
