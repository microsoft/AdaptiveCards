using System;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class AdaptiveCardConverter : JsonConverter
    {
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanWrite => false;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            var card = (AdaptiveCard) Activator.CreateInstance(objectType);
            // Get the version from the payload
            card.Version = null;

            serializer.Populate(jObject.CreateReader(), card);

            // TODO: return parse result error that version must be specified
            if (card.Version == null)
                return null;

            // When objects without a valid "type" are parsed they return null but still get added to the collections, this removes them
            card.Actions.RemoveAll(item => item == null);
            card.Body.RemoveAll(item => item == null);

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }
    }
}