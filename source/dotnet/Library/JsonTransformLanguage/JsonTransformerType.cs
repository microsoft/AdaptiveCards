using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerType
    {
        [JsonProperty(PropertyName = "def")]
        public JToken Definition { get; set; }

        public JToken GetDefinition()
        {
            return Definition;
        }
    }
}
