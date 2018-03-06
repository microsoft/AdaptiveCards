using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    public class IgnoreEmptyItemsConverter<T> : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return typeof(List<T>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);
            return array.Children<JObject>()
                .Where(obj => obj.HasValues)
                .Select(obj => serializer.Deserialize(obj.CreateReader(), typeof(T)))
                .Where(value => value != null)
                .Select(value => (T) value).ToList();
        }

        public override bool CanWrite => false;

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}