using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Windows.UI.Xaml;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using CustomElementJsonNetHelpers;

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

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AnimalGrid : IAdaptiveCardElement
    {
        [JsonRequired]
        [JsonConverter(typeof(StringEnumConverter))]
        public AnimalType AnimalType { get; set; }
        public uint AnimalCount { get; set; } = 1;

        public JsonObject ToJson()
        {
            try
            {
                string jsonString = JsonConvert.SerializeObject(this, new JsonSerializerSettings
                {
                    ContractResolver = new AdaptiveCardContractResolver()
                });
                return JsonObject.Parse(jsonString);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                throw e;
            }
        }

        // Set element type to custom and type string to "AnimalGrid"
        public ElementType ElementType { get; } = ElementType.Custom;
        public string ElementTypeString { get; } = "AnimalGrid";
        public IList<AdaptiveRequirement> Requirements { get; } = new List<AdaptiveRequirement>(); //BECKYTODO - cusomizer must initialize?

        // Element properties handled automatically by Json.NET and the AdaptiveCardElementConverter
        public FallbackType FallbackType { get; set; }
        public IAdaptiveCardElement FallbackContent { get; set; }
        public JsonObject AdditionalProperties { get; set; }
        public HeightType Height { get; set; }
        public string Id { get; set; }
        public bool Separator { get; set; }
        public Spacing Spacing { get; set; }
        public bool IsVisible { get; set; }
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

