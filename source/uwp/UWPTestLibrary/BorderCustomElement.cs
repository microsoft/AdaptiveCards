using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Windows.UI.Xaml;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using CustomElementJsonNetHelpers;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace TestLibrary
{
    public class BorderCustomElement : IAdaptiveCardElement
    {
        public IAdaptiveCardElement ContainedElement { get; set; }
        public ForegroundColor BorderColor { get; set; }

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

        public JsonObject AdditionalProperties { get; set; }
        public ElementType ElementType { get; } = ElementType.Custom;
        public string ElementTypeString { get; } = "Border";

        public IAdaptiveCardElement FallbackContent { get; set; }
        public FallbackType FallbackType { get; set; }
        public HeightType Height { get; set; }
        public string Id { get; set; }
        public bool IsVisible { get; set; }
        public IList<AdaptiveRequirement> Requirements { get; } = new List<AdaptiveRequirement>();
        public bool Separator { get; set; }
        public Spacing Spacing { get; set; }
    }

    public class BorderCustomElementParser : IAdaptiveElementParser
    {
        public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            var animalGridParser = elementParsers.Get("AnimalGrid");
            var borderParser = elementParsers.Get("Border");

            BorderCustomElement borderCustomElement = JsonConvert.DeserializeObject<BorderCustomElement>((inputJson as IJsonValue).Stringify(), new JsonSerializerSettings
            {
                ContractResolver = new AdaptiveCardContractResolver(elementParsers, actionParsers, warnings)
            });

            return borderCustomElement;
        }
    }

    public class BorderCustomElementRenderer : IAdaptiveElementRenderer
    {
        public UIElement Render(IAdaptiveCardElement element, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
        {
            BorderCustomElement borderCustomElement = element as BorderCustomElement;

            IAdaptiveElementRenderer renderer = context.ElementRenderers.Get(borderCustomElement.ContainedElement.ElementTypeString);
            UIElement containedUIElement = renderer.Render(borderCustomElement.ContainedElement, context, renderArgs);

            Border xamlBorder = new Border
            {
                Child = containedUIElement,
                BorderThickness = new Thickness(5),
                BorderBrush = new SolidColorBrush(GetColor(borderCustomElement, context, renderArgs))
            };

            return xamlBorder;
        }

        // BECKYTODO - this is unfortunate...
        public Windows.UI.Color GetColor(BorderCustomElement borderElement, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
        {
            AdaptiveContainerStyleDefinition containerStyleDefinition;
            switch(renderArgs.ContainerStyle)
            {
                case ContainerStyle.Accent:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Accent;
                    break;

                case ContainerStyle.Attention:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Attention;
                    break;

                case ContainerStyle.Emphasis:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Emphasis;
                    break;

                case ContainerStyle.Good:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Good;
                    break;

                case ContainerStyle.Warning:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Warning;
                    break;

                case ContainerStyle.Default:
                case ContainerStyle.None:
                default:
                    containerStyleDefinition = context.HostConfig.ContainerStyles.Default;
                    break;
            }

            return GetColorFromContainerStyle(containerStyleDefinition, borderElement.BorderColor);
        }

        public Windows.UI.Color GetColorFromContainerStyle(AdaptiveContainerStyleDefinition containerStyle, ForegroundColor foregroundColor)
        { 
            switch(foregroundColor)
            {
                case ForegroundColor.Accent:
                    return containerStyle.ForegroundColors.Accent.Default;

                case ForegroundColor.Attention:
                    return containerStyle.ForegroundColors.Attention.Default;

                case ForegroundColor.Dark:
                    return containerStyle.ForegroundColors.Dark.Default;

                case ForegroundColor.Good:
                    return containerStyle.ForegroundColors.Good.Default;

                case ForegroundColor.Light:
                    return containerStyle.ForegroundColors.Light.Default;

                case ForegroundColor.Warning:
                    return containerStyle.ForegroundColors.Warning.Default;

                case ForegroundColor.Default:
                default:
                    return containerStyle.ForegroundColors.Default.Default;
            }
        }
    }
}
