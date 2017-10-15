using System;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering.Html
{
    public class RenderContext
    {
        public RenderContext(HostConfig hostConfig, ElementRenderers<HtmlTag, RenderContext> elementRenderers)
        {
            // clone it
            this.Config = JsonConvert.DeserializeObject<HostConfig>(JsonConvert.SerializeObject(hostConfig));
            this.ElementRenderers = elementRenderers;
        }

        public HostConfig Config { get; set; }

        public ElementRenderers<HtmlTag, RenderContext> ElementRenderers { get; set; }

        /// <summary>
        /// Helper to deal with casting
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        public HtmlTag Render(TypedElement element)
        {
            return this.ElementRenderers.Get(element.GetType())(element, this);
        }


        public string GetColor(TextColor color, bool isSubtle)
        {
            FontColorConfig colorConfig;
            switch (color)
            {
                case TextColor.Accent:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Accent;
                    break;
                case TextColor.Good:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Good;
                    break;
                case TextColor.Warning:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Warning;
                    break;
                case TextColor.Attention:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Attention;
                    break;
                case TextColor.Dark:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Dark;
                    break;
                case TextColor.Light:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Light;
                    break;
                default:
                    colorConfig = Config.ContainerStyles.Default.FontColors.Default;
                    break;
            }
            return GetRGBColor(isSubtle ? colorConfig.Subtle : colorConfig.Normal);
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
