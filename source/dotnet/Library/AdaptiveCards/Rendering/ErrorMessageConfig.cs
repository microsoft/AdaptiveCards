// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of media
    /// </summary>
    public class ErrorMessageConfig
    {
        /// <summary>
        ///  The text color of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveSpacing Spacing { get; set; } = AdaptiveSpacing.Default;

        /// <summary>
        ///  The text size of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextSize Size { get; set; } = AdaptiveTextSize.Default;

        /// <summary>
        ///  The text weight of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextWeight Weight { get; set; } = AdaptiveTextWeight.Default;
    }
}
