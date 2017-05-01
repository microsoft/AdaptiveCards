using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        public RenderContext(HostConfig hostConfig = null)
        {
            if (hostConfig != null)
                this.Config = hostConfig;
        }

        public HostConfig Config { get; set; } = new HostConfig();
    }
}
