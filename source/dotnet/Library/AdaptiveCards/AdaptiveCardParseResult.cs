// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards
{
    public class AdaptiveCardParseResult
    {
        /// <summary>
        /// The parsed card object
        /// </summary>
        public AdaptiveCard Card { get; set; }

        /// <summary>
        /// If any modifications were done to the parsed card they will be reported here
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();
    }
}
