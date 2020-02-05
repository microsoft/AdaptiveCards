// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSetConfig
    {
        public ImageSetConfig() { }

        public AdaptiveImageSize ImageSize { get; set; } = AdaptiveImageSize.Medium;
    }

}
