// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the style of an Action, which influences how the action is displayed, spoken, etc.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveActionStyle>), true)]
    public enum AdaptiveActionStyle
    {
        /// <summary>
        /// Action is displayed as normal.
        /// </summary>
        Default,

        /// <summary>
        ///     Action is displayed with a positive style (typically the button becomes accent color)
        /// </summary>
        Positive,

        /// <summary>
        ///     Action is displayed with a destructive style (typically the button becomes red)
        /// </summary>
        Destructive
    }
}
