// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveColumnRenderer
    {
        public static FrameworkElement Render(AdaptiveColumn column, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");
            uiContainer.SetBackgroundSource(column.BackgroundImage, context);

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            // This is the renderArgs that will be passed down to the children
            var childRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

#if WPF
            Border border = new Border();
            border.Child = uiContainer;
#elif XAMARIN
            Frame border = new Frame();
            //Xamarin default this to having a shadow
            //TODO: Confirm this on Xamarin Android
            border.Padding = 0;
            border.HasShadow = false;
            border.BackgroundColor = Color.Transparent;
            border.Content = uiContainer;
#endif

            bool inheritsStyleFromParent = !column.Style.HasValue;
            bool columnHasPadding = false;

            if (!inheritsStyleFromParent)
            {
                columnHasPadding = AdaptiveContainerRenderer.ApplyPadding(border, uiContainer, column, parentRenderArgs, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(column.Style);

#if WPF
                border.Background = context.GetColorBrush(containerStyle.BackgroundColor);
#elif XAMARIN
                border.BackgroundColor = context.GetColor(containerStyle.BackgroundColor);
#endif

                childRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            childRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : column.Style.Value;

            // If the column has no padding or has padding and doesn't bleed, then the children can bleed
            // to the side the column would have bled
            if (columnHasPadding)
            {
                childRenderArgs.BleedDirection = BleedDirection.BleedAll;
            }

            // If either this column or an ancestor had padding, then the children will have an ancestor with padding
            childRenderArgs.HasParentWithPadding = (columnHasPadding || parentRenderArgs.HasParentWithPadding);
            context.RenderArgs = childRenderArgs;

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, column.Items, context);

            RendererUtil.ApplyVerticalContentAlignment(uiContainer, column);

#if WPF
            uiContainer.MinHeight = column.PixelMinHeight;
#elif XAMARIN
            uiContainer.MinimumHeightRequest = column.PixelMinHeight;
#endif

            // Revert context's value to that of outside the Column
            context.RenderArgs = parentRenderArgs;

            return RendererUtil.ApplySelectAction(border, column, context);
        }
    }
}
