// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontSizesConfig
    {
        public int? Small { get; set; }

        public int? Default { get; set; }

        public int? Medium { get; set; }

        public int? Large { get; set; }

        public int? ExtraLarge { get; set; }

        public int? GetFontSize(AdaptiveTextSize fontSize)
        {
            switch (fontSize)
            {
                case AdaptiveTextSize.Small:
                    return Small;
                case AdaptiveTextSize.Medium:
                    return Medium;
                case AdaptiveTextSize.Large:
                    return Large;
                case AdaptiveTextSize.ExtraLarge:
                    return ExtraLarge;
                case AdaptiveTextSize.Default:
                default:
                    return Default;
            }
        }

        public static int GetDefaultFontSize(AdaptiveTextSize fontSize)
        {
            switch (fontSize)
            {
                case AdaptiveTextSize.Small:
                    return 12;
                case AdaptiveTextSize.Medium:
                    return 17;
                case AdaptiveTextSize.Large:
                    return 21;
                case AdaptiveTextSize.ExtraLarge:
                    return 26;
                case AdaptiveTextSize.Default:
                default:
                    return 14;
            }
        }
    }
}
