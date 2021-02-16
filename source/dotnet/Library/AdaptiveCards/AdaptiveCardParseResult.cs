// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards
{
    /// <summary>
    /// The result of parsing an AdaptiveCard from JSON.
    /// </summary>
    public class AdaptiveCardParseResult
    {
        /// <summary>
        /// The parsed card object.
        /// </summary>
        public AdaptiveCard Card { get; set; }

        /// <summary>
        /// A collection of any warnings that might have been encountered when parsing the card.
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();
    }
}
