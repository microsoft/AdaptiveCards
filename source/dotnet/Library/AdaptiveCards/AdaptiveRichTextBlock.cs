using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveRichTextBlock.TypeName)]
#endif
    public class AdaptiveRichTextBlock : AdaptiveElement
    {
        public const string TypeName = "RichTextBlock";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        public AdaptiveRichTextBlock()
        {

        }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxLines { get; set; }

        [JsonRequired]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveParagraph>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveParagraph))]
#endif
        public List<AdaptiveParagraph> Paragraphs { get; set; } = new List<AdaptiveParagraph>();

        [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
        public class AdaptiveParagraph
        {
            [JsonRequired]
            [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveTextRun>))]
#if !NETSTANDARD1_3
            [XmlElement(typeof(AdaptiveTextRun))]
#endif
            public List<AdaptiveTextRun> Inlines { get; set; } = new List<AdaptiveTextRun>();

#if !NETSTANDARD1_3
            [XmlType(TypeName = AdaptiveTextBlock.TypeName)]
#endif
            public class AdaptiveTextRun : ITextElement
            {
                public const string TypeName = "TextRun";

                public string Type { get; set; } = TypeName;

                public AdaptiveTextRun()
                {

                }

                public AdaptiveTextRun(string text)
                {
                    Text = text;
                }

                /// <summary>
                ///     The size of the text
                /// </summary>
                [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
                [XmlAttribute]
#endif
                [DefaultValue(typeof(AdaptiveTextSize), "normal")]
                public AdaptiveTextSize Size { get; set; }

                /// <summary>
                ///     The weight of the text
                /// </summary>
                [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
                [XmlAttribute]
#endif
                [DefaultValue(typeof(AdaptiveTextWeight), "normal")]
                public AdaptiveTextWeight Weight { get; set; }

                /// <summary>
                ///     The color of the text
                /// </summary>
                [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
                [XmlAttribute]
#endif
                [DefaultValue(typeof(AdaptiveTextColor), "default")]
                public AdaptiveTextColor Color { get; set; }

                /// <summary>
                ///     Make the text less prominent
                /// </summary>
                [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
                [XmlAttribute]
#endif
                [DefaultValue(false)]
                public bool IsSubtle { get; set; }

                /// <summary>
                ///     The text to display
                /// </summary>
                [JsonRequired]
#if !NETSTANDARD1_3
                [XmlText]
#endif
                public string Text { get; set; } = " ";

                /// <summary>
                ///     The font style of the text
                /// </summary>
                [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
                [XmlAttribute]
#endif
                [DefaultValue(typeof(AdaptiveFontStyle), "default")]
                public AdaptiveFontStyle FontStyle { get; set; }
            }
        }
    }
}
