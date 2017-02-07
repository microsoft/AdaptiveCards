using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using Adapative = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    class AdapativeRenderer
    {
        public UIElement Render(Adapative.AdaptiveCard card)
        {
            return Render(card.Body);
        }

        private UIElement RenderUnknownElement(Adapative.CardElement element)
        {
            if (element is Adapative.Container)
            {
                return Render(element as Adapative.Container);
            }
            else if (element is Adapative.ColumnGroup)
            {
                return Render(element as Adapative.Container);
            }
            else if (element is Adapative.ImageGallery)
            {
                return Render(element as Adapative.ImageGallery);
            }
            else if (element is Adapative.FactGroup)
            {
                return Render(element as Adapative.FactGroup);
            }
            else if (element is Adapative.TextBlock)
            {
                return Render(element as Adapative.TextBlock);
            }
            else if (element is Adapative.Input)
            {
                return Render(element as Adapative.Input);
            }
            else if (element is Adapative.Image)
            {
                return Render(element as Adapative.Image);
            }
            else if (element is Adapative.Seperator)
            {
                return Render(element as Adapative.Seperator);
            }

            return null;
        }

        public UIElement Render(Adapative.Container container)
        {
            var body = new Grid();
            int iRow = 0;
            foreach (var cardElement in container.Items)
            {
                UIElement itemElement = RenderUnknownElement(cardElement);
                body.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(itemElement, iRow++);
            }
            return body;
        }

        public UIElement Render(Adapative.ColumnGroup columnGroup)
        {
            var body = new Grid();
            int iRow = 0;
            foreach (var column in columnGroup.Columns)
            {
                UIElement itemElement = RenderCardElement(cardElement);
                body.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(itemElement, iRow++);
            }
            return body;
        }
    }
}
