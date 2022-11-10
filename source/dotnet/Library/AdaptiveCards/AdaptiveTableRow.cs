// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Collections;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.ComponentModel;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents TableRow element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTableRow.TypeName)]
#endif
    public class AdaptiveTableRow : AdaptiveCollectionWithContentAlignment 
    {
        /// <inheritdoc />
        public const string TypeName = "TableRow";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Collection of TableCells that this TableRow contains.
        /// </summary>

        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveTableCell), ElementName = AdaptiveTableCell.TypeName)]
#endif
        public List<AdaptiveTableCell> Cells{ get; set; } = new List<AdaptiveTableCell>();

        /// <inheritdoc/>
        public override IEnumerator<AdaptiveElement> GetEnumerator()
        {
            return Cells.GetEnumerator(); 
        }

        /// <summary>
        /// The style used to display this element. See <see cref="AdaptiveContainerStyle" />.
        /// </summary>
        [JsonConverter(typeof(IgnoreNullEnumConverter<AdaptiveContainerStyle>), true)]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Style")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public AdaptiveContainerStyle StyleXml { get { return (Style.HasValue) ? Style.Value : AdaptiveContainerStyle.Default; } set { Style = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeStyleXml() => this.Style.HasValue;
#endif

        /// <summary>
        /// Sets the content flow direction
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public bool? Rtl { get; set; } = null;
    }
}
