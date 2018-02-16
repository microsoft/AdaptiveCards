using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns
    /// </summary>
    [XmlType(TypeName = AdaptiveColumnSet.TypeName)]
    public class AdaptiveColumnSet : AdaptiveElement
    {
        public const string TypeName = "ColumnSet";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }
    }
}