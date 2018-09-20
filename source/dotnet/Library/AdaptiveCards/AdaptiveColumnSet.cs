using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveColumnSet.TypeName)]
#endif
    public class AdaptiveColumnSet : AdaptiveElement
    {
        public const string TypeName = "ColumnSet";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveColumn), ElementName = AdaptiveColumn.TypeName)]
#endif
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }
    }
}