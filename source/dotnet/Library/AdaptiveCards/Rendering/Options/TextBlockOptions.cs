using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Options
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TextOptions
    {
        public TextOptions()
        { }

        /// <summary>
        ///  The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize Size { get; set; } = TextSize.Normal;

        /// <summary>
        ///  The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight Weight { get; set; } = TextWeight.Normal;

        /// <summary>
        ///  The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor Color { get; set; } = TextColor.Default;

        /// <summary>
        ///   Should it be subtle?
        /// </summary>
        public bool IsSubtle { get; set; } = false;

        /// <summary>
        ///  Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool Wrap { get; set; }

        public bool ShouldSerializeSize()
        {
            return Size != TextSize.Normal;
        }

        public bool ShouldSerializeColor()
        {
            return Color != TextColor.Default;
        }


        public bool ShouldSerializeWeight()
        {
            return Weight != TextWeight.Normal;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TextBlockOptions
    {
        public TextBlockOptions()
        { }

        public TextSizeSepartations Seperations { get; set; } = new TextSizeSepartations();
    }



    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]

    public class TextSizeSepartations
    {
        public TextSizeSepartations()
        {
        }

        public SeparationOption Small { get; set; } = new SeparationOption() { Spacing = 10 };

        public SeparationOption Normal { get; set; } = new SeparationOption() { Spacing = 10 };

        public SeparationOption Medium { get; set; } = new SeparationOption() { Spacing = 10 };

        public SeparationOption Large { get; set; } = new SeparationOption() { Spacing = 10 };

        public SeparationOption ExtraLarge { get; set; } = new SeparationOption() { Spacing = 10 };

    }
}
