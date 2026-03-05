// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Base class for configuration-holding renderer classes.
    /// </summary>
    public abstract class AdaptiveConfigBase
    {
        /// <summary>
        /// Holds additional data in a configuration that doesn't map to known properties.
        /// </summary>
        [JsonExtensionData]
        public Dictionary<string, JsonElement> AdditionalData { get; set; } = new Dictionary<string, JsonElement>();
    }
}
