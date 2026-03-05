// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Config for TextBlock
    /// </summary>
    public class TextBlockConfig
    {
        /// <summary>
        ///  The size of the text
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextSize Size { get; set; } = AdaptiveTextSize.Default;

        /// <summary>
        ///  The weight of the text
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextWeight Weight { get; set; } = AdaptiveTextWeight.Default;

        /// <summary>
        ///  The color of the text
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextColor Color { get; set; } = AdaptiveTextColor.Default;

        /// <summary>
        ///   Should it be subtle?
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public bool IsSubtle { get; set; } = false;

        /// <summary>
        ///  Is it allowed for the text to wrap
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public bool Wrap { get; set; }

        /// <summary>
        /// The maximum width for text
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int MaxWidth { get; set; }
    }
}
