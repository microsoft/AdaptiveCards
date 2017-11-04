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
        public AdaptiveCard OriginatingCard { get; }

        /// <summary>
        /// If any modifications were done to the rendered card they will be reported here
        /// </summary>
        public IList<AdaptiveWarning> Warnings { get; }
        
        protected RenderedAdaptiveCardBase(AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? throw new ArgumentNullException(nameof(warnings));
            OriginatingCard = originatingCard ?? throw new ArgumentNullException(nameof(originatingCard));
        }
    }
}
