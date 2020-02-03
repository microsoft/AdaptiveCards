// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;


namespace AdaptiveCards
{
    internal class IgnoreDefaultStringEnumConverter<TEnum> : StringEnumConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        // TODO: temporary warning code for invalid value. Remove when common set of error codes created and integrated.
        private enum WarningStatusCode {UnknownElementType = 0};

        private readonly string defaultValue;

        public IgnoreDefaultStringEnumConverter()
        {
            defaultValue = Enum.Parse(typeof(TEnum), "0").ToString();
        }

        public IgnoreDefaultStringEnumConverter(bool camelCaseText) : base(camelCaseText)
        {
            defaultValue = Enum.Parse(typeof(TEnum), "0").ToString();
        }
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            try
            {
                // Try to read regularly
                return base.ReadJson(reader, objectType, existingValue, serializer);
            }
            catch
            {
                // Catch invalid values and replace them with default value
                // Add warning stating behavior
                Warnings.Add(new AdaptiveWarning((int)WarningStatusCode.UnknownElementType, $"Value \"{reader.Value.ToString()}\" could not be converted to \"{typeof(TEnum).ToString()}\", using the default value of \"{defaultValue}\" instead."));
                return Enum.Parse(typeof(TEnum), "0");
            }
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            if (value?.ToString() == defaultValue)
                value = null;
            base.WriteJson(writer, value, serializer);
        }
    }
}
