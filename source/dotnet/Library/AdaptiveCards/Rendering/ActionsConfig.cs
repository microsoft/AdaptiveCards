// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of actions
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ActionsConfig
    {
        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment ActionAlignment { get; set; } = AdaptiveHorizontalAlignment.Stretch;

        /// <summary>
        /// Space between actions
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int ButtonSpacing { get; set; } = 10;

        /// <summary>
        /// Max number of actions to support on your Cards(e.g., 3)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int MaxActions { get; set; } = 5;

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// ShowCard configuration
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ShowCardConfig ShowCard { get; set; } = new ShowCardConfig();

        /// <summary>
        /// Position of Icon relative to Title
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public IconPlacement IconPlacement { get; set; } = new IconPlacement();

        /// <summary>
        /// Size of Icon
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int IconSize { get; set; } = 30;
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ShowCardConfig
    {
        public ShowCardConfig() { }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Inline;

        /// <summary>
        /// If actionMode is inline this is the margin between the inline card and the actions
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int InlineTopMargin { get; set; } = 16;
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ShowCardActionMode
    {
        /// <summary>
        /// Show the card inline
        /// </summary>
        Inline,

        /// <summary>
        /// Popup the card
        /// </summary>
        Popup
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

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum IconPlacement
    {
        /// <summary>
        /// Places the icons about the text in actions
        /// </summary>
        AboveTitle,

        /// <summary>
        /// Place the icon to the left of the text in actions
        /// </summary>
        LeftOfTitle
    }
}
