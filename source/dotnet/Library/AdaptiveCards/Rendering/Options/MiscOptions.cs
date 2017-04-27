using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class CardElementOptions
    {
        public CardElementOptions() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        public SeparationOption Separation { get; set; } = new SeparationOption() { Spacing = 10 };
    }
}
