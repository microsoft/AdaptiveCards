using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerContext
    {
        public JsonTransformerContext(JToken rootData, Dictionary<string, JToken> additionalReservedProperties)
        {
            RootData = rootData;
            if (additionalReservedProperties != null)
            {
                foreach (var item in additionalReservedProperties)
                {
                    AdditionalReservedProperties[item.Key] = item.Value;
                }
            }
        }

        public JToken RootData { get; }

        public Dictionary<string, JToken> AdditionalReservedProperties { get; } = new Dictionary<string, JToken>();

        public JsonTransformerWarnings Warnings { get; } = new JsonTransformerWarnings();
    }
}
