using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Windows.UI.Xaml;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters;
using System.Reflection;
using System.Linq;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;

namespace TestLibrary
{
    public enum AnimalType
    {
        Mammals,
        Birds,
        Fish,
        Reptiles,
        Insects,
    }

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
            if ((objectType is IAdaptiveCardElement) || (objectType is IAdaptiveActionElement))
            {
                return new AdaptiveElementConverter(ElementParsers, ActionParsers, Warnings);
            }
            else
            {
                return base.ResolveContractConverter(objectType);
            }
        }

        class AdaptiveElementConverter : JsonConverter<IAdaptiveCardElement>
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

                return cardElement;
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

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    //[JsonConverter(typeof(AdaptiveCardElementConverter))]
    public class AnimalGrid : IAdaptiveCardElement
    {
        [JsonRequired]
        [JsonConverter(typeof(StringEnumConverter))]
        public AnimalType AnimalType { get; set; }
        public uint AnimalCount { get; set; } = 1;

        public bool MeetsRequirements(AdaptiveFeatureRegistration featureRegistration) { return true; }

        // These are handled by the AdaptiveCardElementConverter
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FallbackType FallbackType { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public IAdaptiveCardElement FallbackContent { get; set; }

        [JsonIgnore]
        public JsonObject AdditionalProperties { get; set; }

        public JsonObject ToJson()
        {
            try
            {
                string jsonString = JsonConvert.SerializeObject(this);
                JsonObject.Parse(jsonString);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            return JsonObject.Parse(JsonConvert.SerializeObject(this));
        }

        // Set element type to custom and type string to "AnimalGrid"
        [JsonIgnore]
        public ElementType ElementType { get; } = ElementType.Custom;

        [JsonProperty("type")]
        public string ElementTypeString { get; } = "AnimalGrid";

        // Element properties handled automatically by Json.NET
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [JsonConverter(typeof(StringEnumConverter))]
        public HeightType Height { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Id { get; set; }
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool Separator { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [JsonConverter(typeof(StringEnumConverter))]
        public Spacing Spacing { get; set; }

        // Need to explicitly default this one to true or elements with unset visibility will be non visible
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [DefaultValue(true)]
        public bool IsVisible { get; set; } = true;
    }

    public class AnimalGridParser : IAdaptiveElementParser
    {
        public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            AnimalGrid animalGrid = JsonConvert.DeserializeObject<AnimalGrid>((inputJson as IJsonValue).Stringify(), new JsonSerializerSettings
            {
                ContractResolver = new AdaptiveCardContractResolver(elementParsers, actionParsers, warnings)
            });

            if (animalGrid.AnimalCount > 5)
            {
                var warning = new AdaptiveWarning(WarningStatusCode.CustomWarning, "We only have 5 animals, some will be repeats");
                warnings.Add(warning);
            }

            return animalGrid;
        }
    }

    public class AnimalGridRenderer : IAdaptiveElementRenderer
    {
        public UIElement Render(IAdaptiveCardElement element, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
        {
            AnimalGrid animalGrid = element as AnimalGrid;
            string[] animalUris = new string[5];

            switch (animalGrid.AnimalType)
            {
                case AnimalType.Mammals:
                    {
                        animalUris[0] = "https://images.pexels.com/photos/145939/pexels-photo-145939.jpeg";
                        animalUris[1] = "https://images.pexels.com/photos/2071873/pexels-photo-2071873.jpeg";
                        animalUris[2] = "https://images.pexels.com/photos/1319515/pexels-photo-1319515.jpeg";
                        animalUris[3] = "https://images.pexels.com/photos/2295744/pexels-photo-2295744.jpeg";
                        animalUris[4] = "https://images.pexels.com/photos/145947/pexels-photo-145947.jpeg";
                        break;
                    }
                case AnimalType.Birds:
                    {
                        animalUris[0] = "https://images.pexels.com/photos/2629372/pexels-photo-2629372.jpeg";
                        animalUris[1] = "https://images.pexels.com/photos/2226006/pexels-photo-2226006.jpeg";
                        animalUris[2] = "https://images.pexels.com/photos/151511/pexels-photo-151511.jpeg";
                        animalUris[3] = "https://images.pexels.com/photos/2152399/pexels-photo-2152399.jpeg";
                        animalUris[4] = "https://images.pexels.com/photos/2214495/pexels-photo-2214495.jpeg";
                        break;
                    }
                case AnimalType.Fish:
                    {
                        animalUris[0] = "https://images.pexels.com/photos/128756/pexels-photo-128756.jpeg";
                        animalUris[1] = "https://images.pexels.com/photos/325045/pexels-photo-325045.jpeg";
                        animalUris[2] = "https://images.pexels.com/photos/60090/pexels-photo-60090.jpeg";
                        animalUris[3] = "https://images.pexels.com/photos/1112007/pexels-photo-1112007.jpeg";
                        animalUris[4] = "https://images.pexels.com/photos/1365264/pexels-photo-1365264.jpeg";
                        break;
                    }
                case AnimalType.Reptiles:
                    {
                        animalUris[0] = "https://images.pexels.com/photos/47310/king-snake-snake-banded-red-47310.jpeg";
                        animalUris[1] = "https://images.pexels.com/photos/62289/yemen-chameleon-chamaeleo-calyptratus-chameleon-reptile-62289.jpeg";
                        animalUris[2] = "https://images.pexels.com/photos/735174/pexels-photo-735174.jpeg";
                        animalUris[3] = "https://images.pexels.com/photos/2758845/pexels-photo-2758845.jpeg";
                        animalUris[4] = "https://images.pexels.com/photos/792358/pexels-photo-792358.jpeg";
                        break;
                    }
                case AnimalType.Insects:
                    {
                        animalUris[0] = "https://images.pexels.com/photos/1085542/pexels-photo-1085542.jpeg";
                        animalUris[1] = "https://images.pexels.com/photos/37830/locust-jumping-grasshopper-animal-37830.jpeg";
                        animalUris[2] = "https://images.pexels.com/photos/53957/striped-core-butterflies-butterfly-brown-53957.jpeg";
                        animalUris[3] = "https://images.pexels.com/photos/1104974/pexels-photo-1104974.jpeg";
                        animalUris[4] = "https://images.pexels.com/photos/395241/pexels-photo-395241.jpeg";
                        break;
                    }
                default:
                    {
                        throw new Exception("Unexpected value for AnimalType");
                    }
            }

            AdaptiveImageSet animalImageSet = new AdaptiveImageSet
            {
                ImageSize = ImageSize.Large
            };

            for (uint i = 0; i < animalGrid.AnimalCount; i++)
            {
                AdaptiveImage image = new AdaptiveImage
                {
                    Url = animalUris[i % 5]
                };

                animalImageSet.Images.Add(image);
            }

            AdaptiveImageSetRenderer imageSetRenderer = new AdaptiveImageSetRenderer();
            return imageSetRenderer.Render(animalImageSet, context, renderArgs);
        }
    }
}

