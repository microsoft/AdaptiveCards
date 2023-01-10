// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the TextBlock element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTextBlock.TypeName)]
#endif
    public class AdaptiveTextBlock : AdaptiveElement, IAdaptiveTextElement
    {
        /// <inheritdoc />
        public const string TypeName = "TextBlock";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Initializes an empty <see cref="AdaptiveTextBlock"/> instance.
        /// </summary>
        public AdaptiveTextBlock()
        {
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveTextBlock"/> instance with the supplied text.
        /// </summary>
        /// <param name="text">The text of this TextBlock.</param>
        public AdaptiveTextBlock(string text)
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

//#if !NETSTANDARD1_3
//        [JsonIgnore]
//        [XmlAttribute("space", Namespace = "http://www.w3.org/XML/1998/namespace")]
//        public string Space = "preserve";
//        public bool ShouldSerializeSpace() => Text != null && Text.Length > 0 && String.IsNullOrWhiteSpace(Text);
//#endif

        /// <inheritdoc />
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(HorizontalAlignment))]
        [DefaultValue(null)]
        public string _HorizontalAlignment
        {
            get => JToken.FromObject(HorizontalAlignment).ToString();
            set => HorizontalAlignment = (AdaptiveHorizontalAlignment)Enum.Parse(typeof(AdaptiveHorizontalAlignment), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_HorizontalAlignment() => HorizontalAlignment != AdaptiveHorizontalAlignment.Left;
#endif

        /// <summary>
        /// Controls text wrapping behavior.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        /// When <see cref="AdaptiveTextBlock.Wrap"/> is true, this controls the maximum number of lines of text to display.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxLines { get; set; }

        /// <summary>
        /// The maximum width of the TextBlock.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxWidth { get; set; }

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
        /// The style (<see cref="AdaptiveTextBlockStyle"/>) of text.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveTextBlockStyle), "default")]
        public AdaptiveTextBlockStyle Style { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Style))]
        [DefaultValue(null)]
        public string _Style
        {
            get => JToken.FromObject(Style).ToString();
            set => Style = (AdaptiveTextBlockStyle)Enum.Parse(typeof(AdaptiveTextBlockStyle), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Style() => Style != AdaptiveTextBlockStyle.Default;
#endif

    }
}
