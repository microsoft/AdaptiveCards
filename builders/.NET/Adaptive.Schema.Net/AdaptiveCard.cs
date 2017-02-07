using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Adaptive card which has flexible container
    /// </summary>
    public class AdaptiveCard : TypedElement
    {
        public AdaptiveCard() { }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

        public List<CardElement> Body { get; set; } = new List<CardElement>();
    }
}
