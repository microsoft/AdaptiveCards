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

    public class XamlRendererExtended : AdaptiveCardRenderer
    {
        public XamlRendererExtended(HostConfig hostConfig)
            : base(hostConfig)
        {
            SetObjectTypes();
        }

        private void SetObjectTypes()
        {
            this.ElementRenderers.Set<TextInput>(XamlExTextInput.Render);
            this.ElementRenderers.Set<NumberInput>(XamlExNumberInput.Render);
            this.ElementRenderers.Set<DateInput>(XamlExDateInput.Render);
            this.ElementRenderers.Set<TimeInput>(XamlExTimeInput.Render);
        }
    }
}
