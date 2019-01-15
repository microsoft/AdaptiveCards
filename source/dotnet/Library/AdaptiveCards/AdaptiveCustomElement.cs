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

        public void ResolveElement(ResolveContext context)
        {
            if (context.Elements.TryGetElementDefinition(Type, out AdaptiveElementDefinition definition))
            {
                ResolvedElement = definition.GetNewElement();
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
