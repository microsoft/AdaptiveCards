using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Column
    /// </summary>
    public class Column : Container
    {
        public new const string TYPE = "Column";

        public Column()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Size { get; set; }
    }
}