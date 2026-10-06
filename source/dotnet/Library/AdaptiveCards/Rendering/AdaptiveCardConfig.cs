// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Contains options for the AdaptiveCard element.
    /// </summary>
    public class AdaptiveCardConfig : AdaptiveConfigBase
    {
        /// <summary>
        /// Determines whether custom styles should be honored.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public bool AllowCustomStyle { get; set; }
    }
}
