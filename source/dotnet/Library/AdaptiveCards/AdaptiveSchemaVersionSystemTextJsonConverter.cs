// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// System.Text.Json converter for AdaptiveSchemaVersion to ensure it serializes as a string (e.g. "1.0") 
    /// instead of an object with major/minor properties.
    /// </summary>
    public class AdaptiveSchemaVersionSystemTextJsonConverter : JsonConverter<AdaptiveSchemaVersion>
    {
        /// <summary>
        /// Reads a version string and converts it to AdaptiveSchemaVersion.
        /// </summary>
        public override AdaptiveSchemaVersion Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.String)
            {
                string versionString = reader.GetString();
                return new AdaptiveSchemaVersion(versionString);
            }
            else if (reader.TokenType == JsonTokenType.StartObject)
            {
                // Handle object format like {"major": 1, "minor": 0}
                using (JsonDocument document = JsonDocument.ParseValue(ref reader))
                {
                    JsonElement root = document.RootElement;
                    
                    int major = 1;
                    int minor = 0;
                    
                    if (root.TryGetProperty("major", out JsonElement majorElement))
                    {
                        major = majorElement.GetInt32();
                    }
                    
                    if (root.TryGetProperty("minor", out JsonElement minorElement))
                    {
                        minor = minorElement.GetInt32();
                    }
                    
                    return new AdaptiveSchemaVersion(major, minor);
                }
            }

            throw new JsonException($"Unable to parse AdaptiveSchemaVersion from {reader.TokenType}");
        }

        /// <summary>
        /// Writes AdaptiveSchemaVersion as a string (e.g. "1.0").
        /// </summary>
        public override void Write(Utf8JsonWriter writer, AdaptiveSchemaVersion value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value.ToString());
        }
    }
}