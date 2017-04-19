using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Options
{

    /// <summary>
    /// Properties which control spacing and visual between elements
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SeparationOptions
    {
        public SeparationOptions() { }

        /// <summary>
        /// Separation settings when Separation:default
        /// </summary>
        public SeparationOption Default { get; set; } = new SeparationOption() { Spacing = 10 };

        /// <summary>
        /// Separation settings when Separation:Strong
        /// </summary>
        public SeparationOption Strong { get; set; } = new SeparationOption() { Spacing = 20, LineThickness = 1, LineColor = "#FF707070" };
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SeparationOption
    {
        public SeparationOption() { }

        /// <summary>
        /// How much space between this element and previous should be used
        /// </summary>
        public int Spacing { get; set; }

        /// <summary>
        /// If there is a visible line, how thick should the line be
        /// </summary>
        public int LineThickness { get; set; }

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        public string LineColor { get; set; }

    }

}
