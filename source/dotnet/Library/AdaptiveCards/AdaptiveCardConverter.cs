using System;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class AdaptiveCardConverter : JsonConverter
    {
        private readonly AdaptiveCardParseResult _parseResult;

        public AdaptiveCardConverter() : this(new AdaptiveCardParseResult())
        {
            
        }

        public AdaptiveCardConverter(AdaptiveCardParseResult parseResult)
        {
            _parseResult = parseResult;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanWrite => false;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            var card = (AdaptiveCard) Activator.CreateInstance(objectType);

            // AdaptiveCard ctor will specify the version by default, but we don't want that
            card.Version = null;

            serializer.Populate(jObject.CreateReader(), card);

            // TODO: return parse result error that version must be specified
            // If this is the root AdaptiveCard and missing a version we fail parsing. 
            // The depth checks that cards within a Action.ShowCard don't require the version
            if (reader.Depth == 0 && card.Version == null)
            {
                _parseResult.Errors.Add(new AdaptiveViolation(1, "Missing version"));
                return null;
            }

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }
    }
}