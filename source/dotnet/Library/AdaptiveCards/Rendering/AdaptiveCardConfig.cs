// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveCardConfig : AdaptiveConfigBase
    {
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool AllowCustomStyle { get; set; }
    }
}
