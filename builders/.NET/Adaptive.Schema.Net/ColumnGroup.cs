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

        // ISSUE? Should this be called columns, it only can take Column elements, right?
        public List<Column> Items { get; set; } = new List<Column>();
    }
}
