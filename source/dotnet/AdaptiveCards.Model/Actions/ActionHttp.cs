using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// Action.Http represents the properties needed to do an Http request. All input properties are available for use 
    /// via data binding. Properties can be data bound to the Uri and Body properties, allowing you to send a request 
    /// to an arbitrary url.
    /// </summary>
    public partial class ActionHttp : ActionBase
    {
        public ActionHttp() : base()
        {
            this.Type = "Action.Http";
        }

        /// <summary>
        /// HttpMethod to use
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Method { get; set; } = "POST";

        /// <summary>
        /// url to use (can have binding information)
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string where 
        /// InputID is an id property on an TextInput or ChoiceInput element
        /// </summary>
        [JsonRequired]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Url { get; set; }

        /// <summary>
        /// Object which represents headers Example: { "content-type":"application/json" }
        /// </summary>
#if DESKTOP
        [XmlIgnore]
#endif
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public object Headers { get; set; }

        [JsonIgnore]
#if DESKTOP
        [XmlElement("Headers")]
#endif
        public string HeadersJson
        {
            get
            {
                if (this.Headers != null)
                    return JsonConvert.SerializeObject(this.Headers, Formatting.Indented);
                return null;
            }
            set
            {
                if (value == null)
                    this.Headers = null;
                else
                    this.Headers = JsonConvert.DeserializeObject(value);
            }
        }

        /// <summary>
        /// Body for payload to http command 
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlElement]
#endif
        public string Body { get; set; }
    }
}
