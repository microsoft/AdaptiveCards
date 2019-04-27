// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards.Rendering.Html
{
    /// <summary>
    /// The rendered Adaptive Card result.
    /// </summary>
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(HtmlTag htmlTag, AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings)
            : base(originatingCard, warnings)
        {
            Html = htmlTag;
        }

        /// <summary>
        /// The rendered HTML for the card
        /// </summary>
        public HtmlTag Html { get; }
    }
}
