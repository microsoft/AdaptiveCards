using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Column
    /// </summary>
    [XmlType(TypeName = AdaptiveColumn.TypeName)]
    public class AdaptiveColumn : AdaptiveContainer
    {
        public new const string TypeName = "Column";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get; set; }

        /// <summary>
        ///     Width for the column (either ColumnWidth string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Width { get; set; } // TODO: this should be a ColumnWidth type with implict converter
    }
}