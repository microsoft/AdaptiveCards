// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the backgroundImage property
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTableColumnDefinition.TypeName)]
#endif
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTableColumnDefinition
    {
        /// <summary>
        /// The JSON property name that this class implements.
        /// </summary>
        public const string TypeName = "TableColumnDefinition";

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalContentAlignment), "leading")]
        public AdaptiveHorizontalContentAlignment HorizontalContentAlignment { get; set; }

        /// <summary>
        /// Explicit Column width.
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("pixelWidth", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelWidth { get; set; }

        /// <summary>
        /// Relative Column width.
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("width", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint Width { get; set; }
    }
}
