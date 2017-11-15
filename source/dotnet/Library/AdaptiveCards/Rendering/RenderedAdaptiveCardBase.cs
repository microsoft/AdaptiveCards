using System;
using System.Collections.Generic;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// The base class for RenderedAdaptiveCard. Renderers extend this class to provide their native UI element property.
    /// </summary>
    public abstract class RenderedAdaptiveCardBase
    {
        /// <summary>
        /// The card that the visual was rendered from.
        /// </summary>
        public AdaptiveCard OriginatingCard { get; }

        /// <summary>
        /// If any modifications were done to the rendered card they will be reported here
        /// </summary>
        public IList<AdaptiveWarning> Warnings { get; }

        /// <summary>
        /// Input bindings associated with this card. Used to get input values from any controls
        /// </summary>
        public IDictionary<string, Func<string>> InputBindings { get; set; } = new Dictionary<string, Func<string>>();

        public RenderedAdaptiveCardInputs UserInputs { get; set; }


        protected RenderedAdaptiveCardBase(AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? throw new ArgumentNullException(nameof(warnings));
            OriginatingCard = originatingCard ?? throw new ArgumentNullException(nameof(originatingCard));
            UserInputs = new RenderedAdaptiveCardInputs(this);
        }

    }
}
