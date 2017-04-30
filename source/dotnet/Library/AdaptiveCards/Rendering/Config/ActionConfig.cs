using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Config
{
    /// <summary>
    /// Properties which control rendering of actions
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ActionConfig
    {
        public ActionConfig() { }

        public ShowCardConfig ShowCard { get; set; } = new ShowCardConfig();

        /// <summary>
        /// Max number of actions to support on your Cards(e.g., 3)
        /// </summary>
        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        public HorizontalAlignment ActionAlignment { get; set; } = HorizontalAlignment.Center;


        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundColor { get; set; } = "#FF5098FF";

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BorderColor { get; set; } = "#FF000000";

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string TextColor { get; set; } = "#FFFFFFFF";

        public int BorderThickness { get; set; } = 1;

        public int FontWeight { get; set; } = 400;

        public int FontSize { get; set; } = 12;

        /// <summary>
        /// Space between actions
        /// </summary>
        public int Spacing { get; set; } = 8;

        /// <summary>
        /// space between title and button edge
        /// </summary>

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SpacingDefinition Padding { get; set; } = new SpacingDefinition(4);

    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ShowCardConfig
    {
        public ShowCardConfig() { }

        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Inline;

        /// <summary>
        /// Background color for showcard area
        /// </summary>
        public string BackgroundColor { get; set; } = "#FFF8F8F8";

        /// <summary>
        /// If actionMode is inline and AutoPadding is on then the background will extend to the edges of the parent card.
        /// </summary>
        public bool AutoPadding { get; set; } = true;
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ShowCardActionMode
    {
        Inline,
        Popup
    }

}
