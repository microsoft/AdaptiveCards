using System;
using System.Collections.Generic;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class AdaptiveCardConverter : JsonConverter, ILogWarnings
    {
        public IList<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanWrite => false;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            if(jObject.Value<string>("type") != AdaptiveCard.TypeName)
                throw new AdaptiveSerializationException($"Property 'type' must be '{AdaptiveCard.TypeName}'");

            var typedElementConverter = serializer.ContractResolver.ResolveContract(typeof(AdaptiveTypedElement)).Converter;

            var card = (AdaptiveCard)typedElementConverter.ReadJson(jObject.CreateReader(), objectType, existingValue, serializer);

            // If this is the root AdaptiveCard and missing a version we fail parsing. 
            // The depth checks that cards within a Action.ShowCard don't require the version
            if (reader.Depth == 0 && card.Version == null)
            {
                // TODO: HACK for BF needing to deserialize legacy payloads that did not have a version
                card.Version = "0.5";
                //throw new AdaptiveSerializationException("Required property 'version' not found on AdaptiveCard");
            }

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }
    }
}