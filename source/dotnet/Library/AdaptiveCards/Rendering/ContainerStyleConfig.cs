// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Class ContainersStyleConfig
    /// </summary>
    public class ContainerStyleConfig
    {
        /// <summary>
        /// The background color to use for this container
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// The font colors to use for this container
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public ForegroundColorsConfig ForegroundColors { get; set; } = new ForegroundColorsConfig();
    }
}
