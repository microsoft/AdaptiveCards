using System.Windows;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// ImageSet
        /// </summary>
        /// <param name="imageSet"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(ImageSet imageSet, RenderContext context)
        {
#if WPF
            var uiImageSet = new ListBox();
            uiImageSet.Style = this.GetStyle("Adaptive.ImageSet");

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
                var uiImage = this.Render(image, context);
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