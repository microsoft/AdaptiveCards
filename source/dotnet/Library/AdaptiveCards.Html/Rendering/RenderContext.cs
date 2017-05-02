using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using HtmlTags;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        public RenderContext(HostConfig hostConfig, Dictionary<Type, Func<TypedElement, RenderContext, HtmlTag>> elementRenderers)
        {
            // clone it
            this.Config = JsonConvert.DeserializeObject<HostConfig>(JsonConvert.SerializeObject(hostConfig));
            this.ElementRenderers = elementRenderers;
        }

        public HostConfig Config { get; set; }

        public Dictionary<Type, Func<TypedElement, RenderContext, HtmlTag>> ElementRenderers { get; set; }

        /// <summary>
        /// Helper to deal with casting
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        public HtmlTag Render(TypedElement element)
        {
            return this.ElementRenderers[element.GetType()](element, this);
        }
    }
}
