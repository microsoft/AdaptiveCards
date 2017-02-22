using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Adaptive
{
    /// <summary>
    /// This handles using @type field to instantiate strongly typed object on deserialization
    /// </summary>
    public partial class TypedElementConverter : JsonConverter
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
                var type = typeof(TypedElement).GetTypeInfo().Assembly.ExportedTypes.FirstOrDefault(t => t.Name.ToLower() == typeName.ToLower());
                if (type != null)
                {
                    result = Activator.CreateInstance(type);
                }
                // Populate the object properties
                serializer.Populate(jObject.CreateReader(), result);
            }

            return result;
        }

        public override bool CanRead { get { return true; } }

        public override bool CanWrite { get { return false; } }
    }

}
