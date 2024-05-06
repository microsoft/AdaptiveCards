// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an element in Adaptive Cards.
    /// </summary>
    public abstract class AdaptiveElement : AdaptiveTypedElement
    {
        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveSpacing.Default"/>.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveSpacing), "default")]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between this element and the one before it.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Separator { get; set; }

        /// <summary>
        /// SSML fragment for spoken interaction.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveHeight.Auto"/>.
        /// </summary>
        [JsonConverter(typeof(AdaptiveHeightConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlElement]
        public AdaptiveHeight Height { get; set; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        /// <summary>
        /// Determines whether the height property should be serialized or not.
        /// </summary>
        public bool ShouldSerializeHeight() => this.Height?.ShouldSerializeAdaptiveHeight() == true;

        /// <summary>
        /// Indicates whether the element should be visible when the card has been rendered.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlElement]
        [DefaultValue(true)]
        public bool IsVisible { get; set; } = true;
    }
}
