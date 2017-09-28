using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;

namespace AdaptiveCards.Rendering
{
    // TODO: give this a better name

    public class XamlRendererExtended : XamlRenderer
    {
        public XamlRendererExtended(HostConfig hostConfig,
            ResourceDictionary resources,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(hostConfig, resources, actionCallback, missingDataCallback)
        {
            SetObjectTypes();
        }

#if WPF
        public XamlRendererExtended(HostConfig hostConfig, string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(hostConfig, stylePath, actionCallback, missingDataCallback)
        {
            SetObjectTypes();
        }
#endif
        private void SetObjectTypes()
        {
            this.ElementRenderers.Set<TextInput>(XamlExTextInput.Render);
            this.ElementRenderers.Set<NumberInput>(XamlExNumberInput.Render);
            this.ElementRenderers.Set<DateInput>(XamlExDateInput.Render);
            this.ElementRenderers.Set<TimeInput>(XamlExTimeInput.Render);
        }
    }
}
