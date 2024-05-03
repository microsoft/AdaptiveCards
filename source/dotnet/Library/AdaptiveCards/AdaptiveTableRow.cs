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
        [JsonProperty(Required = Required.Default)]
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


        public override void Add(AdaptiveElement value)
        {
            if (value is AdaptiveTableCell cell)
            {
                Cells.Add(cell);
            }
        }

        /// <summary>
        /// Sets the content flow direction
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public bool? Rtl { get; set; } = null;

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Rtl")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool RtlXml { get { return (Rtl.HasValue) ? Rtl.Value : false; } set { Rtl = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeRtlXml() => this.Rtl.HasValue;
#endif

    }
}
