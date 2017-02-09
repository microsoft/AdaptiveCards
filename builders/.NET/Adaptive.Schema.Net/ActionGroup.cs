using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// A container for grouping columns together
    /// </summary>
    public class ActionGroup : CardElement
    {
        public ActionGroup() { }

        /// <summary>
        /// Columns that are part of this group
        /// </summary>
        [JsonRequired]
        public List<Action> Actions { get; set; } = new List<Action>();
    }
}
