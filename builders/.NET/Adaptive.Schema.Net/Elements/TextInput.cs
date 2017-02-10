using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Element which collects text from the user
    /// </summary>
    public class TextInput : Input
    {
        public TextInput()
        {
        }

        /// <summary>
        /// Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        TextInputStyle? Style { get; set; }

        /// <summary>
        /// true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        bool? IsMultiline { get; set; }

        /// <summary>
        /// hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        int? MaxLength { get; set; }

        /// <summary>
        /// hint of minimum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        string Min { get; set; }

        /// <summary>
        /// hint of maximum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        string Max { get; set; }

        /// <summary>
        /// hint of step value(may be ignored by some clients)   
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        int? Step { get; set; }
    }
}