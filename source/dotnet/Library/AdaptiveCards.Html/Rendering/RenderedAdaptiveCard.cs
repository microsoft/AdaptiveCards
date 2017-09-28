using AdaptiveCards.Rendering;
using HtmlTags;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// The rendered Adaptive Card result.
    /// </summary>
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(HtmlTag htmlTag, AdaptiveCard originatingCard)
            : base(originatingCard: originatingCard)
        {
            HtmlTag = htmlTag;
        }

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary>
        public HtmlTag HtmlTag { get; private set; }
    }
}
