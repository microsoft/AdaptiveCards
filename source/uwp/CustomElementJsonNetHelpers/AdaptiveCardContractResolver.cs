using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Uwp;
using Newtonsoft.Json;
using System.Reflection;
using Newtonsoft.Json.Serialization;

namespace CustomElementJsonNetHelpers
{
    public class AdaptiveCardContractResolver : DefaultContractResolver
    {
        private AdaptiveElementParserRegistration ElementParsers { get; set; }
        private AdaptiveActionParserRegistration ActionParsers { get; set; }
        private IList<AdaptiveWarning> Warnings { get; set; }

        // This is not great because it lets the caller make a mistake and use this constructor for
        // deserialize. In the deserialize case we *must* have element and action parsers, in the
        // serialize case we will *not* have them. 
        public AdaptiveCardContractResolver() { }

        public AdaptiveCardContractResolver(AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            ElementParsers = elementParsers;
            ActionParsers = actionParsers;
            Warnings = warnings;
        }

        protected override JsonConverter ResolveContractConverter(Type objectType)
        {
            if (typeof(IAdaptiveCardElement).IsAssignableFrom(objectType))
            {
                // Use element converter to handle Additional Properties, Requirements, and Fallback
                return new AdaptiveElementConverter(ElementParsers, ActionParsers, Warnings);
            }
            else
            {
                return base.ResolveContractConverter(objectType);
            }
        }
    }
}
