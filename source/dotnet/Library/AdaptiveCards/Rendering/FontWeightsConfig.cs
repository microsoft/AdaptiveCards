// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// FontWeight config
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontWeightsConfig
    {
        /// <summary>
        /// Lighter config
        /// </summary>
        public int? Lighter { get; set; }

        /// <summary>
        /// Default confing
        /// </summary>
        public int? Default { get; set; }

        /// <summary>
        /// Bolder config
        /// </summary>
        public int? Bolder { get; set; }

        /// <summary>
        /// Given a textWeight get the fontweight config for it.
        /// </summary>
        /// <param name="fontWeight"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Given a text weight get the default font weight for it.
        /// </summary>
        /// <param name="fontWeight"></param>
        /// <returns></returns>
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
