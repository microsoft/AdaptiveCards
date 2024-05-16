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
    [XmlType(TypeName = AdaptiveFactSet.TypeName)]
    public class AdaptiveFactSet : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "FactSet";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// A collection of Facts to this FactSet contains.
        /// </summary>
        [JsonRequired]
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Fact")]
        public List<AdaptiveFact> Facts { get; set; } = new List<AdaptiveFact>();
    }
}
