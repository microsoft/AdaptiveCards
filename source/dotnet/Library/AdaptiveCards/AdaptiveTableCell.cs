// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType(TypeName = "TableCell")]
#endif
    public class AdaptiveTableCell : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "TableCell";

        /// <summary>
        /// Initializes an empty Fact.
        /// </summary>
        public AdaptiveTableCell()
        {
        }

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Background image to use when displaying this container.
        /// </summary>
        [JsonConverter(typeof(AdaptiveBackgroundImageConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [DefaultValue(null)]
        public AdaptiveBackgroundImage BackgroundImage { get; set; }

        /// <summary>
        /// Elements within this container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveElement>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTextBlock))]
        [XmlElement(typeof(AdaptiveRichTextBlock))]
        [XmlElement(typeof(AdaptiveImage))]
        [XmlElement(typeof(AdaptiveContainer))]
        [XmlElement(typeof(AdaptiveColumnSet))]
        [XmlElement(typeof(AdaptiveImageSet))]
        [XmlElement(typeof(AdaptiveFactSet))]
        [XmlElement(typeof(AdaptiveTextInput))]
        [XmlElement(typeof(AdaptiveDateInput))]
        [XmlElement(typeof(AdaptiveTimeInput))]
        [XmlElement(typeof(AdaptiveNumberInput))]
        [XmlElement(typeof(AdaptiveChoiceSetInput))]
        [XmlElement(typeof(AdaptiveToggleInput))]
        [XmlElement(typeof(AdaptiveMedia))]
        [XmlElement(typeof(AdaptiveActionSet))]
        [XmlElement(typeof(AdaptiveTable))]
        [XmlElement(typeof(AdaptiveUnknownElement))]
#endif
        public List<AdaptiveElement> Items { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        /// The style used to display this element. See <see cref="AdaptiveContainerStyle" />.
        /// </summary>
        [JsonConverter(typeof(IgnoreNullEnumConverter<AdaptiveContainerStyle>), true)]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Style")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public AdaptiveContainerStyle StyleXml { get { return (Style.HasValue) ? Style.Value : AdaptiveContainerStyle.Default; } set { Style = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeStyleXml() => this.Style.HasValue;
#endif

        /// <summary>
        /// The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// Defines if the element can bleed through its parent's padding.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Bleed { get; set; }

        /// <summary>
        /// Explicit container element minimum height.
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelMinHeight { get; set; }
        /// <summary>
        /// Sets the text flow direction
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public bool? Rtl { get; set; } = null;
    }
}
