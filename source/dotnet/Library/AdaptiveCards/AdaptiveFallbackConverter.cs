using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace AdaptiveCards
{
    public class AdaptiveFallbackConverter : AdaptiveTypedBaseElementConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public override bool CanWrite => true;
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            AdaptiveFallbackElement fallback = value as AdaptiveFallbackElement;
            if (fallback != null)
            {
                if (fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None)
                {
                    if (fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                    {
                        writer.WriteValue(AdaptiveFallbackElement.drop);
                    }
                    else
                    {
                        serializer.Serialize(writer, fallback.Content);
                    }
                }
            }
            else
            {
                throw new AdaptiveSerializationException("Unable to safely cast to AdaptiveFallbackElement");
            }
        }

        public static bool IsInFallback = false;

        public override bool CanRead => true;
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var token = reader.TokenType;
            switch (token)
            {
                case JsonToken.String:
                    {
                        AdaptiveFallbackElement adaptiveFallbackElement = new AdaptiveFallbackElement();

                        string stringValue = (string)reader.Value;
                        if (stringValue == "drop")
                        {
                            adaptiveFallbackElement.Type = AdaptiveFallbackElement.AdaptiveFallbackType.Drop;
                        }
                        else
                        {
                            throw new AdaptiveSerializationException("The only valid string value for the fallback property is 'drop'.");
                        }
                        return adaptiveFallbackElement;
                    }

                case JsonToken.StartObject:
                    {
                        var jObject = JObject.Load(reader);

                        var typeName = AdaptiveTypedElementConverter.GetElementTypeName(objectType, jObject);
                        Type type;
                        if (!AdaptiveTypedElementConverter.TypedElementTypes.Value.TryGetValue(typeName, out type))
                        {
                            type = typeof(AdaptiveUnknownElement);
                        }
                        IsInFallback = true;
                        string objectId = jObject.Value<string>("id");
                        AdaptiveInternalID internalID = AdaptiveInternalID.Next();

                        // Handle deserializing unknown element
                        ParseContext.PushElement(objectId, internalID);

                        var result = (AdaptiveTypedElement)Activator.CreateInstance(type);
                        serializer.Populate(jObject.CreateReader(), result);
                        ParseContext.PopElement();
                        IsInFallback = false;

                        AdaptiveFallbackElement adaptiveFallbackElement = new AdaptiveFallbackElement();
                        adaptiveFallbackElement.Type = AdaptiveFallbackElement.AdaptiveFallbackType.Content;
                        adaptiveFallbackElement.Content = result;
                        return adaptiveFallbackElement;
                    }

                default:
                    {
                        throw new AdaptiveSerializationException("Invalid value for fallback");
                    }
            }
        }

        public override bool CanConvert(Type objectType)
        {
            bool result = objectType == typeof(string) || objectType == typeof(AdaptiveTypedElement);

            if (!result)
            {
                throw new AdaptiveSerializationException("Invalid value for fallback");
            }
            return result;
        }

        public AdaptiveFallbackElement ParseFallback(JToken fallbackJSON, JsonSerializer serializer, string objectId, AdaptiveInternalID internalId)
        {
            // Handle fallback as a string ("drop")
            if (fallbackJSON.Type == JTokenType.String)
            {
                var str = fallbackJSON.Value<string>();
                if (str == AdaptiveFallbackElement.drop)
                {
                    // fallback is initialized with "drop" property and empty content
                    return new AdaptiveFallbackElement(AdaptiveFallbackElement.AdaptiveFallbackType.Drop);
                }
                throw new AdaptiveSerializationException("The only valid string value for the fallback property is 'drop'.");
            }
            // handle fallback as an object
            else if (fallbackJSON.Type == JTokenType.Object)
            {
                // fallback value is a JSON object. parse it and add it as fallback content. For more details, refer to
                // the giant comment on ID collision detection in ParseContext.cpp (ObjectModel).
                ParseContext.PushElement(objectId, internalId);
                var elem = new AdaptiveFallbackElement(fallbackJSON.ToObject<AdaptiveTypedElement>());
                ParseContext.PopElement();

                return elem;
            }
            // Should never get here. Instead should be thrown in CanConvert()
            throw new AdaptiveSerializationException("Invalid value for fallback");
        }
    }
}
