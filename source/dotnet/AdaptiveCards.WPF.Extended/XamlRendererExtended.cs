using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRendererExtended : XamlRenderer
    {
        public XamlRendererExtended(RenderOptions options,
            ResourceDictionary resources,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options, resources, actionCallback, missingDataCallback)
        {
        }

#if WPF
        public XamlRendererExtended(RenderOptions options, string stylePath,
            Func<string, MemoryStream> getImageFunc,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options, stylePath, getImageFunc, actionCallback, missingDataCallback)
        {
        }
#endif
    }
}
