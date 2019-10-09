using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering.XamarinForms
{
    public class AdaptiveEventArgs
    {
        public AdaptiveCard AdaptiveCard { get; set; }

        public IDictionary<string, string> Inputs { get; set; }

        public List<AdaptiveWarning> Warnings { get; set; }

        public BaseActionElement BaseActionElement { get; set; }

        public object Visual { get; set; }
    }
}
