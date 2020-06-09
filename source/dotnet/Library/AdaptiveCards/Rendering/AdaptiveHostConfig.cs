// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveHostConfig : AdaptiveConfigBase
    {
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ActionsConfig Actions { get; set; } = new ActionsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveCardConfig AdaptiveCard { get; set; } = new AdaptiveCardConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ContainerStylesConfig ContainerStyles { get; set; } = new ContainerStylesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSizesConfig ImageSizes { get; set; } = new ImageSizesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSetConfig ImageSet { get; set; } = new ImageSetConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FactSetConfig FactSet { get; set; } = new FactSetConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontFamily has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontFamily", false)]
        public string FontFamily { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontSizes has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontSizes", false)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontWeights has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontWeights", false)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontTypesConfig FontTypes { get; set; } = new FontTypesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public SpacingsConfig Spacing { get; set; } = new SpacingsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public SeparatorConfig Separator { get; set; } = new SeparatorConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public MediaConfig Media { get; set; } = new MediaConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public InputsConfig Inputs { get; set; } = new InputsConfig();

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// Image Base URL for relative URLs
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public Uri ImageBaseUrl { get; set; } = null;

        public Uri ResolveFinalAbsoluteUri(string uriString)
        {
            Uri uri;
            try
            {
                uri = new Uri(uriString, UriKind.RelativeOrAbsolute);
            }
            catch (UriFormatException)
            {
                return null;
            }

            return ResolveFinalAbsoluteUri(uri);
        }

        /** Get the absolute URI either by itself or using imageBaseUrl */
        public Uri ResolveFinalAbsoluteUri(Uri uri)
        {
            if (uri == null)
            {
                return null;
            }

            if (uri.IsAbsoluteUri)
            {
                return uri;
            }

            if (ImageBaseUrl != null)
            {
                try
                {
                    Uri finalUri = new Uri(ImageBaseUrl, uri.ToString());
                    if (finalUri.IsAbsoluteUri)
                    {
                        return finalUri;
                    }
                }
                catch (UriFormatException)
                {
                    return null;
                }
                catch (ArgumentOutOfRangeException)
                {
                    return null;
                }
            }

            return null;
        }

        public int GetSpacing(AdaptiveSpacing spacing)
        {
            switch (spacing)
            {
                case AdaptiveSpacing.None:
                    return 0;

                case AdaptiveSpacing.Small:
                    return Spacing.Small;

                case AdaptiveSpacing.Medium:
                    return Spacing.Medium;

                case AdaptiveSpacing.Large:
                    return Spacing.Large;

                case AdaptiveSpacing.ExtraLarge:
                    return Spacing.ExtraLarge;

                case AdaptiveSpacing.Padding:
                    return Spacing.Padding;

                default:
                    return Spacing.Default;
            }
        }

        public static AdaptiveHostConfig FromJson(string json)
        {
            try
            {
                return JsonConvert.DeserializeObject<AdaptiveHostConfig>(json, new JsonSerializerSettings
                {
                    Converters = { new StrictIntConverter() }
                });
            }
            catch (JsonException ex)
            {
                throw new AdaptiveSerializationException(ex.Message, ex);
            }
        }

        /// <summary>
        ///  Serialize this Host Config to JSON
        /// </summary>
        /// <returns></returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }

// Ignore deprecation warnings for Font[Family|Weights|Sizes]
#pragma warning disable 0618
        // Handles inheritance behavior for retrieving the name of the font family given the desired AdaptiveFontType
        public string GetFontFamily(AdaptiveFontType fontType)
        {
            // Value saved in FontTypes.<desiredStyle>
            string fontFamilyValue = FontTypes.GetFontType(fontType).FontFamily;

            if (string.IsNullOrWhiteSpace(fontFamilyValue))
            {
                if (fontType == AdaptiveFontType.Monospace)
                {
                    fontFamilyValue = GetDefaultFontFamily(fontType);
                }
                else
                {
                    // Fallback to deprecated fontFamily value
                    fontFamilyValue = FontFamily;
                    if (string.IsNullOrEmpty(fontFamilyValue))
                    {
                        // Fallback to predefined system default value
                        fontFamilyValue = GetDefaultFontFamily(fontType);
                    }
                }
            }
            return fontFamilyValue;
        }

        public int GetFontWeight(AdaptiveFontType fontType, AdaptiveTextWeight requestedWeight)
        {
            return FontTypes.GetFontType(fontType).FontWeights.GetFontWeight(requestedWeight)
                ?? FontTypes.Default.FontWeights.GetFontWeight(requestedWeight)
                ?? FontWeights.GetFontWeight(requestedWeight)
                ?? FontWeightsConfig.GetDefaultFontWeight(requestedWeight);
        }

        public int GetFontSize(AdaptiveFontType fontType, AdaptiveTextSize requestedSize)
        {
            return FontTypes.GetFontType(fontType).FontSizes.GetFontSize(requestedSize)
                ?? FontTypes.Default.FontSizes.GetFontSize(requestedSize)
                ?? FontSizes.GetFontSize(requestedSize)
                ?? FontSizesConfig.GetDefaultFontSize(requestedSize);
        }
#pragma warning restore 0618

        private string GetDefaultFontFamily(AdaptiveFontType fontType)
        {
            switch (fontType)
            {
                case AdaptiveFontType.Monospace:
                    return "Courier New";
                case AdaptiveFontType.Default:
                default:
                    // Leave it up to the platform.
                    // Renderer default is usually "Segoe UI"
                    return "";
            }
        }
    }
}
