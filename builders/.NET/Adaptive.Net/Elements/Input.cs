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
    /// Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public partial class Input : CardElement
    {
        public Input()
        { }

        /// <summary>
        /// Id for the value (will be used to identify collected input when SUBMIT is clicked)
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Id { get; set; }

        /// <summary>
        /// The input must have a value for it to be part of a Submit or Http action 
        /// </summary>
        [XmlAttribute]
        public bool IsRequired { get; set; }

        public bool ShouldSerializeIsRequired() { return this.IsRequired; }
    }
}
