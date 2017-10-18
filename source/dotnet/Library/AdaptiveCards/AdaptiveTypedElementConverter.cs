using System;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

using System.Collections.Generic;

namespace AdaptiveCards
{
    /// <summary>
    ///     This handles using @type field to instantiate strongly typed object on deserialization
    /// </summary>
    public class AdaptiveTypedElementConverter : JsonConverter
    {
        /// <summary>
        /// Default types to support, register any new types to this list 
        /// </summary>
        private static readonly Lazy<Dictionary<string, Type>> TypedElementTypes = new Lazy<Dictionary<string, Type>>(() =>
        {
            Dictionary<string, Type> types = new Dictionary<string, Type>();
            types[AdaptiveCard.TypeName] = typeof(AdaptiveCard);
            types[AdaptiveTextBlock.TypeName] = typeof(AdaptiveTextBlock);
            types[AdaptiveImage.TypeName] = typeof(AdaptiveImage);
            types[AdaptiveContainer.TypeName] = typeof(AdaptiveContainer);
            types[AdaptiveColumn.TypeName] = typeof(AdaptiveColumn);
            types[AdaptiveColumnSet.TypeName] = typeof(AdaptiveColumnSet);
            types[AdaptiveFactSet.TypeName] = typeof(AdaptiveFactSet);
            types[AdaptiveImageSet.TypeName] = typeof(AdaptiveImageSet);
            types[AdaptiveTextInput.TypeName] = typeof(AdaptiveTextInput);
            types[AdaptiveDateInput.TypeName] = typeof(AdaptiveDateInput);
            types[AdaptiveTimeInput.TypeName] = typeof(AdaptiveTimeInput);
            types[AdaptiveChoiceSetInput.TypeName] = typeof(AdaptiveChoiceSetInput);
            types[AdaptiveNumberInput.TypeName] = typeof(AdaptiveNumberInput);
            types[AdaptiveToggleInput.TypeName] = typeof(AdaptiveToggleInput);
            types[AdaptiveSubmitAction.TypeName] = typeof(AdaptiveSubmitAction);
            types[AdaptiveOpenUrlAction.TypeName] = typeof(AdaptiveOpenUrlAction);
            types[AdaptiveShowCardAction.TypeName] = typeof(AdaptiveShowCardAction);
            return types;
        });

        public static void RegisterTypedElement<T>(string typeName = null)
            where T : AdaptiveTypedElement
        {
            if (typeName == null)
                typeName = ((AdaptiveTypedElement)Activator.CreateInstance(typeof(T))).Type;

            TypedElementTypes.Value[typeName] = typeof(T);
        }

        public override bool CanRead => true;

        public override bool CanWrite => false;

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveTypedElement).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
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
                Type type = null;
                if (TypedElementTypes.Value.TryGetValue(typeName, out type))
                {
                    result = Activator.CreateInstance(type);
                }
                else
                    throw new ArgumentException($"Unknown Type={typeName}");

                // Populate the object properties
                serializer.Populate(jObject.CreateReader(), result);
            }

            return result;
        }

        public static T CreateElement<T>(string typeName = null)
            where T : AdaptiveTypedElement
        {
            if (typeName == null)
                typeName = ((T)Activator.CreateInstance(typeof(T))).Type;

            Type type = null;
            if (TypedElementTypes.Value.TryGetValue(typeName, out type))
            {
                return (T)Activator.CreateInstance(type);
            }
            return null;
        }
    }
}