using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
            return typeof(IList<T>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);
            var items = array.Children<JObject>()
                .Where(obj => obj.HasValues)
                .Select(obj => serializer.Deserialize(obj.CreateReader(), typeof(T)))
                .Where(value => value != null)
                .Select(value => (T)value);
            if (objectType == typeof(ObservableCollection<T>))
                return new ObservableCollection<T>(items);
            else
                return items.ToList();
        }

        public override bool CanWrite => false;

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}