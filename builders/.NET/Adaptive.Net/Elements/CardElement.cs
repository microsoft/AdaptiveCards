using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace Adaptive
{
    /// <summary>
    /// Base class for all elements in a container
    /// </summary>
    public partial class CardElement : TypedElement
    {
        public CardElement() : base()
        {
        }

        /// <summary>
        /// SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

    }
}


