// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the weight of TextBock Elements
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveTextWeight>), true)]
    public enum AdaptiveTextWeight
    {
        /// <summary>
        ///     The default text weight
        /// </summary>
        Default = 0,

        /// <summary>
        ///     The default text weight
        /// </summary>
        [Obsolete("TextWeight.Normal has been deprecated.  Use TextWeight.Default", false)]
        Normal = 0,

        /// <summary>
        ///     Lighter text (thinner stroke)
        /// </summary>
        Lighter = 1,

        /// <summary>
        ///     Bolder text (wider stroke)
        /// </summary>
        Bolder = 2
    }
}
