using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public class Input : CardElement
    {
        public Input()
        { }

        [JsonRequired]
        public string Id { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get; set; }
    }
}
