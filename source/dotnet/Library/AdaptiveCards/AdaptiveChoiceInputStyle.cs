// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveChoiceInputStyle
    {
        /// <summary>
        ///     choices are prefered to be compactly displayed. Example: ComboBox
        /// </summary>
        Compact,

        /// <summary>
        ///     choices are prefered to be displayed for easy input. Example: Checkbox or Radio buttons
        /// </summary>
        Expanded
    }
}
