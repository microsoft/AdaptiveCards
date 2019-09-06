using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Reflection;
using Newtonsoft.Json.Serialization;
using Newtonsoft.Json.Converters;

namespace TestLibrary
{
    public class AdaptiveCardContractResolver : DefaultContractResolver
    {
        private AdaptiveElementParserRegistration ElementParsers { get; set; }
        private AdaptiveActionParserRegistration ActionParsers { get; set; }
        private IList<AdaptiveWarning> Warnings { get; set; }

        // This is not great because it lets the caller make a mistake and use this constructor for deserialize
        public AdaptiveCardContractResolver() { }


        // BECKYTODO - i need to hide this somehow - also make sure a container type would be ok
        bool _useElementConverter = true;
        public AdaptiveCardContractResolver(bool useElementConverter)
        {
            _useElementConverter = useElementConverter;
        }

        public AdaptiveCardContractResolver(AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            ElementParsers = elementParsers;
            ActionParsers = actionParsers;
            Warnings = warnings;
        }

        protected override JsonConverter ResolveContractConverter(Type objectType)
        {
            if (typeof(IAdaptiveCardElement).IsAssignableFrom(objectType) && _useElementConverter)
            {
                // Use element converter to handle Additional Properties, Requirements, and Fallback
                return new AdaptiveElementConverter(ElementParsers, ActionParsers, Warnings);
            }
            else if (typeof(Spacing).IsAssignableFrom(objectType) || typeof(HeightType).IsAssignableFrom(objectType))
            {
                // Use the string enum converter for these types to get them serialized as enum names rather than integers
                return new StringEnumConverter();
            }
            else
            {
                return base.ResolveContractConverter(objectType);
            }
        }

        protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
        {
            JsonProperty jsonProperty = base.CreateProperty(member, memberSerialization);

            // To handle element type, ignore the "ElementType" property, and write out the ElementTypeString property as "type"
            if (member.Name == "FallbackType" ||
                member.Name == "FallbackContent" ||
                member.Name == "AdditionalProperties" ||
                member.Name == "ElementType" ||
                member.Name == "Requirements")
            {
                jsonProperty.ShouldSerialize = o => { return false; };
            }

            // Convert the "E
            if (member.Name == "ElementTypeString")
            {
                jsonProperty.PropertyName = "type";
            }

            // Don't write out default values for these properties
            if (member.Name == "Id" ||
                member.Name == "Height" ||
                member.Name == "Separator" ||
                member.Name == "Spacing" ||
                member.Name == "IsVisible")
            {
                jsonProperty.DefaultValueHandling = DefaultValueHandling.Ignore;
            }

            if (member.Name == "IsVisible")
            {
                jsonProperty.DefaultValue = true;
            }

            return jsonProperty;
        }
    }

    internal class AdaptiveAdditionalPropertiesConverter : JsonConverter<JsonObject>
    {
        public override void WriteJson(JsonWriter writer, JsonObject additionalPropertiesJson, JsonSerializer serializer)
        {
            JObject jObject = new JObject();

            foreach (var additionalProperty in additionalPropertiesJson)
            {
                jObject[additionalProperty.Key] = JsonHelper.JsonValueToJToken(additionalProperty.Value);
            }

            jObject.WriteTo(writer);
        }

        // Deserialization of additional properties is handled in the element converter
        public override bool CanRead { get; } = false;
        public override JsonObject ReadJson(JsonReader reader, Type objectType, JsonObject existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }

    internal class AdaptiveElementConverter : JsonConverter<IAdaptiveCardElement>
    {
        private AdaptiveElementParserRegistration ElementParsers { get; set; }
        private AdaptiveActionParserRegistration ActionParsers { get; set; }
        private IList<AdaptiveWarning> Warnings { get; set; }

        public AdaptiveElementConverter(bool canWrite)
        {
            CanWrite = canWrite;
        }

        public AdaptiveElementConverter(AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            ElementParsers = elementParsers;
            ActionParsers = actionParsers;
            Warnings = warnings;
        }

        public override IAdaptiveCardElement ReadJson(JsonReader reader, Type objectType, IAdaptiveCardElement existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            JObject jObject = JObject.Load(reader);

            IAdaptiveCardElement cardElement = (IAdaptiveCardElement)Activator.CreateInstance(objectType);
            serializer.Populate(jObject.CreateReader(), cardElement);

            DeserializeAdditionalProperties(cardElement, jObject);
            DeserializeFallbackInformation(cardElement, jObject);
            DeserializeRequires(cardElement, jObject);
            DeserializeDefaultVisibility(cardElement, jObject);

            return cardElement;
        }

        private void DeserializeDefaultVisibility(IAdaptiveCardElement cardElement, JObject jObject)
        {
            if (jObject["isVisible"] == null)
            {
                cardElement.IsVisible = true;
            }
        }

        private void DeserializeRequires(IAdaptiveCardElement element, JObject jObject)
        {
            if (element is IAdaptiveCardElement cardElement)
            {
                if (jObject["requires"] != null && jObject["requires"].Type == JTokenType.Object)
                {
                    JObject requires = (JObject)jObject["requires"];

                    foreach (JProperty requirement in requires.Properties())
                    {
                        (element as IAdaptiveCardElement).Requirements.Add(new AdaptiveRequirement(requirement.Name, requirement.Value.ToString()));
                    }
                }
            }
        }

        private void DeserializeFallbackInformation(IAdaptiveCardElement element, JObject jObject)
        {
            var fallback = jObject["fallback"];

            FallbackType fallbackType = FallbackType.None;
            string fallbackElementType = "";
            if (fallback != null)
            {
                if ((fallback.Type == JTokenType.String) &&
                    (string.Compare(fallback.ToString(), "drop") == 0))
                {
                    fallbackType = FallbackType.Drop;
                }
                else if (fallback.Type == JTokenType.Object)
                {
                    fallbackType = FallbackType.Content;
                    fallbackElementType = (string)fallback["type"];
                }
            }

            if (element is IAdaptiveCardElement cardElement)
            {
                cardElement.FallbackType = fallbackType;
                if (fallbackType == FallbackType.Content)
                {
                    cardElement.FallbackContent = ElementParsers.Get(fallbackElementType).FromJson(JsonObject.Parse(fallback.ToString()), ElementParsers, ActionParsers, Warnings);
                }
            }
            else if (element is IAdaptiveActionElement actionElement)
            {
                actionElement.FallbackType = fallbackType;
                if (fallbackType == FallbackType.Content)
                {
                    actionElement.FallbackContent = ActionParsers.Get(fallbackElementType).FromJson(JsonObject.Parse(fallback.ToString()), ElementParsers, ActionParsers, Warnings);
                }
            }
        }

        private void DeserializeAdditionalProperties(object element, JObject jObject)
        {
            IEnumerable<PropertyInfo> runtimeProperties = element.GetType().GetRuntimeProperties();

            foreach (var keyValuePair in jObject)
            {
                bool found = false;
                foreach (var runtimeProperty in runtimeProperties)
                {
                    if (string.Compare(keyValuePair.Key, runtimeProperty.Name, true) == 0)
                    {
                        found = true;
                        break;
                    }
                    else
                    {
                        // Check if it matches the json attribute name
                        string jsonPropertyName = null;
                        foreach (var attribute in runtimeProperty.CustomAttributes)
                        {
                            if (attribute.AttributeType == typeof(JsonPropertyAttribute) &&
                                attribute.ConstructorArguments.Count == 1)
                            {
                                jsonPropertyName = attribute.ConstructorArguments[0].Value as string;
                                break;
                            }
                        }
                        if ((jsonPropertyName != null) && (string.Compare(keyValuePair.Key, jsonPropertyName, true) == 0))
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    if (element is IAdaptiveCardElement cardElement)
                    {
                        if (cardElement.AdditionalProperties == null)
                        {
                            cardElement.AdditionalProperties = new JsonObject();
                        }

                        cardElement.AdditionalProperties[keyValuePair.Key] = JsonHelper.JTokenToJsonValue(keyValuePair.Value);
                    }
                    else if (element is IAdaptiveActionElement actionElement)
                    {
                        if (actionElement.AdditionalProperties == null)
                        {
                            actionElement.AdditionalProperties = new JsonObject();
                        }

                        actionElement.AdditionalProperties[keyValuePair.Key] = JsonHelper.JTokenToJsonValue(keyValuePair.Value);
                    }
                }
            }
        }

        public override bool CanWrite { get; } = true;
        public override void WriteJson(JsonWriter writer, IAdaptiveCardElement value, JsonSerializer serializer)
        {
            JObject jObject = JObject.FromObject(value, new JsonSerializer
            {
                ContractResolver = new AdaptiveCardContractResolver(false)
            });

            SerializeAdditionalProperties(value, jObject);
            SerializeFallback(value, jObject);
            SerializeRequirements(value, jObject);

            jObject.WriteTo(writer);
        }

        private void SerializeRequirements(IAdaptiveCardElement value, JObject jObject)
        {
            if (value.Requirements != null && value.Requirements.Count > 0)
            {
                JObject requirementsObject = new JObject();

                foreach (var requirement in value.Requirements)
                {
                    requirementsObject[requirement.Name] = requirement.Version;
                }
            }
        }

        private void SerializeFallback(IAdaptiveCardElement value, JObject jObject)
        {
            if(value.FallbackType == FallbackType.Drop)
            {
                jObject["fallback"] = "drop";
            }
            else if (value.FallbackType == FallbackType.Content && value.FallbackContent != null)
            {
                jObject["fallback"] = JObject.Parse(value.FallbackContent.ToJson().Stringify());
            }
        }

        public void SerializeAdditionalProperties(IAdaptiveCardElement element, JObject jObject)
        {
            foreach (var additionalProperty in element.AdditionalProperties)
            {
                jObject[additionalProperty.Key] = JsonHelper.JsonValueToJToken(additionalProperty.Value);
            }
        }
    }

    internal class JsonHelper
    {
        static public JsonValue JTokenToJsonValue(JToken jtoken)
        {
            JsonValue value;

            switch (jtoken.Type)
            {
                case JTokenType.None:
                    {
                        value = JsonValue.CreateNullValue();
                        break;
                    }
                case JTokenType.Float:
                case JTokenType.Integer:
                    {
                        value = JsonValue.CreateNumberValue((double)jtoken);
                        break;
                    }
                case JTokenType.Boolean:
                    {
                        value = JsonValue.CreateBooleanValue((bool)jtoken);
                        break;
                    }
                case JTokenType.Array:
                case JTokenType.Object:
                    {
                        value = JsonValue.Parse(jtoken.ToString());
                        break;
                    }
                case JTokenType.String:
                default:
                    {
                        value = JsonValue.CreateStringValue((string)jtoken);
                        break;
                    }
            }

            return value;
        }

        static public JToken JsonValueToJToken(IJsonValue jsonValue)
        {
            switch (jsonValue.ValueType)
            {
                case JsonValueType.Boolean:
                    return new JValue(jsonValue.GetBoolean());

                case JsonValueType.Number:
                    return new JValue(jsonValue.GetNumber());

                case JsonValueType.String:
                    return new JValue(jsonValue.GetString());

                case JsonValueType.Object:
                    return JObject.Parse(jsonValue.GetObject().Stringify());

                case JsonValueType.Array:
                    return JObject.Parse(jsonValue.GetArray().Stringify());

                case JsonValueType.Null:
                default:
                    return JValue.CreateNull();
            }
        }
    }
}
