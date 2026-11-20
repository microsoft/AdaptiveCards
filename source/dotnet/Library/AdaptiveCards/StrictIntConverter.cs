// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Converter for integers only. Rejects floating-point values.
    /// </summary>
    public class StrictIntConverter : JsonConverter<object>
    {
        /// <inheritdoc/>
        public override bool CanConvert(Type typeToConvert)
        {
            return typeToConvert.IsIntegerType();
        }

        /// <inheritdoc/>
        public override object Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.Number)
            {
                // Reject floating point - only allow integers
                if (reader.TryGetInt64(out long longVal))
                {
                    var underlying = Nullable.GetUnderlyingType(typeToConvert) ?? typeToConvert;

                    if (underlying == typeof(int)) return (int)longVal;
                    if (underlying == typeof(uint)) return (uint)longVal;
                    if (underlying == typeof(long)) return longVal;
                    if (underlying == typeof(ulong)) return (ulong)longVal;
                    if (underlying == typeof(short)) return (short)longVal;
                    if (underlying == typeof(ushort)) return (ushort)longVal;
                    if (underlying == typeof(byte)) return (byte)longVal;
                    if (underlying == typeof(sbyte)) return (sbyte)longVal;

                    return Convert.ChangeType(longVal, underlying);
                }

                throw new JsonException($"Token \"{reader.GetDouble()}\" was not a JSON integer");
            }

            if (reader.TokenType == JsonTokenType.Null)
            {
                return null;
            }

            throw new JsonException($"Token of type {reader.TokenType} was not a JSON integer");
        }

        /// <inheritdoc/>
        public override void Write(Utf8JsonWriter writer, object value, JsonSerializerOptions options)
        {
            if (value == null)
            {
                writer.WriteNullValue();
                return;
            }

            // Write the integer value
            if (value is int i) writer.WriteNumberValue(i);
            else if (value is long l) writer.WriteNumberValue(l);
            else if (value is uint ui) writer.WriteNumberValue(ui);
            else if (value is ulong ul) writer.WriteNumberValue(ul);
            else if (value is short s) writer.WriteNumberValue(s);
            else if (value is ushort us) writer.WriteNumberValue(us);
            else if (value is byte b) writer.WriteNumberValue(b);
            else if (value is sbyte sb) writer.WriteNumberValue(sb);
            else writer.WriteNumberValue(Convert.ToInt64(value));
        }
    }

    public static partial class JsonExtensions
    {
        /// <summary>
        /// Helper function to determine if type is an integer type.
        /// </summary>
        public static bool IsIntegerType(this Type type)
        {
            type = Nullable.GetUnderlyingType(type) ?? type;
            if (type == typeof(long)
                || type == typeof(ulong)
                || type == typeof(int)
                || type == typeof(uint)
                || type == typeof(short)
                || type == typeof(ushort)
                || type == typeof(byte)
                || type == typeof(sbyte)
                || type == typeof(System.Numerics.BigInteger))
            {
                return true;
            }

            return false;
        }
    }
}
