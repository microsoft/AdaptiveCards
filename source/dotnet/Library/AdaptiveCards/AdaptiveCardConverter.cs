using System;
using System.Collections.Generic;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class AdaptiveCardConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanWrite => false;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            if (jObject.Value<string>("type") != AdaptiveCard.TypeName)
                throw new AdaptiveSerializationException($"Property 'type' must be '{AdaptiveCard.TypeName}'");

            if (reader.Depth == 0)
            {
                if (jObject.Value<string>("version") == null)
                {
                    throw new AdaptiveSerializationException("Could not parse required key: version. It was not found.");
                }

                // If this is the root AdaptiveCard and missing a version we fail parsing. 
                // The depth checks that cards within a Action.ShowCard don't require the version
                if (jObject.Value<string>("version") == "")
                {
                    throw new AdaptiveSerializationException("Property is required but was found empty: version");
                }

                if (new AdaptiveSchemaVersion(jObject.Value<string>("version")) > AdaptiveCard.KnownSchemaVersion)
                {
                    return MakeFallbackTextCard(jObject);
                }
            }
            var typedElementConverter = serializer.ContractResolver.ResolveContract(typeof(AdaptiveTypedElement)).Converter;

            var card = (AdaptiveCard)typedElementConverter.ReadJson(jObject.CreateReader(), objectType, existingValue, serializer);

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        private AdaptiveCard MakeFallbackTextCard(JObject jObject)
        {
            // Retrieve fallbackText and language defined by parsed json
            string language = jObject.Value<string>("language");
            string fallbackText = jObject.Value<string>("fallbackText");

            if (String.IsNullOrEmpty(fallbackText))
            {
                fallbackText = "We're sorry, this card couldn't be displayed";
            }

            // Define AdaptiveCard to return
            AdaptiveCard fallbackTextCard = new AdaptiveCard("1.0");
            fallbackTextCard.Body.Add(new AdaptiveTextBlock
            {
                Text = fallbackText
            });

            // Add relevant warning
            Warnings.Add(new AdaptiveWarning(7, "Schema version is not supported"));

            return fallbackTextCard;
        }
    }
}