using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        public AdaptiveCard OriginatingCard { get; private set; }

        protected RenderedAdaptiveCardBase(AdaptiveCard originatingCard)
        {
            OriginatingCard = originatingCard ?? throw new ArgumentNullException(nameof(originatingCard));
        }
    }
}
