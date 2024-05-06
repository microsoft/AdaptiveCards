// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Base class for all elements that contain other elements.
    /// </summary>
    public abstract class AdaptiveCollectionElement : AdaptiveElement, IEnumerable<AdaptiveElement>
    {
        /// <summary>
        /// The style used to display this element. See <see cref="AdaptiveContainerStyle" />.
        /// </summary>
        [JsonConverter(typeof(IgnoreNullEnumConverter<AdaptiveContainerStyle>), true)]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlIgnore]
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

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

        /// <inheritdoc/>
        public abstract IEnumerator<AdaptiveElement> GetEnumerator();

        /// <inheritdoc/>
        public abstract void Add(AdaptiveElement value);

        /// <inheritdoc/>
        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new System.NotImplementedException();
        }


        /// <summary>
        /// Horizontal alignment for element.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// Action for this container. This allows for setting a default action at the container level.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        /// Defines if the element can bleed through its parent's padding.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Bleed { get; set; }

        /// <summary>
        /// Explicit card minimum height with 'px'. (100px, 200px)
        /// </summary>
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string MinHeight { get; set; }

        /// <summary>
        /// Explicit container element minimum height.
        /// </summary>
        [JsonIgnore]
        [XmlIgnore]
        public uint PixelMinHeight { get => uint.TryParse(MinHeight?.Replace("px", ""), out var val) ? (uint)val : 0; set => MinHeight = $"{value}px"; }
    }
}
