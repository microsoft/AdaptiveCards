using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

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
                    serializer.Serialize(writer, fallback.Content);
                }
            }
        }

        public override bool CanRead => true;

        public override bool CanWrite => true;

        public static bool IsInFallback = false;

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

                        var typeName = jObject["type"]?.Value<string>() ?? jObject["@type"]?.Value<string>();
                        if (typeName == null)
                        {
                            // Get value of this objectType's "Type" JsonProperty(Required)
                            var typeJsonPropertyRequiredValue = objectType.GetRuntimeProperty("Type")
                                .CustomAttributes.Where(a => a.AttributeType == typeof(JsonPropertyAttribute)).FirstOrDefault()?
                                .NamedArguments.Where(a => a.TypedValue.ArgumentType == typeof(Required)).FirstOrDefault()
                                .TypedValue.Value.ToString();

                            // If this objectType does not require "Type" attribute, use the objectType's XML "TypeName" attribute
                            if (typeJsonPropertyRequiredValue == "0")
                            {
                                typeName = objectType
                                    .GetRuntimeFields().Where(x => x.Name == "TypeName").FirstOrDefault()?
                                    .GetValue("TypeName").ToString();
                            }
                            else
                            {
                                throw new AdaptiveSerializationException("Required property 'type' not found on adaptive card element");
                            }
                        }

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

                        //return null;
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

        public static AdaptiveFallbackElement ParseFallback(JToken fallbackJSON, JsonSerializer serializer, string objectId, AdaptiveInternalID internalId)
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
