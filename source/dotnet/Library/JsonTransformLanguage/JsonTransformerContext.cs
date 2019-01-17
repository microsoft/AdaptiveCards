using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerContext
    {
        public JsonTransformerContext(JToken rootData, Dictionary<string, JToken> additionalReservedProperties)
        {
            RootData = rootData;
            ParentData = rootData;
            Index = -1;
            ParentIsArray = false;
            Types = new JsonTransformerTypes();
            if (additionalReservedProperties != null)
            {
                foreach (var item in additionalReservedProperties)
                {
                    AdditionalReservedProperties[item.Key] = item.Value;
                }
            }
        }

        public JToken ParentData { get; set; }

        public JToken Props { get; set; }

        public int Index { get; set; }

        public bool ParentIsArray { get; set; }

        public JToken RootData { get; private set; }

        public JsonTransformerTypes Types { get; set; }

        public Dictionary<string, JToken> AdditionalReservedProperties { get; private set; } = new Dictionary<string, JToken>();

        public JsonTransformerWarnings Warnings { get; private set; } = new JsonTransformerWarnings();

        public JsonTransformerContext(JsonTransformerContext existingContext)
        {
            foreach (var p in this.GetType().GetTypeInfo().DeclaredProperties)
            {
                p.SetValue(this, p.GetValue(existingContext));
            }

            if (Types != null)
            {
                Types = Types.Clone();
            }
        }
    }
}
