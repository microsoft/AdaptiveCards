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
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            ImageSet imageSet = (ImageSet)element;
#if WPF
            var uiImageSet = new ListBox();
            uiImageSet.Style = context.GetStyle("Adaptive.ImageSet");

            ScrollViewer.SetHorizontalScrollBarVisibility(uiImageSet, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiImageSet.ItemsPanel = itemsPanelTemplate;

            foreach (var image in imageSet.Images)
            {
                if (imageSet.ImageSize != ImageSize.Auto)
                    image.Size = imageSet.ImageSize;
                var uiImage = context.Render(image);
                uiImageSet.Items.Add(uiImage);
            }
            return uiImageSet;
#elif XAMARIN
            // TODO: xamarin imageset support
            return new Grid();
#endif

        }
    }
}