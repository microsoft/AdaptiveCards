// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    internal class StringSizeWithUnitConverter : JsonConverter<object>, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public StringSizeWithUnitConverter() { }

        public StringSizeWithUnitConverter(List<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
        }

        public override bool CanConvert(Type typeToConvert)
        {
            // Only use this converter for string types that match our format or uint
            return typeToConvert == typeof(string) || typeToConvert == typeof(uint) || typeToConvert == typeof(uint?);
        }

        public override object Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.String)
            {
                var dimension = reader.GetString();

                if (dimension.Length < 3)
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{dimension}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return 0U;
                }

                var unit = dimension.Substring(dimension.Length - 2);
                if (String.Compare(unit, "px", false) != 0)
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{unit}\" was not specified as a proper unit(px), it will be ignored."));
                    return 0U;
                }

                if (double.TryParse(dimension.Substring(0, dimension.Length - 2), NumberStyles.AllowDecimalPoint, null, out double dimensionInPix))
                {
                    if (dimension[0] == '.')
                    {
                        WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                            $"The Value \"{dimension}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    }
                    return (uint)dimensionInPix;
                }
                else
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{dimension}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return 0U;
                }
            }

            WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1, $"A value for a dimension field was not the proper type, it will be ignored."));
            reader.Skip();
            return 0U;
        }

        public override void Write(Utf8JsonWriter writer, object value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value.ToString() + "px");
        }
    }
}
