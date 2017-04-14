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
        /// Default types to support, register any new types to this list 
        /// </summary>
        private static Lazy<Dictionary<string, Type>> g_typedElementTypes = new Lazy<Dictionary<string, Type>>(() =>
        {
            Dictionary<string, Type> types = new Dictionary<string, Type>();
            types[AdaptiveCard.TYPE] = typeof(AdaptiveCard);
            types[TextBlock.TYPE] = typeof(TextBlock);
            types[Image.TYPE] = typeof(Image);
            types[Container.TYPE] = typeof(Container);
            types[Column.TYPE] = typeof(Column);
            types[ColumnSet.TYPE] = typeof(ColumnSet);
            types[FactSet.TYPE] = typeof(FactSet);
            types[ImageSet.TYPE] = typeof(ImageSet);
            types[ActionSet.TYPE] = typeof(ActionSet);
            types[TextInput.TYPE] = typeof(TextInput);
            types[DateInput.TYPE] = typeof(DateInput);
            types[TimeInput.TYPE] = typeof(TimeInput);
            types[ChoiceSet.TYPE] = typeof(ChoiceSet);
            types[NumberInput.TYPE] = typeof(NumberInput);
            types[ToggleInput.TYPE] = typeof(ToggleInput);
            types[SubmitAction.TYPE] = typeof(SubmitAction);
            types[OpenUrlAction.TYPE] = typeof(OpenUrlAction);
            types[HttpAction.TYPE] = typeof(HttpAction);
            types[ShowCardAction.TYPE] = typeof(ShowCardAction);
            return types;
        });

        public static void RegisterTypedElement<TypeT>(string typeName = null)
            where TypeT : TypedElement
        {
            if (typeName == null)
                typeName = ((TypedElement)Activator.CreateInstance(typeof(TypeT))).Type;

            g_typedElementTypes.Value[typeName] = typeof(TypeT);
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
                Type type = null;
                if (g_typedElementTypes.Value.TryGetValue(typeName, out type))
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

        public static ElementT CreateElement<ElementT>(string typeName = null)
            where ElementT : TypedElement
        {
            if (typeName == null)
                typeName = ((ElementT)Activator.CreateInstance(typeof(ElementT))).Type;

            Type type = null;
            if (g_typedElementTypes.Value.TryGetValue(typeName, out type))
            {
                return (ElementT)Activator.CreateInstance(type);
            }
            return null;
        }
    }
}