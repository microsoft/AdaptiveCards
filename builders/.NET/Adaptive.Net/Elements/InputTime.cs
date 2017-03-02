using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Adaptive
{
    /// <summary>
    /// Input which collects Time from the user
    /// </summary>
    public partial class InputTime : Input
    {
        public InputTime()
        {
        }

        /// <summary>
        /// Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Placeholder { get; set; }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        /// hint of minimum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Min { get; set; }

        /// <summary>
        /// hint of maximum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Max { get; set; }
    }
}