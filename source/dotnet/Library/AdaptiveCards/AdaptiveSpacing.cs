// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the spacing of an element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveSpacing>), true)]
    public enum AdaptiveSpacing
    {
        /// <summary>
        /// Use the default spacing.
        /// </summary>
        Default,

        /// <summary>
        /// Use no spacing.
        /// </summary>
        None,

        /// <summary>
        /// Use small spacing.
        /// </summary>
        Small,

        /// <summary>
        /// Use medium spacing.
        /// </summary>
        Medium,

        /// <summary>
        /// Use large spacing.
        /// </summary>
        Large,

        /// <summary>
        /// Use extra large spacing.
        /// </summary>
        ExtraLarge,

        /// <summary>
        /// This results in the same padding that's applied to the card itself.
        /// </summary>
        Padding
    }
}
