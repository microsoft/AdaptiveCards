using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Base class for all elements in a container
    /// </summary>
    public class CardItem : TypedElement
    {
        public CardItem() : base()
        {
        }

        /// <summary>
        /// SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

        /// <summary>
        /// Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public HorizontalAlignment? HorizontalAlignment { get; set; }
    }
}


