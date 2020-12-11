// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
        /// Collection of Columns that this ColumnSet contains.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
#endif
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();
    }
}
