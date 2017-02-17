using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Input which collects a choice between two options from the user
    /// </summary>
    public class InputToggle: Input
    {
        public InputToggle()
        {
        }

        /// <summary>
        /// Title text for option1
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        public string Title1 { get; set; }

        /// <summary>
        /// Title text for option2
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        public string Title2 { get; set; }

        /// <summary>
        /// Value text for option1
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        public string Value1 { get; set; }

        /// <summary>
        /// Value text for option2
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        public string Value2 { get; set; }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        public string Value { get; set; }
    }
}