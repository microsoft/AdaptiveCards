using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerTypes : Dictionary<string, JsonTransformerType>
    {
        public JsonTransformerTypes() { }

        private JsonTransformerTypes(JsonTransformerTypes existing) : base(existing) { }

        public JsonTransformerTypes Merge(JsonTransformerTypes other)
        {
            var answer = Clone();
            if (other != null)
            {
                foreach (var item in other)
                {
                    answer[item.Key] = item.Value;
                }
            }
            return answer;
        }

        public JsonTransformerTypes Clone()
        {
            return new JsonTransformerTypes(this);
        }

        public bool TryGetDefinition(string type, out JToken definition)
        {
            if (TryGetValue(type, out JsonTransformerType typeValue))
            {
                definition = typeValue.GetDefinition();
                return true;
            }

            definition = null;
            return false;
        }
    }
}
