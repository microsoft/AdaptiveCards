// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls which style to apply to a container.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
    {
        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 0,

        /// <summary>
        /// The container should be displayed using the default style
        /// </summary>
        Default = 0,

        /// <summary>
        /// The container should be displayed using the emphasis style
        /// </summary>
        Emphasis = 1,

        /// <summary>
        /// The container should be displayed using the good style
        /// </summary>
        Good = 2,

        /// <summary>
        /// The container should be displayed using the attention style
        /// </summary>
        Attention = 3,

        /// <summary>
        /// The container should be displayed using the warning style
        /// </summary>
        Warning = 4,

        /// <summary>
        /// The container should be displayed using the accent style
        /// </summary>
        Accent = 5
    }
}
