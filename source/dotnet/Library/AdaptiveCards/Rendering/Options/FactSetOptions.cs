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
    public class FactSetOptions : CardElementOptions
    {
        public FactSetOptions() { }

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        public TextOptions Title { get; set; } = new TextOptions() { Size = TextSize.Normal, Color = TextColor.Default, IsSubtle = false, Weight = TextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        public TextOptions Value { get; set; } = new TextOptions();

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 20;
    }
}
