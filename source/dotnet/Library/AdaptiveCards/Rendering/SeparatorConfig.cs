// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    /// <summary>
    /// Config for seperator
    /// </summary>
    public class SeparatorConfig
    {
        /// <summary>
        /// If there is a visible line, how thick should the line be
        /// </summary>
        public int LineThickness { get; set; } = 1;

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string LineColor { get; set; } = "#FF707070";

    }

}
