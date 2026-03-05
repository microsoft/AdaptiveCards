// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering and behavior of actions.
    /// </summary>
    public class ActionsConfig
    {
        /// <summary>
        /// Arrange actions horizontally or vertically.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// Control horizontal alignment behavior.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveHorizontalAlignment ActionAlignment { get; set; } = AdaptiveHorizontalAlignment.Stretch;

        /// <summary>
        /// Controls the amount of space between actions.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int ButtonSpacing { get; set; } = 10;

        /// <summary>
        /// Max number of actions to allow in parsed cards.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// Controls spacing between card elements.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// Controls the behavior of Action.ShowCard.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public ShowCardConfig ShowCard { get; set; } = new ShowCardConfig();

        /// <summary>
        /// Controls where action icons are placed relative to titles.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public IconPlacement IconPlacement { get; set; } = new IconPlacement();

        /// <summary>
        /// Defines the size at which to render icons.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int IconSize { get; set; } = 30;
    }

    /// <summary>
    /// Configuration for Action.ShowCard elements.
    /// </summary>
    public class ShowCardConfig
    {
        /// <summary>
        /// Initializes a default <see cref="ShowCardConfig"/>.
        /// </summary>
        public ShowCardConfig() { }

        /// <summary>
        /// Controls how Action.ShowCard elements behave when invoked.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Inline;

        /// <summary>
        /// Determines what style to use when displaying an inline Action.ShowCard.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveContainerStyle Style { get; set; } = AdaptiveContainerStyle.Emphasis;

        /// <summary>
        /// Controls the margin to use when showing an inline Action.ShowCard.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int InlineTopMargin { get; set; } = 16;
    }

    /// <summary>
    /// Controls the behavior of an invoked Action.ShowCard.
    /// </summary>
    [JsonConverter(typeof(JsonStringEnumConverter))]
    public enum ShowCardActionMode
    {
        /// <summary>
        /// Expand the Action.ShowCard in-place.
        /// </summary>
        Inline,

        /// <summary>
        /// Display the Action.ShowCard in a popup window.
        /// </summary>
        Popup
    }

    /// <summary>
    /// Controls the layout of actions.
    /// </summary>
    [JsonConverter(typeof(JsonStringEnumConverter))]
    public enum ActionsOrientation
    {
        /// <summary>
        /// Actions should be laid out horizontally.
        /// </summary>
        Horizontal,

        /// <summary>
        /// Actions should be laid out vertically.
        /// </summary>
        Vertical
    }

    /// <summary>
    /// Controls where to place icons in actions.
    /// </summary>
    [JsonConverter(typeof(JsonStringEnumConverter))]
    public enum IconPlacement
    {
        /// <summary>
        /// Display icons above text.
        /// </summary>
        AboveTitle,

        /// <summary>
        /// Display icons to the left of the text.
        /// </summary>
        LeftOfTitle
    }
}
