using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Adaptive
{
    public partial class ImageSet
    {

        /// <summary>
        /// ImageGallery
        /// </summary>
        /// <param name="imageGallery"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            var uiGallery = new ListBox();
            uiGallery.Style = context.GetStyle("Adaptive.ImageGallery");

            ScrollViewer.SetHorizontalScrollBarVisibility(uiGallery, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiGallery.ItemsPanel = itemsPanelTemplate;

            foreach (var image in this.Images)
            {
                if (this.ImageSize != null)
                    image.Size = this.ImageSize;
                var uiImage = image.Render(context);
                uiGallery.Items.Add(uiImage);
            }
            return uiGallery;
        }
    }
}