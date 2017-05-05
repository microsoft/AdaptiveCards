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
    public class ImageSetConfig : CardElementConfig
    {
        public ImageSetConfig() { }

        public ImageSize ImageSize { get; set; } = ImageSize.Medium;
    }

}
