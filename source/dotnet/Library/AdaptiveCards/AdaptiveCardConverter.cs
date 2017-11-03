using System;
using System.Reflection;
using System.Runtime.Serialization;
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

            // If this is the root AdaptiveCard and missing a version we fail parsing. 
            // The depth checks that cards within a Action.ShowCard don't require the version
            if (reader.Depth == 0 && card.Version == null)
            {
                throw new AdaptiveSchemaException("Missing required property 'version' on AdaptiveCard");
            }

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }
    }

    public class AdaptiveSchemaException : Exception
    {
        public AdaptiveSchemaException()
        {
        }

        public AdaptiveSchemaException(string message) : base(message)
        {
        }

        public AdaptiveSchemaException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}