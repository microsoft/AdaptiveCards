// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// The style of ChoiceInput to display.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveChoiceInputStyle>), true)]
    public enum AdaptiveChoiceInputStyle
    {
        /// <summary>
        /// Compact display similar to a ComboBox.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("compact")]
#endif
        Compact,

        /// <summary>
        /// Expanded display i.e. Checkbox or Radio buttons.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("expanded")]
#endif
        Expanded,

        /// <summary>
        /// Allows users to filter choices in a choice set.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("filtered")]
#endif
        Filtered
    }
}
