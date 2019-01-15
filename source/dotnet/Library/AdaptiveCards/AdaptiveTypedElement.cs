using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(AdaptiveTypedElementConverter))]
    public abstract class AdaptiveTypedElement
    {
        /// <summary>
        /// The type name of the element
        /// </summary>
        [JsonProperty(Order = -10, Required = Required.Always, DefaultValueHandling = DefaultValueHandling.Include)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public abstract string Type { get; set; }

        /// <summary>
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Id { get; set; }


        public Dictionary<string, object> Elements { get; set; } = new Dictionary<string, object>();

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public IDictionary<string, object> AdditionalProperties { get; set;  } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        public object Data { get; set; }

        public virtual IEnumerable<AdaptiveTypedElement> GetChildren()
        {
            return new AdaptiveTypedElement[0];
        }

        public IEnumerable<AdaptiveTypedElement> GetDescendants()
        {
            foreach (var c in GetChildren())
            {
                yield return c;

                foreach (var d in c.GetDescendants())
                {
                    yield return d;
                }
            }
        }

        public void ResolveData()
        {
            foreach (var child in GetChildren())
            {
                if (child.Data == null)
                {
                    child.Data = Data;
                }

                else if (child.Data is string scopedDataExpression)
                {
                    child.Data = BindingEvaluator.EvaluateBinding(Data as JObject, scopedDataExpression);
                }

                child.ResolveData();
            }

            var thisProperties = this.GetType().GetTypeInfo().DeclaredProperties;
            foreach (var p in thisProperties.Where(i => i.PropertyType == typeof(string)))
            {
                string pVal = p.GetValue(this) as string;
                if (pVal != null)
                {
                    string newPVal = BindingEvaluator.EvaluateBinding<string>(Data as JObject, pVal);
                    if (pVal != newPVal)
                    {
                        p.SetValue(this, newPVal);
                    }
                }
            }
        }
    }
}
