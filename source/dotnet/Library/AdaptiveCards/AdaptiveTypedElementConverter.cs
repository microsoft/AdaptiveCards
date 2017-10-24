using System;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

using System.Collections.Generic;
using System.Diagnostics;

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
            // TODO: Should this be a static? It makes it impossible to have diff renderers support different elements
            var types = new Dictionary<string, Type>
            {
                [AdaptiveCard.TypeName] = typeof(AdaptiveCard),
                [AdaptiveTextBlock.TypeName] = typeof(AdaptiveTextBlock),
                [AdaptiveImage.TypeName] = typeof(AdaptiveImage),
                [AdaptiveContainer.TypeName] = typeof(AdaptiveContainer),
                [AdaptiveColumn.TypeName] = typeof(AdaptiveColumn),
                [AdaptiveColumnSet.TypeName] = typeof(AdaptiveColumnSet),
                [AdaptiveFactSet.TypeName] = typeof(AdaptiveFactSet),
                [AdaptiveImageSet.TypeName] = typeof(AdaptiveImageSet),
                [AdaptiveTextInput.TypeName] = typeof(AdaptiveTextInput),
                [AdaptiveDateInput.TypeName] = typeof(AdaptiveDateInput),
                [AdaptiveTimeInput.TypeName] = typeof(AdaptiveTimeInput),
                [AdaptiveChoiceSetInput.TypeName] = typeof(AdaptiveChoiceSetInput),
                [AdaptiveNumberInput.TypeName] = typeof(AdaptiveNumberInput),
                [AdaptiveToggleInput.TypeName] = typeof(AdaptiveToggleInput),
                [AdaptiveSubmitAction.TypeName] = typeof(AdaptiveSubmitAction),
                [AdaptiveOpenUrlAction.TypeName] = typeof(AdaptiveOpenUrlAction),
                [AdaptiveShowCardAction.TypeName] = typeof(AdaptiveShowCardAction)
            };
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
            return typeof(AdaptiveTypedElement).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo()) 
                && TypedElementTypes.Value.ContainsValue(objectType);
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);
            // Create target object based on JObject
            var typeName = jObject["type"]?.Value<string>() ?? jObject["@type"]?.Value<string>();
            if (typeName == null)
            {
                // TODO: log warning, missing type name
                return null;
            }

            if (TypedElementTypes.Value.TryGetValue(typeName, out var type))
            {
                var result = Activator.CreateInstance(type);
                serializer.Populate(jObject.CreateReader(), result);
                return result;
            }
            
            // TODO: log unknown element type 
            return null;
        }

        public static T CreateElement<T>(string typeName = null)
            where T : AdaptiveTypedElement
        {
            if (typeName == null)
                typeName = ((T)Activator.CreateInstance(typeof(T))).Type;

            if (TypedElementTypes.Value.TryGetValue(typeName, out var type))
            {
                return (T)Activator.CreateInstance(type);
            }
            return null;
        }
    }
}