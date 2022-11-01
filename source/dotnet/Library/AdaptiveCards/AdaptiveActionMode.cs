// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Determines whether the action should be displayed as a button or in the overflow menu.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveActionMode>), true)]
    public enum AdaptiveActionMode
    {
        /// <summary>
        /// Action is displayed as a button.
        /// </summary>
        Primary,

        /// <summary>
        /// Action is placed in an overflow menu (typically a popup menu under a ... button). 
        /// </summary>
        Secondary
    }
}
