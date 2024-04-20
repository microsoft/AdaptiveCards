// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Globalization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    internal class AdaptiveWidthConverter : JsonConverter<AdaptiveWidth>, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        public AdaptiveWidthConverter()
        {
        }


        public override void WriteJson(JsonWriter writer, AdaptiveWidth value, JsonSerializer serializer)
        {
            writer.WriteValue(value.ToString());
        }

        public override AdaptiveWidth ReadJson(JsonReader reader, Type objectType, AdaptiveWidth existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            string value = JToken.Load(reader).ToString();
            try
            {
                return AdaptiveWidth.Parse(value);
            }
            catch (Exception err)
            {
                if (value.Length < 3)
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return null;
                }

                var unit = value.Substring(value.Length - 2);
                if (String.Compare(unit, "px", false) != 0)
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{unit}\" was not specified as a proper unit(px), it will be ignored."));
                    return null;
                }

                if (!double.TryParse(value.Substring(0, value.Length - 2), NumberStyles.AllowDecimalPoint, null, out double dimensionInPix))
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return null;
                }

                Warnings.Add(new AdaptiveWarning(-1, $@"The Value ""{value}"" for field ""{reader.Path}"" was not valid, it will be ignored."));
                return null;
            }

        }
    }
}
