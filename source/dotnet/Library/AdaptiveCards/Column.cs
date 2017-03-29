using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A container inside of a ColumnSet
    /// </summary>
    public class Column : Container
    {
        public Column()
        {
            Type = "Column";
        }

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Size { get; set; }
    }
}