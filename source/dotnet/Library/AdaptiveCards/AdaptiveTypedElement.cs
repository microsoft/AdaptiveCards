using System;
using System.Collections;
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


        public AdaptiveElementDefinitions Elements { get; set; } = new AdaptiveElementDefinitions();

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public IDictionary<string, object> AdditionalProperties { get; set;  } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        public object Data { get; set; }

        public object Repeat { get; set; }

        public virtual IEnumerable<AdaptiveTypedElement> GetChildren()
        {
            return new AdaptiveTypedElement[0];
        }

        public virtual IEnumerable<IList> GetChildrenLists()
        {
            return new IList[0];
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

        public void ResolveData(ResolveContext context)
        {
            context = context.CreateForCurrElement(this);

            // First do repeating items
            foreach (var lists in GetChildrenLists())
            {
                for (int i = 0; i < lists.Count; i++)
                {
                    var childEl = lists[i] as AdaptiveTypedElement;
                    if (childEl != null)
                    {
                        if (childEl.Repeat != null)
                        {
                            object repeatData = ResolveChildData(Data, childEl.Repeat);
                            childEl.Repeat = null;
                            if (repeatData != null && repeatData is JArray jArray)
                            {
                                object originalChildElData = childEl.Data;
                                childEl.Data = null;

                                var elementRepeater = new ElementRepeater(childEl);

                                lists.RemoveAt(i);
                                i--;

                                foreach (var item in jArray)
                                {
                                    var newEl = elementRepeater.GetNewElement();
                                    newEl.Data = ResolveChildData(item, originalChildElData);
                                    lists.Insert(i + 1, newEl);
                                    i++;
                                }
                            }
                        }
                    }
                }
            }

            // Resolve data binding on this element
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

            foreach (var additionalProp in AdditionalProperties.ToArray())
            {
                if (additionalProp.Value is string s)
                {
                    object newVal = BindingEvaluator.EvaluateBinding(Data as JObject, s);
                    AdditionalProperties[additionalProp.Key] = newVal;
                }
            }

            // If it's a custom element, load it
            if (this is AdaptiveCustomElement customElement)
            {
                // Serialize the element so its properties can be bound to from its child elements
                JObject customElementData = JObject.FromObject(customElement);

                customElement.ResolveElement(context);
                if (customElement.ResolvedElement != null)
                {
                    customElement.ResolvedElement.Data = ResolveChildData(customElementData, customElement.ResolvedElement.Data);
                }
            }

            // Now deal with children
            foreach (var child in GetChildren())
            {
                child.Data = ResolveChildData(Data, child.Data);

                child.ResolveData(context);
            }
        }

        private static object ResolveChildData(object parentData, object initialChildData)
        {
            if (initialChildData == null)
            {
                return parentData;
            }

            else if (initialChildData is string scopedDataExpression)
            {
                return BindingEvaluator.EvaluateBinding(parentData as JObject, scopedDataExpression);
            }

            return initialChildData;
        }
    }
}
