// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
            AdaptiveAction selectAction = null;
            if (element is AdaptiveCollectionElement)
            {
                selectAction = (element as AdaptiveCollectionElement).SelectAction;

            }
            else if (element is AdaptiveImage)
            {
                selectAction = (element as AdaptiveImage).SelectAction;
            }

            if (selectAction != null)
            {
                return context.RenderSelectAction(selectAction, uiElement);
            }

            return uiElement;
        }

    }
}
