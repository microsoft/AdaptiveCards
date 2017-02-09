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
    public class Action : CardElement
    {
        public Action() { }

        /// <summary>
        /// Name of the action
        /// </summary>
        [JsonRequired]
        public string Name { get; set; } 
    }
}
