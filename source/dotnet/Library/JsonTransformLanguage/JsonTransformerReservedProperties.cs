using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace JsonTransformLanguage
{
    /// <summary>
    /// Reserved variables/properties like $data, $rootData, $index are all defined here.
    /// </summary>
    public class JsonTransformerReservedProperties
    {
        public JsonTransformerReservedProperties() { }

        public JsonTransformerReservedProperties(JsonTransformerReservedProperties existing)
        {
            foreach (var p in this.GetType().GetTypeInfo().DeclaredProperties)
            {
                p.SetValue(this, p.GetValue(existing));
            }
        }

        public JToken Data { get; set; }
        public JToken Index { get; set; }
        public JToken Props { get; set; }
        public JToken RootData { get; set; }

        public Dictionary<string, JToken> AdditionalReservedProperties { get; set; }

        /// <summary>
        /// The name, like "data" (no leading $)
        /// </summary>
        /// <param name="reservedPropertyName"></param>
        /// <returns></returns>
        public JToken GetValue(string reservedPropertyName)
        {
            var p = this.GetType().GetTypeInfo().DeclaredProperties.FirstOrDefault(i => ToCamelCase(i.Name) == reservedPropertyName);
            if (p != null)
            {
                return p.GetValue(this) as JToken;
            }

            return null;
        }

        private static string ToCamelCase(string propertyName)
        {
            return propertyName.Substring(0, 1).ToLower() + propertyName.Substring(1);
        }
    }
}
