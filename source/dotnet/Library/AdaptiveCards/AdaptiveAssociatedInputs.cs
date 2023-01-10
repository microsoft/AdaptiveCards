// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls which inputs are associated with a given submit action
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveAssociatedInputs>), true)]
    public enum AdaptiveAssociatedInputs
    {
        /// <summary>
        ///     Gathers and validates inputs from the current card and any parent cards
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("auto")]
#endif
        Auto,

        /// <summary>
        ///     Does not gather or validate any inputs on submit
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("none")]
#endif
        None
    }
}
