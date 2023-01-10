// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Container element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveContainer.TypeName)]
#endif
    public class AdaptiveContainer : AdaptiveCollectionElement
    {
        /// <inheritdoc />
        public const string TypeName = "Container";

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
        /// Sets the text flow direction
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Rtl { get; set; }

        /// <summary>
        /// Determines how to align the content horizontally.
        /// </summary>
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
        public void Add(AdaptiveElement element)
        {
            this.Items.Add(element);
        }
    }
}
