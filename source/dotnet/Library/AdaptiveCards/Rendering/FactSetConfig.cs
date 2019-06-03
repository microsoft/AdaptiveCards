// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FactSetConfig
    {

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextBlockConfig Title { get; set; } = new TextBlockConfig() { Size = AdaptiveTextSize.Default, Color = AdaptiveTextColor.Default, IsSubtle = false, Weight = AdaptiveTextWeight.Bolder, Wrap = true, MaxWidth = 150 };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextBlockConfig Value { get; set; } = new TextBlockConfig() { Size = AdaptiveTextSize.Default, Color = AdaptiveTextColor.Default, IsSubtle = false, Weight = AdaptiveTextWeight.Default, Wrap = true };

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 10;
    }
}
