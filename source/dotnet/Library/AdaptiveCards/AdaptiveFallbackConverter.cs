using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class AdaptiveFallbackConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            AdaptiveFallbackElement fallback = (AdaptiveFallbackElement)value;
            if (fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None)
            {
                if (fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                {
                    writer.WriteValue(AdaptiveFallbackElement.drop);
                }
                else
                {
                    serializer.Serialize(writer, value);
                }
            }
        }

        public override bool CanRead => false;

        public override bool CanWrite => true;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanConvert(Type objectType)
        {
            return objectType == typeof(string) || objectType == typeof(AdaptiveTypedElement);
        }

        public static AdaptiveFallbackElement ParseFallback(JToken fallbackJSON, JsonSerializer serializer, string objectId, AdaptiveInternalID internalId)
        {
            // Handle fallback as a string ("drop")
            if (fallbackJSON.Type == JTokenType.String)
            {
                var str = fallbackJSON.Value<string>();
                if (str == AdaptiveFallbackElement.drop)
                {
                    // fallback is initialized with "drop" property and empty content
                    return new AdaptiveFallbackElement(null);
                }
                throw new AdaptiveSerializationException("The only valid string value for the fallback property is 'drop'.");
            }
            // handle fallback as an object
            else if (fallbackJSON.Type == JTokenType.Object)
            {
                // fallback value is a JSON object. parse it and add it as fallback content. For more details, refer to
                // the giant comment on ID collision detection in ParseContext.cpp (ObjectModel).
                ParseContext.PushElement(objectId, internalId, isFallback: true);
                var elem = new AdaptiveFallbackElement(fallbackJSON.ToObject<AdaptiveTypedElement>());
                ParseContext.PopElement();

                return new AdaptiveFallbackElement(fallbackJSON.ToObject<AdaptiveTypedElement>());
            }
            else
            {
                return null;
            }
        }
    }
}
