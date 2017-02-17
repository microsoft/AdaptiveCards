using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Input which collects text from the user
    /// </summary>
    public class InputText : Input
    {
        public InputText()
        {
        }

        /// <summary>
        /// Title Description of the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get; set; }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get; set; }

        /// <summary>
        /// Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextInputStyle? Style { get; set; }

        /// <summary>
        /// true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? IsMultiline { get; set; }

        /// <summary>
        /// hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public int? MaxLength { get; set; }
    }
}