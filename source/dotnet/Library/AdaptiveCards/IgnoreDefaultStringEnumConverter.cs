// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    internal class IgnoreDefaultStringEnumConverter<TEnum> : JsonConverter<TEnum>, ILogWarnings where TEnum : struct, Enum
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        private enum WarningStatusCode { UnknownElementType = 0 };

        private readonly string defaultValue;

        private string GetDefaultValueFromEnum()
        {
            return Enum.Parse(typeof(TEnum), "0").ToString();
        }

        public IgnoreDefaultStringEnumConverter()
        {
            defaultValue = GetDefaultValueFromEnum();
        }

        public IgnoreDefaultStringEnumConverter(bool camelCaseText)
        {
            defaultValue = GetDefaultValueFromEnum();
        }

        public override TEnum Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.String)
            {
                var stringValue = reader.GetString();
                if (Enum.TryParse<TEnum>(stringValue, true, out var result))
                {
                    return result;
                }

                WarningContext.AddWarning(Warnings, new AdaptiveWarning((int)WarningStatusCode.UnknownElementType,
                    $"Value \"{stringValue}\" could not be converted to \"{typeof(TEnum)}\", using the default value of \"{defaultValue}\" instead."));
                return default(TEnum);
            }

            if (reader.TokenType == JsonTokenType.Number)
            {
                var intValue = reader.GetInt32();
                if (Enum.IsDefined(typeof(TEnum), intValue))
                {
                    return (TEnum)(object)intValue;
                }
                return default(TEnum);
            }

            return default(TEnum);
        }

        public override void Write(Utf8JsonWriter writer, TEnum value, JsonSerializerOptions options)
        {
            if (value.ToString() == defaultValue)
            {
                writer.WriteNullValue();
            }
            else
            {
                // Write in camelCase
                var name = value.ToString();
                var camelCase = char.ToLowerInvariant(name[0]) + name.Substring(1);
                writer.WriteStringValue(camelCase);
            }
        }
    }
}
