using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Reflection;

namespace CustomElementJsonNetHelpers
{
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


        private bool IsKnownAdaptiveCardsType(JObject jObject, out string elementTypeString)
        {
            elementTypeString = (string)jObject["type"];
            return Enum.TryParse(elementTypeString, out ElementType knownElementType);
        }

        public override IAdaptiveCardElement ReadJson(JsonReader reader, Type objectType, IAdaptiveCardElement existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            JObject jObject = JObject.Load(reader);

            IAdaptiveCardElement cardElement;

            if (IsKnownAdaptiveCardsType(jObject, out string elementTypeString) || objectType == typeof(IAdaptiveCardElement))
            {
                // If this is a known element type, or if we just have the interface, get the parser from the parser registration
                IAdaptiveElementParser parser = ElementParsers.Get(elementTypeString);

                string jsonString = jObject.ToString();
                JsonObject jsonObject = JsonObject.Parse(jsonString);

                cardElement = parser.FromJson(jsonObject, ElementParsers, ActionParsers, Warnings);

                //cardElement = ElementParsers.Get(elementTypeString).FromJson(JsonObject.Parse(jObject.ToString()), ElementParsers, ActionParsers, Warnings);
            }
            else
            {
                // This is a custom type, instantiate and populate it via Json.NET
                cardElement = (IAdaptiveCardElement)Activator.CreateInstance(objectType);
                serializer.Populate(jObject.CreateReader(), cardElement);

                // Handle custom parsing for AdditionalProperties, Fallback, Requires, and Visibility
                DeserializeAdditionalProperties(cardElement, jObject);
                DeserializeFallbackInformation(cardElement, jObject);
                DeserializeRequires(cardElement, jObject);
                DeserializeDefaultVisibility(cardElement, jObject);
            }

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
            JToken fallback = jObject["fallback"];

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

            element.FallbackType = fallbackType;
            if (fallbackType == FallbackType.Content)
            {
                element.FallbackContent = ElementParsers.Get(fallbackElementType).FromJson(JsonObject.Parse(fallback.ToString()), ElementParsers, ActionParsers, Warnings);
            }
        }

        private void DeserializeAdditionalProperties(IAdaptiveCardElement element, JObject jObject)
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
                    if (element.AdditionalProperties == null)
                    {
                        element.AdditionalProperties = new JsonObject();
                    }

                    element.AdditionalProperties[keyValuePair.Key] = JsonHelper.JTokenToJsonValue(keyValuePair.Value);
                }
            }
        }

        public override bool CanWrite { get; } = true;
        public override void WriteJson(JsonWriter writer, IAdaptiveCardElement value, JsonSerializer serializer)
        {
            JObject jObject;
            if (value.ElementType == ElementType.Custom)
            {
                Type customElementType = value.GetType();
                PropertyInfo[] properties = customElementType.GetProperties();

                foreach (PropertyInfo property in properties)
                {
                    customElementType.InvokeMember();
                }





                // If this is a custom element type, use Json.NET with the AdaptiveCardSerializationResolver
                // which handles special case JsonProperty definitions for IAdaptiveCardElement properties.
                // (Note: If we use the AdaptiveCardContractResolver here we end up calling back into this
                // function until the stack overflows)
                jObject = JObject.FromObject(value, new JsonSerializer
                {
                    ContractResolver = new AdaptiveCardSerializationResolver()
                });

                // Handle more complex special case serialization
                SerializeAdditionalProperties(value, jObject);
                SerializeFallback(value, jObject);
                SerializeRequirements(value, jObject);
            }
            else
            {
                // If this is a known type, use our native ToJson method and convert the JsonObject
                // to a JObject using ToString() and Parse().
                jObject = JObject.Parse(value.ToJson().ToString());
            }

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
            if (value.FallbackType == FallbackType.Drop)
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
}
