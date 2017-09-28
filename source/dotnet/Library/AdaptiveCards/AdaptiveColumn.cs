using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Column
    /// </summary>
    public class AdaptiveColumn : AdaptiveContainer
    {
        public new const string TYPE = "Column";

        public AdaptiveColumn()
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
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get; set; }

        /// <summary>
        ///     Width for the column (either ColumnWidth string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Width { get; set; }
    }

    [Obsolete("Use AdaptiveColumn instead")]
    public class Column : AdaptiveColumn { }
}