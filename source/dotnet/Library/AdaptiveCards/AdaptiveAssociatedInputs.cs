// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
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
        Auto = 0,

        /// <summary>
        ///     Does not gather or validate any inputs on submit
        /// </summary>
        None = 1
    }
}
