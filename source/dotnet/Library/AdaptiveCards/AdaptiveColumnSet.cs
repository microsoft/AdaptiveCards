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
    [XmlType(TypeName = AdaptiveColumnSet.TypeName)]
    public class AdaptiveColumnSet : AdaptiveCollectionElement
    {
        /// <inheritdoc />
        public const string TypeName = "ColumnSet";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Collection of Columns that this ColumnSet contains.
        /// </summary>
        [JsonRequired]
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <inheritdoc/>
        public override IEnumerator<AdaptiveElement> GetEnumerator()
        {
            return Columns.GetEnumerator();
        }

        /// <inheritdoc/>
        public override void Add(AdaptiveElement element)
        {
            if (element is AdaptiveColumn)
            {
                Columns.Add(element as AdaptiveColumn);
            }
        }
    }
}
