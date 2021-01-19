// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Helper class to validate and convert color strings.
    /// </summary>
    public class HashColorConverter : JsonConverter, ILogWarnings
    {
        /// <summary>
        /// A list of warnings encountered during processing.
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        readonly JsonSerializer defaultSerializer = new JsonSerializer();

        /// <inheritdoc />
        public override bool CanConvert(Type objectType)
        {
            // Only use this converter for string types that match our format
            return (objectType == typeof(string));
        }

        /// <inheritdoc />
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.String)
            {
                var colorString = defaultSerializer.Deserialize(reader, objectType) as string;
                // We need to have a string in the format #AARRGGBB or #RRGGBB
                if (ColorUtil.IsValidColor(colorString))
                {
                    // We have the right format, and all the digits are hex, return the string
                    if (colorString.Length == ColorUtil.colorStringLength)
                    {
                        return $"#FF{colorString.Substring(1).ToUpperInvariant()}";
                    }
                    else
                    {
                        return colorString.ToUpperInvariant();
                    }
                }
            }

            Warnings.Add(new AdaptiveWarning(-1, $"The Value \"{reader.Value}\" for field \"{reader.Path}\" of type \"{reader.TokenType}\" was not specified as a proper color in the format #AARRGGBB or #RRGGBB, it will be ignored."));
            return null;
        }

        /// <inheritdoc />
        public override bool CanWrite { get { return false; } }

        /// <inheritdoc />
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }

    /// <summary>
    /// Helper class for color validation.
    /// </summary>
    public static partial class JsonExtensions
    {
        /// <summary>
        /// Determines if a character is a valid hex digit.
        /// </summary>
        /// <param name="c">Character to check.</param>
        /// <returns>true iff c is a valid hex digit.</returns>
        public static bool IsHexDigit(this char c)
        {
            return (c >= '0' && c <= '9') ||
                   (c >= 'A' && c <= 'F') ||
                   (c >= 'a' && c <= 'f');
        }
    }
}
