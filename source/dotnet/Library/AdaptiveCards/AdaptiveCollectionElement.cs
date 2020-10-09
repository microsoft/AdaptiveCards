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
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveContainerStyle? Style { get; set; }

#if !NETSTANDARD1_3
        // Xml Serializer doesn't handle nullable value types, but this trick allows us to serialize only if non-null
        [JsonIgnore]
        [XmlAttribute("Style")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public AdaptiveContainerStyle StyleXml { get { return (Style.HasValue) ? Style.Value : AdaptiveContainerStyle.Default; } set { Style = value; } }
        public bool ShouldSerializeStyleXml() => this.Style.HasValue;
#endif

        /// <summary>
        ///     The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
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
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Bleed { get; set; }

        /// <summary>
        ///    Explicit container element minimum height
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelMinHeight { get; set; }
    }
}
