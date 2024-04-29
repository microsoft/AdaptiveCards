// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections;
using System.Collections.Generic;
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
        /// Horizontal alignment (<see cref="AdaptiveHorizontalAlignment"/>) to use.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// Collection of Columns that this ColumnSet contains.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
#endif
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

		/// <summary>
        /// Gets or sets the padding.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        public AdaptivePadding Padding { get; set; }

        public override IEnumerator<AdaptiveElement> GetEnumerator()
        {
            return Columns.GetEnumerator();
        }

        public override void Add(AdaptiveElement element)
        {
            if (element is AdaptiveColumn)
            {
                Columns.Add(element as AdaptiveColumn);
            }
        }
    }
}
