// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;

namespace AdaptiveCards
{
    public class IgnoreNullEnumConverter<TEnum> : StringEnumConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        // TODO: temporary warning code for invalid value. Remove when common set of error codes created and integrated.
        private enum WarningStatusCode { UnknownElementType = 0 };

        public IgnoreNullEnumConverter()
        {
        }

        public IgnoreNullEnumConverter(bool camelCase) : base(camelCase)
        {
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
                Warnings.Add(new AdaptiveWarning((int)WarningStatusCode.UnknownElementType, $"Value \"{reader.Value.ToString()}\" could not be converted to \"{typeof(TEnum).ToString()}\", using null instead."));
                return null;
            }
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            base.WriteJson(writer, value, serializer);
        }
    }
}
