using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Input which collects text from the user
    /// </summary>
    public partial class InputText : Input
    {
        public InputText()
        {
            this.Type = "Input.Text";
        }

        /// <summary>
        /// Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Placeholder { get; set; }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        /// Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public TextInputStyle Style { get; set; }

        /// <summary>
        /// true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public bool IsMultiline { get; set; }

        /// <summary>
        /// hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public int MaxLength { get; set; }

        public bool ShouldSerializeIsMultiline() { return this.IsMultiline; }

    }
}