using System.Collections.Generic;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     The FactSet element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    [XmlType(TypeName = AdaptiveFactSet.TypeName)]
    public class AdaptiveFactSet : AdaptiveElement
    {
        public const string TypeName = "FactSet";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Fact")]
        public List<AdaptiveFact> Facts { get; set; } = new List<AdaptiveFact>();
    }
}