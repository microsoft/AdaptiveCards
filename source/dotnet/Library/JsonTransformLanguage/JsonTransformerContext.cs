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
            ReservedProperties = new JsonTransformerReservedProperties()
            {
                RootData = rootData,
                Data = rootData,
                Index = null,
                Props = null,
                AdditionalReservedProperties = additionalReservedProperties ?? new Dictionary<string, JToken>()
            };
            ParentIsArray = false;
            Types = new JsonTransformerTypes();
        }

        public JsonTransformerReservedProperties ReservedProperties { get; set; }

        public bool ParentIsArray { get; set; }

        public JsonTransformerTypes Types { get; set; }

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

            if (ReservedProperties != null)
            {
                ReservedProperties = new JsonTransformerReservedProperties(ReservedProperties);
            }
        }
    }
}
