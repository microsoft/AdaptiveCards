// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Foreground Color Config
    /// </summary>
    public class ForegroundColorsConfig
    {
        /// <summary>
        /// Default Config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Default { get; set; } = new FontColorConfig("#FF000000");

        /// <summary>
        /// Accent config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Accent { get; set; } = new FontColorConfig("#FF0000FF");

        /// <summary>
        /// Dark config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Dark { get; set; } = new FontColorConfig("#FF101010");

        /// <summary>
        /// Light config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Light { get; set; } = new FontColorConfig("#FFFFFFFF");

        /// <summary>
        /// Good config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Good { get; set; } = new FontColorConfig("#FF008000");

        /// <summary>
        /// Warning config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Warning { get; set; } = new FontColorConfig("#FFFFD700");

        /// <summary>
        /// Attention config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public FontColorConfig Attention { get; set; } = new FontColorConfig("#FF8B0000");
    }

    /// <summary>
    /// Font Color config
    /// </summary>
    public class FontColorConfig
    {
        /// <summary>
        /// Default constructor for deserialization.
        /// </summary>
        public FontColorConfig()
        {
            this.Default = "#FF000000";
            this.HighlightColors = new HighlightColorConfig();
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="defaultColor"></param>
        /// <param name="subtle"></param>
        public FontColorConfig(string defaultColor, string subtle = null)
        {
            this.Default = defaultColor;
            if (subtle == null)
            {
                var opacity = (byte)(Convert.ToByte(defaultColor.Substring(1, 2), 16) * .7);
                this.Subtle = $"#{opacity.ToString("x")}{defaultColor.Substring(3)}";
            }
            else
            {
                this.Subtle = subtle;
            }

            this.HighlightColors = new HighlightColorConfig();

        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public string Default { get; set; }

        /// <summary>
        /// Subtle config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public string Subtle { get; set; }

        /// <summary>
        /// HightlightColors config
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public HighlightColorConfig HighlightColors { get; set; }
    }
}
