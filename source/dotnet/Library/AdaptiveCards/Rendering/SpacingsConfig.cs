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
        /// <summary>
        /// Small spacing config
        /// </summary>
        public int Small { get; set; } = 3;

        /// <summary>
        /// Default spacing config
        /// </summary>
        public int Default { get; set; } = 8;

        /// <summary>
        /// Medium spacing config
        /// </summary>
        public int Medium { get; set; } = 20;

        /// <summary>
        /// Large spacing config
        /// </summary>
        public int Large { get; set; } = 30;

        /// <summary>
        /// ExtraLarge spacing config
        /// </summary>
        public int ExtraLarge { get; set; } = 40;

        /// <summary>
        /// Padding config
        /// </summary>
        public int Padding { get; set; } = 15;
    }
}
