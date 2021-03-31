// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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

        [JsonRequired]
        [JsonConverter(typeof(AdaptiveInlinesConverter))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTextRun))]
#endif
        public List<AdaptiveInline> Inlines { get; set; } = new List<AdaptiveInline>();
    }
}
