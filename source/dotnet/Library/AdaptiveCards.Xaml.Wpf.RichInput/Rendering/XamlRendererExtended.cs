using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering
{
    // TODO: give this a better name

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
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options, stylePath, actionCallback, missingDataCallback)
        {
        }
#endif
    }
}
