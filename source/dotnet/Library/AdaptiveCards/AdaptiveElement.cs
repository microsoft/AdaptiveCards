// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{

    public abstract class AdaptiveElement : AdaptiveTypedElement
    {
        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveSpacing.Default"/>.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveSpacing), "default")]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between this element and the one before it.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Separator { get; set; }

        /// <summary>
        ///     SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        public bool ShouldSerializeHeight()
        {
            if (Height == AdaptiveHeight.Auto)
            {
                return false;
            }
            if (Height.HeightType == AdaptiveHeightType.Pixel)
            {
                if (!Height.Unit.HasValue)
                {
                    return false;
                }
                if (Height.Unit.Value == 0)
                {
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveHeight.Default"/>.
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), true)]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveHeight))]
#endif
        [DefaultValue(typeof(AdaptiveHeight), "auto")]
        public AdaptiveHeight Height { get; set; }

        /// <summary>
        /// Indicates whether the element should be visible when the card has been rendered.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(true)]
        public bool IsVisible { get; set; } = true;
    }
}
