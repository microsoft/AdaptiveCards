using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlImageSet
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveImageSet imageSet = (AdaptiveImageSet)element;
#if WPF
            var uiImageSet = new ListBox();
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
