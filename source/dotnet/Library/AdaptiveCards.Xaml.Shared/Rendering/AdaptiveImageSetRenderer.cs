// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Media;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveImageSetRenderer
    {
        public static FrameworkElement Render(AdaptiveImageSet imageSet, AdaptiveRenderContext context)
        {
#if WPF
            var uiImageSet = new ListBox();
            uiImageSet.BorderThickness = new Thickness(0);
            uiImageSet.Background = new SolidColorBrush(Colors.Transparent);
            ScrollViewer.SetHorizontalScrollBarVisibility(uiImageSet, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiImageSet.ItemsPanel = itemsPanelTemplate;
#elif XAMARIN
            var uiImageSet = new StackLayout { Orientation = StackOrientation.Vertical };
#endif

            uiImageSet.Style = context.GetStyle("Adaptive.ImageSet");
            foreach (var image in imageSet.Images)
            {
                // Use the imageSize in imageSet for all images if present
                if (imageSet.ImageSize != AdaptiveImageSize.Auto)
                    image.Size = imageSet.ImageSize;
                else if (image.Size == AdaptiveImageSize.Auto)
                    image.Size = context.Config.ImageSet.ImageSize;

                var uiImage = context.Render(image);
                uiImageSet.Add(uiImage);
            }

            return uiImageSet;

        }
    }
}
