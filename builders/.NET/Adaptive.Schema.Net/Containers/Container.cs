using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Container for a collection of elements
    /// </summary>
    public class Container : CardElement
    {
        public Container()
        { }

        [JsonRequired]
        public List<CardElement> Items { get; set; } = new List<CardElement>();

        /// <summary>
        /// Image to use for the background of a card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundImageUrl { get; set; }

        /// <summary>
        /// Background color to use for the card as RGB string
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundColor { get; set; }

        /// <summary>
        /// Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public Action Action { get; set; }

        /// <summary>
        /// Actions for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public List<Action> Actions { get; set; } = new List<Action>();

        /// <summary>
        /// visually separate this container from preiovus or pending containers
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparationStyle? Separation { get; set; }
    }
}
