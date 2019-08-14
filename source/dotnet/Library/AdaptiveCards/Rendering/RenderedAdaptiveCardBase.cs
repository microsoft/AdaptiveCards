// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
        /// Provides access to the input fields on a card
        /// </summary>
        public RenderedAdaptiveCardInputs UserInputs { get; set; } = new RenderedAdaptiveCardInputs();

        protected RenderedAdaptiveCardBase(AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? throw new ArgumentNullException(nameof(warnings));
            OriginatingCard = originatingCard ?? throw new ArgumentNullException(nameof(originatingCard));
        }

    }
}
