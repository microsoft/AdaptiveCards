using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of containers (each a container of items)
    /// </summary>
    public class ColumnSet : CardElement
    {
        public const string TYPE = "ColumnSet";

        public ColumnSet()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName = "Column", Type = typeof(Column))]
#endif
        public List<Column> Columns { get; set; } = new List<Column>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }
    }
}