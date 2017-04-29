using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColumnOptions
    {
        public ColumnOptions() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        public SeparationOptions Separations { get; set; } = new SeparationOptions();
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerOptions : CardElementOptions
    {
        public ContainerOptions() { }

        public ContainerStyleOptions Normal { get; set; } = new ContainerStyleOptions();

        public ContainerStyleOptions Emphasis { get; set; } = new ContainerStyleOptions() { };
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ActionSetOptions : CardElementOptions
    {
        public ActionSetOptions() { }
    }


    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColumnSetOptions : CardElementOptions
    {
        public ColumnSetOptions() { }
    }

}
