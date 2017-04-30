using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Config
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColumnSetConfig : CardElementConfig
    {
        public ColumnSetConfig() { }
    }

}
