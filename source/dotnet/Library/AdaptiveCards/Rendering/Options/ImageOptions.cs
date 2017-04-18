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
    public class ImageOptions : CardElementOptions
    {
        public ImageOptions() { }
    }


    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSetOptions : CardElementOptions
    {
        public ImageSetOptions() { }

        public ImageSize ImageSize { get; set; } = ImageSize.Medium;
    }

}
