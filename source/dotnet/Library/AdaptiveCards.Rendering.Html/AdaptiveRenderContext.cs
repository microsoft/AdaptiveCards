// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering.Html
{
    public class AdaptiveRenderContext
    {
        public AdaptiveRenderContext(AdaptiveHostConfig hostConfig, AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext> elementRenderers)
        {
            // clone it
            Config = JsonConvert.DeserializeObject<AdaptiveHostConfig>(JsonConvert.SerializeObject(hostConfig));
            ElementRenderers = elementRenderers;
            RenderArgs = new AdaptiveRenderArgs { ForegroundColors = Config.ContainerStyles.Default.ForegroundColors };
        }

        public AdaptiveHostConfig Config { get; set; }

        public AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext> ElementRenderers { get; set; }

        public AdaptiveFeatureRegistration FeatureRegistration { get; set; }

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public IList<HtmlTag> ShowCardTags { get; } = new List<HtmlTag>();

        private bool AncestorHasFallback = false;

        public HtmlTag Render(AdaptiveTypedElement element)
        {
            HtmlTag htmlTagOut = null;
            var oldAncestorHasFallback = AncestorHasFallback;
            var elementHasFallback = element != null && element.Fallback != null && (element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None);
            AncestorHasFallback = AncestorHasFallback || elementHasFallback;

            try
            {
                if (AncestorHasFallback && !element.MeetsRequirements(FeatureRegistration))
                {
                    throw new AdaptiveFallbackException("Element requirements aren't met");
                }

                // If non-interactive, inputs should just render text
                if (!Config.SupportsInteractivity && element is AdaptiveInput input)
                {
                    var tb = new AdaptiveTextBlock();
                    tb.Text = input.GetNonInteractiveValue();
                    Warnings.Add(new AdaptiveWarning(-1, $"Rendering non-interactive input element '{element.Type}'"));
                    htmlTagOut = Render(tb);
                }

                if (htmlTagOut == null)
                {
                    var renderer = ElementRenderers.Get(element.GetType());
                    if (renderer != null)
                    {
                        htmlTagOut = renderer.Invoke(element, this);
                    }
                }
            }
            catch (AdaptiveFallbackException)
            {
                if (!elementHasFallback)
                {
                    throw;
                }
            }

            if (htmlTagOut == null)
            {
                // Since no renderer exists for this element, add warning and render fallback (if available)
                if (element.Fallback != null && element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None)
                {
                    if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                    {
                        Warnings.Add(new AdaptiveWarning(-1, $"Dropping element for fallback '{element.Type}'"));
                    }
                    else if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Content && element.Fallback.Content != null)
                    {
                        // Render fallback content
                        htmlTagOut = Render(element.Fallback.Content);
                    }
                }
                else if (AncestorHasFallback)
                {
                    throw new AdaptiveFallbackException();
                }
                else
                {
                    Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element '{element.Type}'"));
                }
            }

            AncestorHasFallback = oldAncestorHasFallback;
            return htmlTagOut;
        }

        public string GetColor(AdaptiveTextColor color, bool isSubtle, bool isHighlight)
        {
            FontColorConfig colorConfig;
            switch (color)
            {
                case AdaptiveTextColor.Accent:
                    colorConfig = RenderArgs.ForegroundColors.Accent;
                    break;
                case AdaptiveTextColor.Good:
                    colorConfig = RenderArgs.ForegroundColors.Good;
                    break;
                case AdaptiveTextColor.Warning:
                    colorConfig = RenderArgs.ForegroundColors.Warning;
                    break;
                case AdaptiveTextColor.Attention:
                    colorConfig = RenderArgs.ForegroundColors.Attention;
                    break;
                case AdaptiveTextColor.Dark:
                    colorConfig = RenderArgs.ForegroundColors.Dark;
                    break;
                case AdaptiveTextColor.Light:
                    colorConfig = RenderArgs.ForegroundColors.Light;
                    break;
                default:
                    colorConfig = RenderArgs.ForegroundColors.Default;
                    break;
            }

            if (isHighlight)
            {
                return GetRGBColor(isSubtle ? colorConfig.HighlightColors.Subtle : colorConfig.HighlightColors.Default);
            }
            else
            {
                return GetRGBColor(isSubtle ? colorConfig.Subtle : colorConfig.Default);
            }
        }

        public string GetRGBColor(string color)
        {
            if (color?.StartsWith("#") == true)
            {
                if (color.Length == 7)
                    return color;
                if (color.Length == 9)
                {
                    var opacity = (float)Convert.ToByte(color.Substring(1, 2), 16) / Byte.MaxValue;
                    return $"rgba({Convert.ToByte(color.Substring(3, 2), 16)}, {Convert.ToByte(color.Substring(5, 2), 16)}, {Convert.ToByte(color.Substring(7, 2), 16)}, {opacity.ToString("F")})";
                }
            }
            return color;
        }

        public string Lang { get; set; }

        public AdaptiveRenderArgs RenderArgs { get; set; }
    }
}
