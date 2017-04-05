using AdaptiveCards.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        public RenderContext(RendererOptions options = null)
        {
            if (options != null)
                this.Options = options;
        }

        public RendererOptions Options { get; set; } = new RendererOptions();
    }
}
