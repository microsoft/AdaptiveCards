using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// A set of columns (each column is a container of items)
    /// </summary>
    public class ColumnSet : CardElement
    {
        public ColumnSet() { }

        /// <summary>
        /// Columns that are part of this group
        /// </summary>
        [JsonRequired]
        public List<Column> Columns { get; set; } = new List<Column>();
    }
}
