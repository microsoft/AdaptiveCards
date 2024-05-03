// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

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
#if !NETSTANDARD1_3
        [XmlElement(nameof(BackgroundImage))]
#endif
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
        [XmlElement(typeof(AdaptiveToggleInput))]
        [XmlElement(typeof(AdaptiveChoiceSetInput))]
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
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public bool? Rtl { get; set; } = null;

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Rtl")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool RtlXml { get { return (Rtl.HasValue) ? Rtl.Value : false; } set { Rtl = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeRtlXml() => this.Rtl.HasValue;
#endif

        public override IEnumerator<AdaptiveElement> GetEnumerator()
        {
            return Items.GetEnumerator();
        }

        public override void Add(AdaptiveElement element)
        {
            Items.Add(element);
        }
    }
}
