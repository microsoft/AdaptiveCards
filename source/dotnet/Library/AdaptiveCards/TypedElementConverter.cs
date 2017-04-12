using System;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Xml.Serialization;
using System.Collections.Generic;

namespace AdaptiveCards
{
    /// <summary>
    ///     This handles using @type field to instantiate strongly typed object on deserialization
    /// </summary>
    public class TypedElementConverter : JsonConverter
    {
        /// <summary>
        /// List of additional types to support, register any new types to this list 
        /// </summary>
        internal static Lazy<Dictionary<string, Type>> g_typedElementTypes = new Lazy<Dictionary<string, Type>>(() =>
        {
            return typeof(TypedElement).GetTypeInfo().Assembly.ExportedTypes
                .Where(exportedType => exportedType.Namespace.Contains("AdaptiveCards"))
                .ToDictionary(type => type.Name);
        });

        public static void RegisterTypedElement<TypeT>()
            where TypeT : TypedElement
        {
            g_typedElementTypes.Value.Add(typeof(TypeT).Name, typeof(TypeT));
        }

        public override bool CanRead => true;

        public override bool CanWrite => false;

        public override bool CanConvert(Type objectType)
        {
            return typeof(TypedElement).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);
            // Create target object based on JObject
            var typeName = jObject["type"]?.Value<string>() ?? jObject["@type"]?.Value<string>();
            object result = jObject;
            if (typeName != null)
            {
                typeName = typeName.Replace(".", string.Empty);

                Type type = null;
                if (g_typedElementTypes.Value.TryGetValue(typeName, out type))
                {
                    result = Activator.CreateInstance(type);
                }
                // Populate the object properties
                serializer.Populate(jObject.CreateReader(), result);
            }

            return result;
        }
    }
}