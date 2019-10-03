using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering.Forms
{
    class AdaptiveColumnRenderer
    {

        public static View Render(AdaptiveColumn column, AdaptiveRenderContext context)
        {
            Grid cardContainer = new Grid();

            AdaptiveCardRenderer.AddContainerElements(cardContainer, column.Items, context);

            return cardContainer;
        }

    }
}
