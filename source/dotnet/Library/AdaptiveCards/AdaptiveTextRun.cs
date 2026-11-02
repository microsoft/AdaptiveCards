// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.ComponentModel;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a TextRun.
    /// </summary>
    [XmlType(TypeName = AdaptiveTextRun.TypeName)]
    public class AdaptiveTextRun : AdaptiveInline, IAdaptiveTextElement
    {
        /// <inheritdoc />
        public const string TypeName = "TextRun";

        /// <inheritdoc />
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Initializes an empty <see cref="AdaptiveTextRun"/>.
        /// </summary>
        public AdaptiveTextRun()
        {
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveTextRun"/> with the given text.
        /// </summary>
        /// <param name="text">The initial text for this TextRun.</param>
        public AdaptiveTextRun(string text)
        {
            Text = text;
        }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveTextSize), "normal")]
        public AdaptiveTextSize Size { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveTextWeight), "normal")]
        public AdaptiveTextWeight Weight { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveTextColor), "default")]
        public AdaptiveTextColor Color { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsSubtle { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Italic { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Strikethrough { get; set; }

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Highlight { get; set; }

        /// <inheritdoc />
        [JsonRequired]
        [XmlText]
        public string Text { get; set; } = " ";

        /// <inheritdoc />
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveFontType), "default")]
        public AdaptiveFontType FontType { get; set; }

        /// <summary>
        ///     Action for this text run
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        /// Display this text underlined.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Underline { get; set; }
    }
}
