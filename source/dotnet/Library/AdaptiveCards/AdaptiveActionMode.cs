// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the font type of the TextBlock Elements
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveActionMode>), true)]
    public enum AdaptiveActionMode
    {
        /// <summary>
        ///     The Action is displayed as a button.
        /// </summary>
        Primary,

        /// <summary>
        ///     Action is placed in an overflow menu (typically a popup menu under a ... button).
        /// </summary>
        Secondary
    }
}
