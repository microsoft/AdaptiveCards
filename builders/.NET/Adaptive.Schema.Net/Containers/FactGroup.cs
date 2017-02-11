using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// The FactGroup element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class FactGroup : CardElement
    {
        public FactGroup()
        { }

        /// <summary>
        /// The facts to be displayed.
        /// </summary>
        [JsonRequired]
        public List<Fact> Facts { get; set; } = new List<Fact>();
    }

    /// <summary>
    /// Represents one "fact" in a FactGroup element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class Fact
    {
        public Fact(string name, string value, string speak = null)
        {
            this.Name = name;
            this.Value = value;
            this.Speak = speak;
        }

        /// <summary>
        /// The facts label
        /// </summary>
        [JsonRequired]
        public string Name { get; set; }

        /// <summary>
        /// The fact's value
        /// </summary>
        [JsonRequired]
        public string Value { get; set; }

        /// <summary>
        /// (Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }
    }



}
