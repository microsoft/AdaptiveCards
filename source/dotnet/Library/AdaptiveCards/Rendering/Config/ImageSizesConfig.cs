using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSizesConfig

    {
        public ImageSizesConfig() { }

        public int Small { get; set; } = 60;

        public int Medium { get; set; } = 120;

        public int Large { get; set; } = 180;
    }
}
