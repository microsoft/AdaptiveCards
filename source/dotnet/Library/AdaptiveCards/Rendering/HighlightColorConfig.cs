// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Configuration for HightlightColors
    /// </summary>
    public class HighlightColorConfig
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public HighlightColorConfig()
        {
            this.Default = this.Subtle = "#FFFFFF00";
        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public string Default { get; set; }

        /// <summary>
        /// Color config for subtle highlight
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public string Subtle { get; set; }
    }
}
