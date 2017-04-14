using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlImageSet : ImageSet, IRender<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// ImageSet
        /// </summary>
        /// <param name="imageSet"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
#if WPF
            var uiImageSet = new ListBox();
            uiImageSet.Style = context.GetStyle("Adaptive.ImageSet");

            ScrollViewer.SetHorizontalScrollBarVisibility(uiImageSet, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiImageSet.ItemsPanel = itemsPanelTemplate;

            foreach (var image in this.Images)
            {
                if (this.ImageSize != ImageSize.Auto)
                    image.Size = this.ImageSize;
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