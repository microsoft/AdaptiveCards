using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public struct RemoteResourceInformation
    {
        readonly string url;
        readonly Type type;
        readonly string mimeType;

        public RemoteResourceInformation(string url, Type type, string mimeType)
        {
            this.url = url;
            this.type = type;
            this.mimeType = mimeType;
        }
    }
}
