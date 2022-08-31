// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the ColumnSet element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveColumnSet.TypeName)]
#endif
    public class AdaptiveColumnSet : AdaptiveCollectionElement
    {
        /// <inheritdoc />
        public const string TypeName = "ColumnSet";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Collection of Columns that this ColumnSet contains.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
#endif
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <summary>
        /// Determines how to align the background image horizontally.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// Determines how to align the background image vertically.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalAlignment), "top")]
        public AdaptiveVerticalAlignment VerticalAlignment { get; set; }
    }
}
