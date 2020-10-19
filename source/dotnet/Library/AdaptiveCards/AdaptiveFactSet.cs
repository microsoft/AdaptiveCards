// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the FactSet element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveFactSet.TypeName)]
#endif
    public class AdaptiveFactSet : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "FactSet";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// A collection of Facts to this FactSet contains.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Fact")]
#endif
        public List<AdaptiveFact> Facts { get; set; } = new List<AdaptiveFact>();
    }
}
