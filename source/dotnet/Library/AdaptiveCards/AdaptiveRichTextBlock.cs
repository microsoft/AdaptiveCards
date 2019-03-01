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

        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveParagraph>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveParagraph))]
#endif
        public List<AdaptiveParagraph> Paragraphs { get; set; } = new List<AdaptiveParagraph>();

        [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
        public class AdaptiveParagraph
        {
            [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveRun>))]
#if !NETSTANDARD1_3
            [XmlElement(typeof(AdaptiveTextRun))]
#endif
            public List<AdaptiveRun> Inlines { get; set; } = new List<AdaptiveRun>();

            public abstract class AdaptiveRun : AdaptiveTypedElement { }

#if !NETSTANDARD1_3
            [XmlType(TypeName = AdaptiveTextBlock.TypeName)]
#endif
            public class AdaptiveTextRun : AdaptiveRun, ITextElement
            {
                public const string TypeName = "TextRun";

                public override string Type { get; set; } = TypeName;

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
                public AdaptiveTextSize Size { get; set; }

                /// <summary>
                ///     The weight of the text
                /// </summary>
                public AdaptiveTextWeight Weight { get; set; }

                /// <summary>
                ///     The color of the text
                /// </summary>
                public AdaptiveTextColor Color { get; set; }

                /// <summary>
                ///     Make the text less prominent
                /// </summary>
                public bool IsSubtle { get; set; }

                /// <summary>
                ///     The text to display
                /// </summary>
                public string Text { get; set; } = " ";

                /// <summary>
                ///     The font style of the text
                /// </summary>
                public AdaptiveFontStyle FontStyle { get; set; }
            }
        }
    }
}
