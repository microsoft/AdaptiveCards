using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTargetElement
    {

        public AdaptiveTargetElement() { }

        public AdaptiveTargetElement(string elementId, bool isVisible)
        {
            ElementId = elementId;
            IsVisible = isVisible;
        }

        public string ElementId { get; set; }

        public bool IsVisible { get; set; }

    }
}
