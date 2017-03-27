using System;
using System.Collections.Generic;
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

        public XamlRendererExtended(RenderOptions options, string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options, stylePath, actionCallback, missingDataCallback)
        {
        }
    }
}
