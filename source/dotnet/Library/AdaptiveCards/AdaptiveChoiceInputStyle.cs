// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    /// The style of ChoiceInput to display.
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveChoiceInputStyle
    {
        /// <summary>
        /// Compact display similar to a ComboBox.
        /// </summary>
        Compact,

        /// <summary>
        /// Expanded display i.e. Checkbox or Radio buttons.
        /// </summary>
        Expanded
    }
}
