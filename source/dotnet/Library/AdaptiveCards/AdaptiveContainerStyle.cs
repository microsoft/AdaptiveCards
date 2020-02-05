// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
    {
        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 0,

        /// <summary>
        /// The container is a default container
        /// </summary>
        Default = 0,

        /// <summary>
        /// The container should be emphasized as a grouping of elements
        /// </summary>
        Emphasis = 1,

        Good = 2,
        Attention = 3,
        Warning = 4,
        Accent = 5
    }
}
