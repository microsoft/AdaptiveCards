// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Helper class to validate and convert color strings.
    /// </summary>
    public class HashColorConverter : JsonConverter<string>, ILogWarnings
    {
        /// <summary>
        /// A list of warnings encountered during processing.
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        /// <summary>
        /// Initializes a new instance with an empty warnings list.
        /// </summary>
        public HashColorConverter() { }

        /// <summary>
        /// Initializes a new instance with a shared warnings list.
        /// </summary>
        public HashColorConverter(List<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
        }

        /// <inheritdoc />
        public override string Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.String)
            {
                var colorString = reader.GetString();
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

            Warnings.Add(new AdaptiveWarning(-1, $"The Value for a color field was not specified as a proper color in the format #AARRGGBB or #RRGGBB, it will be ignored."));
            // Skip the current token if we haven't consumed it
            if (reader.TokenType != JsonTokenType.String)
            {
                reader.Skip();
            }
            return null;
        }

        /// <inheritdoc />
        public override void Write(Utf8JsonWriter writer, string value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value);
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
