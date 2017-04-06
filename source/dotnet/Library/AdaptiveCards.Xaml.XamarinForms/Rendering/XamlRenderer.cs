using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using AdaptiveCards.Rendering;
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;

namespace AdaptiveCards.Rendering
{
   public partial class XamlRenderer
    {
        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public View RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, CardStyling styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Styling = styling ?? this.DefaultStyling
            };
            return Render(card, context);
        }

        public View RenderShowCard(ActionShowCard showCard, Func<string, MemoryStream> imageResolver = null, CardStyling styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Styling = styling ?? this.DefaultStyling
            };
            return Render(showCard.Card, context);
        }
    }
}
