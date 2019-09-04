using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Reflection;
using Newtonsoft.Json.Serialization;

namespace TestLibrary
{
    public class AdaptiveCardContractResolver : DefaultContractResolver
    {
        private AdaptiveElementParserRegistration ElementParsers { get; set; }
        private AdaptiveActionParserRegistration ActionParsers { get; set; }
        private IList<AdaptiveWarning> Warnings { get; set; }

        public AdaptiveCardContractResolver(AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            ElementParsers = elementParsers;
            ActionParsers = actionParsers;
            Warnings = warnings;
        }

        protected override JsonConverter ResolveContractConverter(Type objectType)
        {
            if (typeof(IAdaptiveCardElement).IsAssignableFrom(objectType) ||
                typeof(IAdaptiveActionElement).IsAssignableFrom(objectType))
            {
                return new AdaptiveElementConverter(ElementParsers, ActionParsers, Warnings);
            }
            else
            {
                return base.ResolveContractConverter(objectType);
            }
        }
    }

    internal class AdaptiveElementConverter : JsonConverter<IAdaptiveCardElement>
    {
        private AdaptiveElementParserRegistration ElementParsers { get; set; }
        private AdaptiveActionParserRegistration ActionParsers { get; set; }
        private IList<AdaptiveWarning> Warnings { get; set; }

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

            SetAdditionalProperties(cardElement, jObject);
            SetFallbackInformation(cardElement, jObject);
            SetRequires(cardElement, jObject);

            return cardElement;
        }

        private void SetRequires(object element, JObject jObject)
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

        private void SetFallbackInformation(object element, JObject jObject)
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

        private void SetAdditionalProperties(object element, JObject jObject)
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

                        cardElement.AdditionalProperties[keyValuePair.Key] = JTokenToJsonValue(keyValuePair.Value);
                    }
                    else if (element is IAdaptiveActionElement actionElement)
                    {
                        if (actionElement.AdditionalProperties == null)
                        {
                            actionElement.AdditionalProperties = new JsonObject();
                        }

                        actionElement.AdditionalProperties[keyValuePair.Key] = JTokenToJsonValue(keyValuePair.Value);
                    }
                }
            }
        }

        public override bool CanWrite { get; } = false;

        public override void WriteJson(JsonWriter writer, IAdaptiveCardElement value, JsonSerializer serializer)
        {

            serializer.Serialize(writer, value);
        }

        JsonValue JTokenToJsonValue(JToken jtoken)
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
    }
}
