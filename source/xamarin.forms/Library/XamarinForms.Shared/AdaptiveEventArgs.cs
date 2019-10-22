using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering.XamarinForms
{
    public class AdaptiveEventArgs : EventArgs
    {
        // public AdaptiveCard AdaptiveCard { get; set; }

        public Dictionary<string, string> Inputs { get; set; }

        // public List<AdaptiveWarning> Warnings { get; set; }

        // public BaseActionElement BaseActionElement { get; set; }

        public object Visual { get; set; }
    }
}
