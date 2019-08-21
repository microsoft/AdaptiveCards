using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace TestLibrary
{
    public class AnimalGrid : IAdaptiveCardElement
    {
        public string AnimalType { get; set; }
        public uint AnimalCount { get; set; } = 1;

        public bool MeetsRequirements(AdaptiveFeatureRegistration featureRegistration) { return true; }
        public JsonObject ToJson() { return new JsonObject(); }
        public JsonObject AdditionalProperties { get; set; }
        public ElementType ElementType { get; } = ElementType.Custom;
        public string ElementTypeString { get; } = "AnimalGrid";
        public IAdaptiveCardElement FallbackContent { get; set; }
        public FallbackType FallbackType { get; set; }
        public HeightType Height { get; set; }
        public string Id { get; set; } = "";
        public bool IsVisible { get; set; } = true;
        public bool Separator { get; set; }
        public Spacing Spacing { get; set; }
    }

    public class AnimalGridParser : IAdaptiveElementParser
    {
        public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            AnimalGrid animalGrid = new AnimalGrid();

            // Set the animal type
            if (!inputJson.ContainsKey("animalType") || inputJson["animalType"].ValueType != JsonValueType.String)
            {
                throw new Exception("Animal Type is required and must be a string!");
            }
            animalGrid.AnimalType = inputJson["animalType"].GetString();

            // Set the animal count
            if (inputJson.ContainsKey("animalCount"))
            {
                var animalCountJson = inputJson["animalCount"];
                if (animalCountJson.ValueType != JsonValueType.Number || animalCountJson.GetNumber() < 1)
                {
                    throw new Exception("Animal Count must be a number > 0");
                }

                if (animalCountJson.GetNumber() > 5)
                {
                    var warning = new AdaptiveWarning
                    {
                        StatusCode = WarningStatusCode.CustomWarning,
                        Message = "We only have 5 animals, some will be repeats"
                    };

                    warnings.Add(warning);
                }

                animalGrid.AnimalCount = (uint)animalCountJson.GetNumber();
            }

            return animalGrid;
        }
    }

    public class AnimalGridRenderer : IAdaptiveElementRenderer
    {
        public UIElement Render(IAdaptiveCardElement element, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
        {
            Uri[] mammelUris =
            {
                new Uri("https://picsum.photos/300/200?image=1003"),
                new Uri("https://en.wikipedia.org/wiki/File:Kittyply_edit1.jpg")
            };

            AnimalGrid animalGrid = element as AnimalGrid;
            for (uint i = 0; i < animalGrid.AnimalCount; i++)
            {

            }

            var textBlock = new TextBlock();
            textBlock.Text = "This is an animal grid with " + animalGrid.AnimalCount + " " + animalGrid.AnimalType + "!";

            return textBlock;
        }
    }
}

