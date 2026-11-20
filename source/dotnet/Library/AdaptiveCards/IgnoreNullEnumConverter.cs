// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// JSON converter that will ignore enum values that can't be parsed correctly, returning null.
    /// </summary>
    public class IgnoreNullEnumConverter<TEnum> : JsonConverter<TEnum?>, ILogWarnings where TEnum : struct, Enum
    {
        /// <inheritdoc />
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        private enum WarningStatusCode { UnknownElementType = 0 };

        /// <inheritdoc />
        public IgnoreNullEnumConverter() { }

        /// <inheritdoc />
        public IgnoreNullEnumConverter(bool camelCase) { }

        /// <inheritdoc />
        public override TEnum? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.Null)
            {
                return null;
            }

            if (reader.TokenType == JsonTokenType.String)
            {
                var stringValue = reader.GetString();
                if (Enum.TryParse<TEnum>(stringValue, true, out var result))
                {
                    return result;
                }

                Warnings.Add(new AdaptiveWarning((int)WarningStatusCode.UnknownElementType,
                    $"Value \"{stringValue}\" could not be converted to \"{typeof(TEnum)}\", using null instead."));
                return null;
            }

            if (reader.TokenType == JsonTokenType.Number)
            {
                var intValue = reader.GetInt32();
                if (Enum.IsDefined(typeof(TEnum), intValue))
                {
                    return (TEnum)(object)intValue;
                }
                return null;
            }

            return null;
        }

        /// <inheritdoc />
        public override void Write(Utf8JsonWriter writer, TEnum? value, JsonSerializerOptions options)
        {
            if (value == null)
            {
                writer.WriteNullValue();
            }
            else
            {
                var name = value.Value.ToString();
                var camelCase = char.ToLowerInvariant(name[0]) + name.Substring(1);
                writer.WriteStringValue(camelCase);
            }
        }
    }
}
