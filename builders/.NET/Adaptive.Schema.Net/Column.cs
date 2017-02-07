using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// A column container inside of a columngroup
    /// </summary>
    public class Column : Container
    {
        public Column() { }

        /// <summary>
        /// Size which is either Auto|Stretch|Small|Medium|Large| or a number
        /// </summary>
        public string Size { get; set; }
    }
}
