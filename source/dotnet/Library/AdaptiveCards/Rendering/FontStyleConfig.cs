// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// FontStyle config
    /// </summary>
    public class FontStyleConfig
    {
        /// <summary>
        /// Font family 
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string FontFamily { get; set; }

        /// <summary>
        /// FontSizes Config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        /// <summary>
        /// FontWeights config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();
    }
}
