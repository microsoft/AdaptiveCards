// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontWeightsConfig
    {
        public int? Lighter { get; set; }

        public int? Default { get; set; }

        public int? Bolder { get; set; }

        public int? GetFontWeight(AdaptiveTextWeight fontWeight)
        {
            switch (fontWeight)
            {
                case AdaptiveTextWeight.Lighter:
                    return Lighter;
                case AdaptiveTextWeight.Bolder:
                    return Bolder;
                case AdaptiveTextWeight.Default:
                default:
                    return Default;
            }
        }

        public static int GetDefaultFontWeight(AdaptiveTextWeight fontWeight)
        {
            switch (fontWeight)
            {
                case AdaptiveTextWeight.Lighter:
                    return 200;
                case AdaptiveTextWeight.Bolder:
                    return 600;
                case AdaptiveTextWeight.Default:
                default:
                    return 400;
            }
        }
    }
}
