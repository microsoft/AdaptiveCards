// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a TextRun.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTextRun.TypeName)]
#endif
    public class AdaptiveTextRun : AdaptiveInline, IAdaptiveTextElement
    {
        /// <inheritdoc />
        public const string TypeName = "TextRun";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
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
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveTextSize), "default")]
        public AdaptiveTextSize Size { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Size))]
        [DefaultValue(null)]
        public string _Size
        {
            get => JToken.FromObject(Size).ToString();
            set => Size = (AdaptiveTextSize)Enum.Parse(typeof(AdaptiveTextSize), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Size() => Size != AdaptiveTextSize.Default;
#endif

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveTextWeight), "default")]
        public AdaptiveTextWeight Weight { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Weight))]
        [DefaultValue(null)]
        public string _Weight
        {
            get => JToken.FromObject(Weight).ToString();
            set => Weight = (AdaptiveTextWeight)Enum.Parse(typeof(AdaptiveTextWeight), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Weight() => Weight != AdaptiveTextWeight.Default;
#endif

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveTextColor), "default")]
        public AdaptiveTextColor Color { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Color))]
        [DefaultValue(null)]
        public string _Color
        {
            get => JToken.FromObject(Color).ToString();
            set => Color = (AdaptiveTextColor)Enum.Parse(typeof(AdaptiveTextColor), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Color() => Color != AdaptiveTextColor.Default;
#endif
        
        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool IsSubtle { get; set; }

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Italic { get; set; }

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Strikethrough { get; set; }

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Underline { get; set; }

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Highlight { get; set; }

        /// <inheritdoc />
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public string Text { get; set; } = "";

#if !NETSTANDARD1_3
        [JsonIgnore]
        [XmlText]
        public string _Text
        {
            // We use %20 to represent an whitespace only string in xml.
            get => (Text != null && string.IsNullOrWhiteSpace(Text)) ? Text.Replace(" ", "%20") : Text;
            set => Text = string.IsNullOrWhiteSpace(value?.Replace("%20", " ")) ? value?.Replace("%20", " ") : value;
        }
#endif

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveFontType), "default")]
        public AdaptiveFontType FontType { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(FontType))]
        [DefaultValue(null)]
        public string _FontType
        {
            get => JToken.FromObject(FontType).ToString();
            set => FontType = (AdaptiveFontType)Enum.Parse(typeof(AdaptiveFontType), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_FontType() => FontType != AdaptiveFontType.Default;
#endif

        /// <summary>
        ///     Action for this text run
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveExecuteAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }
    }
}
