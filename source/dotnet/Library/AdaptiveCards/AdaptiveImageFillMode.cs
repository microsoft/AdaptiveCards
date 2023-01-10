// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls how an image fills a space.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveImageFillMode>), true)]
    public enum AdaptiveImageFillMode
    {
        /// <summary>
        /// Image covers the entire width of its container (preserving aspect ratio). The image may be clipped if the
        /// aspect ratio of the image doesn't match the aspect ratio of its container. <see
        /// cref="AdaptiveVerticalAlignment"/> is respected, but <see cref="AdaptiveHorizontalAlignment"/> is ignored
        /// (as it's irrelevant).
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("cover")]
#endif
        Cover,

        /// <summary>
        /// The image isn't stretched. Rather, it's repeated on the x-axis as many times as needed to cover the
        /// container's width. <see cref="AdaptiveVerticalAlignment"/> is respected (defaults to <see
        /// cref="AdaptiveVerticalAlignment.Top"/>). <see cref="AdaptiveHorizontalAlignment"/> is ignored.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("repeatHorizontally")]
#endif
        RepeatHorizontally,

        /// <summary>
        /// The image isn't stretched. Rather, it's repeated on the y-axis as many times as needed to cover the
        /// container's width. <see cref="AdaptiveHorizontalAlignment"/> is respected (defaults to <see
        /// cref="AdaptiveHorizontalAlignment.Left"/>). <see cref="AdaptiveVerticalAlignment"/> is ignored.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("repeatVertically")]
#endif
        RepeatVertically,

        /// <summary> The image isn't stretched. Rather, it's repeated on the x-axis and then on the y-axis as many
        /// times as needed to cover the container's width. Both <see cref="AdaptiveHorizontalAlignment"/> and <see
        /// cref="AdaptiveHorizontalAlignment.Left"/>) are respected. (defaults to <see
        /// cref="AdaptiveVerticalAlignment.Top"/> and <see cref="AdaptiveHorizontalAlignment.Left"/>
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("repeat")]
#endif
        Repeat
    }
}
