// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Contains host-configurable options for controlling rendering behavior.
    /// </summary>
    public class AdaptiveHostConfig : AdaptiveConfigBase
    {
        /// <summary>
        /// Properties which control rendering and behavior of actions.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ActionsConfig Actions { get; set; } = new ActionsConfig();

        /// <summary>
        /// Properties that control the rendering and behavior of the toplevel Adaptive Card.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveCardConfig AdaptiveCard { get; set; } = new AdaptiveCardConfig();

        /// <summary>
        /// Definitions of the various styles that can be applied to containers and container-like elements.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ContainerStylesConfig ContainerStyles { get; set; } = new ContainerStylesConfig();

        /// <summary>
        /// Controls the sizes at which images render.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSizesConfig ImageSizes { get; set; } = new ImageSizesConfig();

        /// <summary>
        /// Controls the default size at which images in an ImageSet are rendered.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSetConfig ImageSet { get; set; } = new ImageSetConfig();

        /// <summary>
        /// Controls the rendering of the FactSet element.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FactSetConfig FactSet { get; set; } = new FactSetConfig();

        /// <summary>
        /// Defines which font families to use during rendering. (Obsolete)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontFamily has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontFamily", false)]
        public string FontFamily { get; set; }

        /// <summary>
        /// Defines which font sizes to use during rendering. (Obsolete)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontSizes has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontSizes", false)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        /// <summary>
        /// Defines which font weights to use during rendering. (Obsolete)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [Obsolete("AdaptiveHostConfig.FontWeights has been deprecated.  Use AdaptiveHostConfig.FontTypes.Default.FontWeights", false)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();

        /// <summary>
        /// Defines font families, sizes, and weights to use during rendering.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontTypesConfig FontTypes { get; set; } = new FontTypesConfig();

        /// <summary>
        /// Defines the various values to use for spacing.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public SpacingsConfig Spacing { get; set; } = new SpacingsConfig();

        /// <summary>
        /// Controls the appearance of the separator.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public SeparatorConfig Separator { get; set; } = new SeparatorConfig();

        /// <summary>
        /// Controls the rendering and behavior of media elements.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public MediaConfig Media { get; set; } = new MediaConfig();

        /// <summary>
        /// Controls the rendering and behavior of input elements.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public InputsConfig Inputs { get; set; } = new InputsConfig();

        /// <summary>
        /// Toggles whether or not to render inputs and actions.
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// Image Base URL for relative URLs.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public Uri ImageBaseUrl { get; set; } = null;

        /// <summary>
        /// Resolves a URI string in an absolute <see cref="Uri"/>.
        /// </summary>
        /// <param name="uriString">The URI to resolve.</param>
        /// <returns>The absolute Uri that uriString represents.</returns>
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

        /// <summary>
        /// Converts a Uri into absolute form using <see cref="ImageBaseUrl"/> as needed.
        /// </summary>
        /// <param name="uri">URI to resolve.</param>
        /// <returns>An absolute URI for uri.</returns>
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

        /// <summary>
        /// Get the numeric value of spacing to use for a given spacing type.
        /// </summary>
        /// <param name="spacing">The spacing to look up.</param>
        /// <returns>The numeric value for the type of spacing.</returns>
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

        /// <summary>
        /// Constructs an <see cref="AdaptiveHostConfig"/> instance from the given JSON.
        /// </summary>
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
        /// Serialize this Host Config to JSON.
        /// </summary>
        /// <returns>A JSON string representation of this Host Config.</returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }

// Ignore deprecation warnings for Font[Family|Weights|Sizes]
#pragma warning disable 0618
        /// <summary>
        /// Retrieves the name of the font family given the desired AdaptiveFontType.
        /// </summary>
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

        /// <summary>
        /// Retrieves a font weight for an AdaptiveFontType.
        /// </summary>
        public int GetFontWeight(AdaptiveFontType fontType, AdaptiveTextWeight requestedWeight)
        {
            return FontTypes.GetFontType(fontType).FontWeights.GetFontWeight(requestedWeight)
                ?? FontTypes.Default.FontWeights.GetFontWeight(requestedWeight)
                ?? FontWeights.GetFontWeight(requestedWeight)
                ?? FontWeightsConfig.GetDefaultFontWeight(requestedWeight);
        }

        /// <summary>
        /// Retrieves a font size for an AdaptiveFontType.
        /// </summary>
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
