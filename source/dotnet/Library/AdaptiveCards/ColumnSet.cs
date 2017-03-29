using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns (each column is a container of items)
    /// </summary>
    public class ColumnSet : CardElement
    {
        public ColumnSet()
        {
            Type = "ColumnSet";
        }

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
#if DESKTOP
        [XmlElement(ElementName = "Column", Type = typeof(Column))]
#endif
        public List<Column> Columns { get; set; } = new List<Column>();
    }
}