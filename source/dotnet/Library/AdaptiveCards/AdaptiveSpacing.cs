// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveSpacing>), true)]
    public enum AdaptiveSpacing
    {
        Default,
        None,
        Small,
        Medium,
        Large,
        ExtraLarge,

        /// <summary>
        /// This results in the same padding that's applied to the card itself.
        /// </summary>
        Padding
    }
}
