using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveCardOptions
    {
        public AdaptiveCardOptions() { }

        /// <summary>
        ///  Padding for the card
        /// </summary>
        public SpacingDefinition Padding { get; set; } = new SpacingDefinition(8);

        /// <summary>
        /// Background color for card 
        /// </summary>
        public string BackgroundColor { get; set; } = "#FFFFFF";
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ActionsOrientation
    {
        /// <summary>
        /// actions should be laid out horizontally
        /// </summary>
        Horizontal,

        /// <summary>
        /// Actions should be laid out vertically
        /// </summary>
        Vertical
    }
}
