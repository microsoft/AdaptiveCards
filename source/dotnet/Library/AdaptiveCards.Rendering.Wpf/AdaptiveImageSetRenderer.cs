using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveImageSetRenderer
    {
        public static FrameworkElement Render(AdaptiveImageSet imageSet, AdaptiveRenderContext context)
        {
            var uiImageSet = new ListBox();
            uiImageSet.BorderThickness = new Thickness(0);
            uiImageSet.Background = new SolidColorBrush(Colors.Transparent);
            ScrollViewer.SetHorizontalScrollBarVisibility(uiImageSet, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiImageSet.ItemsPanel = itemsPanelTemplate;            

            uiImageSet.Style = context.GetStyle("Adaptive.ImageSet");
            foreach (var image in imageSet.Images)
            {
                if (image.Size == AdaptiveImageSize.Auto)
                    if (imageSet.ImageSize != AdaptiveImageSize.Auto)
                        image.Size = imageSet.ImageSize;
                    else
                        image.Size = context.Config.ImageSet.ImageSize;

                var uiImage = context.Render(image);
                uiImageSet.Add(uiImage);
            }
            return uiImageSet;

        }
    }
}