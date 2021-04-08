// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HeadingsConfig
    {
        /// <summary>
        /// Level of heading text, used only if underlying platform requires it.
        /// </summary>
        public int Level { get; set; } = 2;
    }
}
