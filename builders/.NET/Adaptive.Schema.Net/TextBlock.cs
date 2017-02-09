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
        public TextSize? TextSize { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight? TextWeight { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor? TextColor { get; set; } 

        [JsonRequired]
        public string Text { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? IsSubtle { get; set; } 

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? Wrap { get; set; } 

    }
}
