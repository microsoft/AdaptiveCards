using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveCustomElement : AdaptiveElement
    {
        public override string Type { get; set; }

        /// <summary>
        /// Programmatically generated through resolution process
        /// </summary>
        public AdaptiveElement ResolvedElement { get; set; }

        [JsonIgnore]
        IDictionary<string, object> OriginalAdditionalProperties { get; set; }

        public void ResolveElement(ResolveContext context, JToken data)
        {
            if (context.Elements.TryGetElementDefinition(Type, out AdaptiveElementDefinition definition))
            {
                ResolvedElement = definition.GetNewElement(data);

                // We store the original additional properties so they don't get re-serialized. This is a temporary hack primarily for unit testing,
                // so that the data bound properties don't get re-serialized.
                OriginalAdditionalProperties = AdditionalProperties;
                AdditionalProperties = null;
            }
        }

        public override IEnumerable<AdaptiveTypedElement> GetChildren()
        {
            if (ResolvedElement != null)
            {
                yield return ResolvedElement;
            }
        }
    }
}
