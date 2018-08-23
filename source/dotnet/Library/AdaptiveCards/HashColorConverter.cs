using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    public class HashColorConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        readonly JsonSerializer defaultSerializer = new JsonSerializer();

        public override bool CanConvert(Type objectType)
        {
            // Only use this converter for string types that match our format
            return (objectType == typeof(string));
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            bool fValidString = true;
            if (reader.TokenType == JsonToken.String)
            {
                var colorString = defaultSerializer.Deserialize(reader, objectType) as string;
                // We need to have a string in the format #AARRGGBB or #RRGGBB
                if (!string.IsNullOrEmpty(colorString) && (colorString.Length == 7 || colorString.Length == 9) && colorString[0] == '#')
                {
                    // Verify that each character is a proper hex digit
                    for (int i = 1; i < colorString.Length; i++)
                    {
                        if (!colorString[i].IsHexDigit())
                        {
                            fValidString = false;
                            break;
                        }
                    }

                    // We have the right format, and all the digits are hex, return the string
                    if (fValidString)
                    {
                        if (colorString.Length == 7)
                        {
                            return $"#FF{colorString.Substring(1).ToUpperInvariant()}";
                        }
                        else
                        {
                            return colorString.ToUpperInvariant();
                        }
                    }
                }
            }

            Warnings.Add(new AdaptiveWarning(-1, $"Token \"{reader.Value}\" of type {reader.TokenType} was not specified as a proper color in the format #AARRGGBB or #RRGGBB"));
            return null;
        }

        public override bool CanWrite { get { return false; } }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }

    public static partial class JsonExtensions
    {
        public static bool IsHexDigit(this char c)
        {
            return (c >= '0' && c <= '9') ||
                   (c >= 'A' && c <= 'F') ||
                   (c >= 'a' && c <= 'f');
        }
    }
}
