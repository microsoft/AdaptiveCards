using System;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// This handles using @type field to instantiate strongly typed object on deserialization
    /// </summary>
    public class TypedElementConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return typeof(TypedElement).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            JObject jObject = JObject.Load(reader);
            // Create target object based on JObject
            string typeName = jObject["type"]?.Value<string>() ?? jObject["@type"]?.Value<string>();
            object result = jObject;
            if (typeName != null)
            {
                typeName = typeName.Replace(".", string.Empty);
                var type = typeof(TypedElement).GetTypeInfo().Assembly.ExportedTypes
                    .Where(t => t.Namespace.Contains("AdaptiveCards"))
                    .FirstOrDefault(t => string.Equals(t.Name, typeName, StringComparison.CurrentCultureIgnoreCase));
                if (type != null)
                {
                    result = Activator.CreateInstance(type);
                }
                // Populate the object properties
                serializer.Populate(jObject.CreateReader(), result);
            }

            return result;
        }

        public override bool CanRead => true;

        public override bool CanWrite => false;
    }

}
