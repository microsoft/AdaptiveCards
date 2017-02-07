using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// The FactGroup element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class FactGroup : CardElement
    {
        public FactGroup()
        { }

        /// <summary>
        /// The facts to be displayed.
        /// </summary>
        [JsonRequired]
        public List<Fact> Facts { get; set; } = new List<Fact>();
    }
}
