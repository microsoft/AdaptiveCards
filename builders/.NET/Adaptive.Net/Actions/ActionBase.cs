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
    /// Base of Action types
    /// </summary>
    public partial class ActionBase : TypedElement
    {
        public ActionBase() { }

        /// <summary>
        /// Title of the action
        /// </summary>

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        /// Speak phrase for this action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement]
        public string Speak { get; set; }
    }
}
