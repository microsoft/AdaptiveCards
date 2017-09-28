using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using HtmlTags;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
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
            ColorConfig colorConfig;
            switch (color)
            {
                case TextColor.Accent:
                    colorConfig = Config.Colors.Accent;
                    break;
                case TextColor.Good:
                    colorConfig = Config.Colors.Good;
                    break;
                case TextColor.Warning:
                    colorConfig = Config.Colors.Warning;
                    break;
                case TextColor.Attention:
                    colorConfig = Config.Colors.Attention;
                    break;
                case TextColor.Dark:
                    colorConfig = Config.Colors.Dark;
                    break;
                case TextColor.Light:
                    colorConfig = Config.Colors.Light;
                    break;
                default:
                    colorConfig = Config.Colors.Default;
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

        public SeparationConfig GetElementSeparation(TypedElement element)
        {
            switch(element.Type)
            {
                case TextBlock.TYPE:
                    TextBlock tb = (TextBlock)element;
                    switch(tb.Size)
                    {
                        case TextSize.Small:
                            return this.Config.TextBlock.Separations.Small;
                        case TextSize.Medium:
                            return this.Config.TextBlock.Separations.Medium;
                        case TextSize.Large:
                            return this.Config.TextBlock.Separations.Large;
                        case TextSize.ExtraLarge:
                            return this.Config.TextBlock.Separations.ExtraLarge;
                        case TextSize.Default:
                        default:
                            return this.Config.TextBlock.Separations.Normal;
                    }

                case Image.TYPE:
                    return this.Config.Image.Separation;
                case Container.TYPE:
                    return this.Config.Container.Separation;
                case ColumnSet.TYPE:
                    return this.Config.ColumnSet.Separation;
                case Column.TYPE:
                    return this.Config.Column.Separation;
                case ImageSet.TYPE:
                    return this.Config.ImageSet.Separation;
                case ChoiceSet.TYPE:
                    return this.Config.ChoiceSet.Separation;
                case TextInput.TYPE:
                    return this.Config.ImageSet.Separation;
                case DateInput.TYPE:
                    return this.Config.DateInput.Separation;
                case TimeInput.TYPE:
                    return this.Config.TimeInput.Separation;
                case NumberInput.TYPE:
                    return this.Config.NumberInput.Separation;
                case ToggleInput.TYPE:
                    return this.Config.ToggleInput.Separation;
                case FactSet.TYPE:
                    return this.Config.FactSet.Separation;
            }
            throw new Exception("Unknown type " + element.Type);
        }

    }
}
