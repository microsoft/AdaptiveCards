// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     The FactSet element makes it simple to display a series of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveFactSet.TypeName)]
#endif
    public class AdaptiveFactSet : AdaptiveElement
    {
        public const string TypeName = "FactSet";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Fact")]
#endif
        public List<AdaptiveFact> Facts { get; set; } = new List<AdaptiveFact>();
    }
}
