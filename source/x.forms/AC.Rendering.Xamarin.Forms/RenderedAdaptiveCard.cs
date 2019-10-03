using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering.Forms
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(
            View view,
            AdaptiveCard originatingCard,
            IList<AdaptiveWarning> warnings,
            IDictionary<string, Func<string>> inputBindings)
            : base(originatingCard, warnings)
        {
            View = view;
            // UserInputs = new RenderedAdaptiveCardInputs(inputBindings);
        }

        /// <summary>
        /// The rendered card
        /// </summary>
        public View View { get; }
    }
}
