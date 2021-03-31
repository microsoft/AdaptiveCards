// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveConfigBase
    {
        [JsonExtensionData]
        public IDictionary<string, JToken> AdditionalData { get; set; } = new Dictionary<string, JToken>();
    }
}
