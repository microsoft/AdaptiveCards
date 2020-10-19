// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// JSON converter that will drop empty element items.
    /// </summary>
    /// <typeparam name="T">Type of the objects to be converted.</typeparam>
    public class IgnoreEmptyItemsConverter<T> : AdaptiveTypedBaseElementConverter
    {
        /// <inheritdoc />
        public override bool CanConvert(Type objectType)
        {
            return typeof(List<T>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        /// <inheritdoc />
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);

            ParseContext.Type = (objectType == typeof(List<AdaptiveElement>)) ? ParseContext.ContextType.Element : ParseContext.ContextType.Action;

            return array.Children<JObject>()
                .Where(obj => obj.HasValues)
                .Select(obj => serializer.Deserialize(obj.CreateReader(), typeof(T)))
                .Where(value => value != null)
                .Select(value => (T) value).ToList();
        }

        /// <inheritdoc />
        public override bool CanWrite => false;

        /// <inheritdoc />
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}
