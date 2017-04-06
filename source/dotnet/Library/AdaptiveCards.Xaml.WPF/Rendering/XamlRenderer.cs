using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using AdaptiveCards.Rendering;
using System.Windows.Markup;

namespace AdaptiveCards.Rendering
{
   public partial class XamlRenderer
    {
        
        public XamlRenderer(RenderOptions options,
            string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options)
        {
            using (var styleStream = File.OpenRead(stylePath))
            {
                Resources = (ResourceDictionary)XamlReader.Load(styleStream);
            }
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
        }

        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public FrameworkElement RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, CardStyling styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Styling = styling ?? this.DefaultStyling
            };
            return Render(card, context);
        }

        public FrameworkElement RenderShowCard(ActionShowCard showCard, Func<string, MemoryStream> imageResolver = null, CardStyling styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Styling = styling ?? this.DefaultStyling
            };

            return Render(showCard.Card, context);
        }
    }
}
