// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    /// <summary>
    /// FontSizes conffig
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontSizesConfig
    {
        /// <summary>
        /// font size for small
        /// </summary>
        public int? Small { get; set; }

        /// <summary>
        /// font size for default
        /// </summary>
        public int? Default { get; set; }

        /// <summary>
        /// font size for medium
        /// </summary>
        public int? Medium { get; set; }

        /// <summary>
        /// font size for large
        /// </summary>
        public int? Large { get; set; }

        /// <summary>
        /// font size for extra large
        /// </summary>
        public int? ExtraLarge { get; set; }

        /// <summary>
        ///  Given AdaptiveTextSize get the font size in real size.
        /// </summary>
        /// <param name="fontSize"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Given a textSize return the default font size.
        /// </summary>
        /// <param name="fontSize"></param>
        /// <returns></returns>
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
