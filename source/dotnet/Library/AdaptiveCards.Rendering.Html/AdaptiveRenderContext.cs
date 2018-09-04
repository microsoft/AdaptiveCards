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
        }

        public AdaptiveHostConfig Config { get; set; }

        public AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext> ElementRenderers { get; set; }

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public HtmlTag Render(AdaptiveTypedElement element)
        {
            // If non-inertactive, inputs should just render text
            if (!Config.SupportsInteractivity && element is AdaptiveInput input)
            {
                var tb = new AdaptiveTextBlock();
                tb.Text = input.GetNonInteractiveValue();
                Warnings.Add(new AdaptiveWarning(-1, $"Rendering non-interactive input element '{element.Type}'"));
                return Render(tb);
            }

            var renderer = ElementRenderers.Get(element.GetType());
            if (renderer != null)
            {
                return renderer.Invoke(element, this);
            }
            else
            {
                Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element '{element.Type}'"));
                return null;
            }
        }


        public string GetColor(AdaptiveTextColor color, bool isSubtle)
        {
            FontColorConfig colorConfig;
            switch (color)
            {
                case AdaptiveTextColor.Accent:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Accent;
                    break;
                case AdaptiveTextColor.Good:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Good;
                    break;
                case AdaptiveTextColor.Warning:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Warning;
                    break;
                case AdaptiveTextColor.Attention:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Attention;
                    break;
                case AdaptiveTextColor.Dark:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Dark;
                    break;
                case AdaptiveTextColor.Light:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Light;
                    break;
                default:
                    colorConfig = Config.ContainerStyles.Default.ForegroundColors.Default;
                    break;
            }
            return GetRGBColor(isSubtle ? colorConfig.Subtle : colorConfig.Default);
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
    }
}
