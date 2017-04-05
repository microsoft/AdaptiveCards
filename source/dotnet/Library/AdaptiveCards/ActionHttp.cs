using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Action.Http represents the properties needed to do an Http request. All input properties are available for use
    ///     via data binding. Properties can be data bound to the Uri and Body properties, allowing you to send a request
    ///     to an arbitrary url.
    /// </summary>
    public class ActionHttp : ActionBase
    {
        public const string TYPE = "Action.Http";

        public ActionHttp()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     HttpMethod to use
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET46
        [XmlAttribute]
#endif
        public string Method { get; set; } = "POST";

        /// <summary>
        ///     url to use (can have binding information)
        ///     NOTE: You can bind to properties from input fields by using {{InputID}} in the string where
        ///     InputID is an id property on an TextInput or ChoiceInput element
        /// </summary>
        [JsonRequired]
#if NET46
        [XmlAttribute]
#endif
        public string Url { get; set; }

        /// <summary>
        ///     Object which represents headers Example: { "content-type":"application/json" }
        /// </summary>
#if NET46
        [XmlIgnore]
#endif
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public object Headers { get; set; }

        [JsonIgnore]
#if NET46
        [XmlElement("Headers")]
#endif
        public string HeadersJson
        {
            get
            {
                if (Headers != null)
                    return JsonConvert.SerializeObject(Headers, Formatting.Indented);
                return null;
            }
            set
            {
                if (value == null)
                    Headers = null;
                else
                    Headers = JsonConvert.DeserializeObject(value);
            }
        }

        /// <summary>
        ///     Body for payload to http command
        ///     NOTE: You can bind to properties from input fields by using {{InputID}} in the string
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET46
        [XmlElement]
#endif
        public string Body { get; set; }
    }
}