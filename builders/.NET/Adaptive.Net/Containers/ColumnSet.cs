using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Adaptive
{
    /// <summary>
    /// A set of columns (each column is a container of items)
    /// </summary>
    public partial class ColumnSet : CardElement
    {
        public ColumnSet() { }

        /// <summary>
        /// Columns that are part of this group
        /// </summary>
        [JsonRequired]
        [XmlElement(ElementName="Column", Type=typeof(Column))]
        public List<Column> Columns { get; set; } = new List<Column>();
    }
}
