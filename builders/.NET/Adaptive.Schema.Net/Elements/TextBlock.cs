using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    public class TextBlock : CardElement
    {
        public TextBlock() 
        {

        }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize? Size { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight? Weight { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor? Color { get; set; } 

        [JsonRequired]
        public string Text { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? IsSubtle { get; set; } 

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? Wrap { get; set; } 

    }
}
