using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Choice as part of a MultichoiceInput element
    /// </summary>
    public class Choice 
    {
        public Choice()
        { }

        /// <summary>
        /// Display text for the choice
        /// </summary>
        [JsonRequired]
        public string Display { get; set; }

        /// <summary>
        /// Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
        public string Value { get; set; }

        /// <summary>
        /// (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }
    }
}
