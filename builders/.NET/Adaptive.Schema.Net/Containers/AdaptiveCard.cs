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

        public List<CardElement> Body { get; set; } = new List<CardElement>();

        /// <summary>
        /// Actions for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();

        /// <summary>
        /// Speak annotation for the card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

        /// <summary>
        /// Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get; set; }
    }
}
