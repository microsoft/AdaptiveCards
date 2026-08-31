// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Format datetime as Iso8601 instant format "yyyy-MM-ddTHH:mm:ssZ".
    /// </summary>
    public class Iso8601DateTimeConverter : JsonConverter<DateTime>
    {
        private const string DateTimeFormat = "yyyy-MM-ddTHH:mm:ssZ";

        /// <inheritdoc />
        public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var str = reader.GetString();
            return DateTime.Parse(str, CultureInfo.InvariantCulture, DateTimeStyles.RoundtripKind);
        }

        /// <inheritdoc />
        public override void Write(Utf8JsonWriter writer, DateTime value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value.ToUniversalTime().ToString(DateTimeFormat, CultureInfo.InvariantCulture));
        }
    }
}
