using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Config
{
    public class HostConfigParseResult
    {
        public HostConfig HostConfig { get; private set; }

        internal HostConfigParseResult(HostConfig hostConfig)
        {
            HostConfig = hostConfig;
        }
    }
}