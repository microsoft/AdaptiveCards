// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents any input element.
    /// </summary>
    public class AdaptivePadding
    {
		/// <summary>
        /// Initializes <see cref="AdaptivePadding"/>.
        /// </summary>
        public AdaptivePadding(AdaptiveSpacing left, AdaptiveSpacing top, AdaptiveSpacing right, AdaptiveSpacing bottom)
        {
			Left = left;
			Right = right;
			Top = top;
			Bottom = bottom;
        }

		/// <summary>
        /// Initializes <see cref="AdaptivePadding"/>.
        /// </summary>
        public AdaptivePadding(AdaptiveSpacing padding)
        {
			Left = Right = Top = Bottom = padding;
        }

        /// <summary>
        /// Gets or sets the left padding.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveSpacing Left { get; set; }

		/// <summary>
        /// Gets or sets the right padding.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveSpacing Right { get; set; }

		/// <summary>
        /// Gets or sets the top padding.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveSpacing Top { get; set; }

		/// <summary>
        /// Gets or sets the bottom padding.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveSpacing Bottom { get; set; }
    }
}
