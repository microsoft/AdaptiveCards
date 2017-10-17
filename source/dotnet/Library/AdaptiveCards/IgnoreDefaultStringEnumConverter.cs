using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;


namespace AdaptiveCards
{
    internal class IgnoreDefaultStringEnumConverter<TEnum> : StringEnumConverter
    {
        private readonly string defaultValue;

        public IgnoreDefaultStringEnumConverter()
        {
            defaultValue = Enum.Parse(typeof(TEnum), "0").ToString();
        }

        public IgnoreDefaultStringEnumConverter(bool camelCaseText) : base(camelCaseText)
        {
            defaultValue = Enum.Parse(typeof(TEnum), "0").ToString();
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            if (value?.ToString() == defaultValue)
                value = null;
            base.WriteJson(writer, value, serializer);
        }
    }
}