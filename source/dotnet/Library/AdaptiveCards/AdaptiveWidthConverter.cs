// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    internal class AdaptiveWidthConverter : JsonConverter<AdaptiveWidth>, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public AdaptiveWidthConverter() { }

        public AdaptiveWidthConverter(List<AdaptiveWarning> warnings)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
        }

        public override void Write(Utf8JsonWriter writer, AdaptiveWidth value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value.ToString());
        }

        public override AdaptiveWidth Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            string value;
            if (reader.TokenType == JsonTokenType.Number)
            {
                value = reader.GetDouble().ToString(CultureInfo.InvariantCulture);
            }
            else
            {
                value = reader.GetString();
            }

            if (value == null)
            {
                return AdaptiveWidth.Auto;
            }

            try
            {
                return AdaptiveWidth.Parse(value);
            }
            catch (Exception)
            {
                if (value.Length < 3)
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{value}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return null;
                }

                var unit = value.Substring(value.Length - 2);
                if (String.Compare(unit, "px", false) != 0)
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{unit}\" was not specified as a proper unit(px), it will be ignored."));
                    return null;
                }

                if (!double.TryParse(value.Substring(0, value.Length - 2), NumberStyles.AllowDecimalPoint, null, out double dimensionInPix))
                {
                    WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1,
                        $"The Value \"{value}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return null;
                }

                WarningContext.AddWarning(Warnings, new AdaptiveWarning(-1, $@"The Value ""{value}"" was not valid, it will be ignored."));
                return AdaptiveWidth.Auto;
            }
        }
    }
}
