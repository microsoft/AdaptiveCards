// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSizesConfig
    {
        public int Small { get; set; } = 40;

        public int Medium { get; set; } = 80;

        public int Large { get; set; } = 160;
    }
}
