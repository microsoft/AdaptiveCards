// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements that contain elements
    /// </summary>
    public abstract class AdaptiveCollectionElement : AdaptiveElement
    {

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonConverter(typeof(IgnoreNullEnumConverter<AdaptiveContainerStyle>), true)]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

        /// <summary>
        ///     The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        ///     Defines if the element can bleed through its parent's padding
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(false)]
        public bool Bleed { get; set; }

        /// <summary>
        ///    Explicit container element minimum height
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelMinHeight { get; set; }
    }
}
