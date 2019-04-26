// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Specifies how much spacing should be used for the various spacing options
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SpacingsConfig
    {
        public int Small { get; set; } = 3;

        public int Default { get; set; } = 8;

        public int Medium { get; set; } = 20;

        public int Large { get; set; } = 30;

        public int ExtraLarge { get; set; } = 40;

        public int Padding { get; set; } = 15;
    }
}
