// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of media
    /// </summary>
    public class InputsConfig
    {

        /// <summary>
        /// LabelConfig config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public LabelConfig Label { get; set; } = new LabelConfig();

        /// <summary>
        /// ErrorMessage config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public ErrorMessageConfig ErrorMessage { get; set; } = new ErrorMessageConfig();
    }
}
