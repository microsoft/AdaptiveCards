// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Table element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = TypeName)]
#endif
    public class AdaptiveTable : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "Table";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// CDefines the number of columns in the table, their sizes, and more.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveTableColumn), ElementName = AdaptiveTableColumn.TypeName)]
#endif
        public List<AdaptiveTableColumn> Columns { get; set; } = new List<AdaptiveTableColumn>();

        /// <summary>
        /// CDefines the number of columns in the table, their sizes, and more.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveTableRow), ElementName = AdaptiveTableRow.TypeName)]
#endif
        public List<AdaptiveTableRow> Rows { get; set; } = new List<AdaptiveTableRow>();

        /// <summary>
        /// Determines how to align the cell horizontally.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalCellContentAlignment { get; set; }

        /// <summary>
        /// Determines how to align the cell vertically.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalAlignment), "top")]
        public AdaptiveVerticalAlignment VerticalCellContentAlignment { get; set; }

        /// <summary>
        /// Specifies whether the first row of the table should be treated as a header row, and be announced as such by accessibility software.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(true)]
        public bool FirstRowAsHeader { get; set; }

        /// <summary>
        /// Specifies whether grid lines should be displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(true)]
        public bool ShowGridLines { get; set; }

        /// <summary>
        /// Defines the style of the grid. This property currently only controls the grid's color.s
        /// </summary>
        [JsonConverter(typeof(IgnoreNullEnumConverter<AdaptiveContainerStyle>), true)]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? GridStyle { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Style")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public AdaptiveContainerStyle StyleXml { get { return (GridStyle.HasValue) ? GridStyle.Value : AdaptiveContainerStyle.Default; } set { GridStyle = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeStyleXml() => this.GridStyle.HasValue;
#endif
    }
}
