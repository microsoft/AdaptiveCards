// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// FactSetConfig
    /// </summary>
    public class FactSetConfig
    {

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public TextBlockConfig Title { get; set; } = new TextBlockConfig() { Size = AdaptiveTextSize.Default, Color = AdaptiveTextColor.Default, IsSubtle = false, Weight = AdaptiveTextWeight.Bolder, Wrap = true, MaxWidth = 150 };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public TextBlockConfig Value { get; set; } = new TextBlockConfig() { Size = AdaptiveTextSize.Default, Color = AdaptiveTextColor.Default, IsSubtle = false, Weight = AdaptiveTextWeight.Default, Wrap = true };

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 10;
    }
}
