using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// A container for grouping columns together
    /// </summary>
    public class ColumnGroup : CardElement
    {
        public ColumnGroup() { }

        /// <summary>
        /// Columns that are part of this group
        /// </summary>
        public List<Column> Columns { get; set; } = new List<Column>();
    }
}
