using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Options;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        public RenderContext(HostOptions options = null)
        {
            if (options != null)
                this.Options = options;
        }

        public HostOptions Options { get; set; } = new HostOptions();
    }
}
