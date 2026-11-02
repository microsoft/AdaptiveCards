// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
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
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveSpacing), "default")]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between this element and the one before it.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Separator { get; set; }

        /// <summary>
        /// SSML fragment for spoken interaction.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveHeight.Auto"/>.
        /// </summary>
        [JsonConverter(typeof(AdaptiveHeightConverter))]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement]
        public AdaptiveHeight Height { get; set; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        /// <summary>
        /// Indicates whether the element should be visible when the card has been rendered.
        /// </summary>
        /// <remarks>
        /// The spec default is <c>true</c> (visible). Because the .NET type default for <c>bool</c>
        /// is <c>false</c>, using <see cref="JsonIgnoreCondition.WhenWritingDefault"/> would suppress
        /// <c>false</c> values during serialization — which would then be read back as <c>true</c>
        /// (the initialised default) and silently make hidden elements visible. To avoid this roundtrip
        /// regression the property is always serialised regardless of its value.
        /// </remarks>
        [XmlElement]
        [DefaultValue(true)]
        public bool IsVisible { get; set; } = true;
    }
}
