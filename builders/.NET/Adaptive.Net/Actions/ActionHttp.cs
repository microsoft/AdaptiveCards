using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Adaptive
{
    /// <summary>
    /// Action.Http represents the properties needed to do an Http request. All input properties are available for use 
    /// via data binding. Properties can be data bound to the Uri and Body properties, allowing you to send a request 
    /// to an arbitrary url.
    /// </summary>
    public partial class ActionHttp : ActionBase
    {
        public ActionHttp() : base() { }


        /// <summary>
        /// HttpMethod to use
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Method { get; set; } = "POST";

        /// <summary>
        /// url to use (can have binding information)
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string where 
        /// InputID is an id property on an TextInput or ChoiceInput element
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Url { get; set; }

        /// <summary>
        /// Object which represents headers Example: { "content-type":"application/json" }
        /// </summary>
        [XmlIgnore]
        public object Headers { get; set; }

        //[JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        //public KeyValuePair<string, string>[] HeadersXml
        //{
        //    get
        //    {
        //        return ((JObject)this.Headers).Properties().Select(p => new KeyValuePair<string, string>(p.Name, (string)p.Value)).ToArray();
        //    }
        //    set
        //    {
        //        dynamic obj = new JObject();
        //        foreach(var pair in value)
        //        {
        //            obj[pair.Key] = pair.Value;
        //        }
        //        this.Headers = obj;
        //    }
        //}

        /// <summary>
        /// Body for payload to http command 
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Body { get; set; }
    }
}
