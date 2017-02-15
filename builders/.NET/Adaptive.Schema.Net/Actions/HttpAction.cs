using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// HttpAction represents the properties needed to do an Http request. All input properties are available for use 
    /// via data binding. Properties can be data bound to the Uri and Body properties, allowing you to send a request 
    /// to an arbitrary url.
    /// </summary>
    public class HttpAction : ActionBase
    {
        public HttpAction() : base() { }


        /// <summary>
        /// HttpMethod to use
        /// </summary>
        public string Method { get; set; } = "POST";

        /// <summary>
        /// url to use (can have binding information)
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string where 
        /// InputID is an id property on an TextInput or ChoiceInput element
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }

        /// <summary>
        /// Object which represents headers Example: { "content-type":"application/json" }
        /// </summary>
        public object Headers { get; set; }

        /// <summary>
        /// Body for payload to http command 
        /// NOTE: You can bind to properties from input fields by using {{InputID}} in the string
        /// </summary>
        public string Body { get; set; }
    }
}
