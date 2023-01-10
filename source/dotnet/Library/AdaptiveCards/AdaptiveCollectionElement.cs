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
    /// Base class for all elements that contain other elements.
    /// </summary>
    public abstract class AdaptiveCollectionElement : AdaptiveElement
    {
        /// <summary>
        /// The style used to display this element. See <see cref="AdaptiveContainerStyle" />.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveContainerStyle), "default")]
        public AdaptiveContainerStyle Style { get; set; }

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
            set => Style = (AdaptiveContainerStyle)Enum.Parse(typeof(AdaptiveContainerStyle), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Style() => Style != AdaptiveContainerStyle.Default;
#endif

        /// <summary>
        /// The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(VerticalContentAlignment))]
        [DefaultValue(null)]
        public string _VerticalContentAlignment
        {
            get => JToken.FromObject(VerticalContentAlignment).ToString();
            set => VerticalContentAlignment = (AdaptiveVerticalContentAlignment)Enum.Parse(typeof(AdaptiveVerticalContentAlignment), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_VerticalContentAlignment() => VerticalContentAlignment != AdaptiveVerticalContentAlignment.Top;
#endif

        /// <summary>
        /// Action for this container. This allows for setting a default action at the container level.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveSelectAction SelectAction { get; set; }

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
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string MinHeight { get; set; }

        /// <summary>
        /// PixelMinHeight if height is not auto/stretch
        /// </summary>
        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public int PixelMinHeight { get => int.TryParse(MinHeight?.Replace("px", ""), out var val) ? (int)val : 0; set => MinHeight = $"{value}px"; }

    }
}
