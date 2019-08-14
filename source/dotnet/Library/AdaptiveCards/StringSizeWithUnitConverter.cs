// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Globalization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    internal class StringSizeWithUnitConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        readonly JsonSerializer defaultSerializer = new JsonSerializer();

        private readonly bool isHeight;

        public StringSizeWithUnitConverter()
        {
            isHeight = true;
        }

        public StringSizeWithUnitConverter(bool height)
        {
            isHeight = height;
        }

        public override bool CanConvert(Type objectType)
        {
            // Only use this converter for string types that match our format
            return (objectType == typeof(string));
        }

        // Checks if the size string was never intended to be explicit size
        private bool isPixelHeight(String size)
        {
            return !((String.Compare(size, AdaptiveHeightType.Auto.ToString(), true) == 0)
                || (String.Compare(size, AdaptiveHeightType.Stretch.ToString(), true) == 0));
        }

        private object GenerateReturnValue(uint px)
        {
            if (!isHeight)
            {
                return px;
            }

            if (px != 0)
            {
                return new AdaptiveHeight(px);
            }
            return null;
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.String)
            {
                var dimension = defaultSerializer.Deserialize(reader) as string;

                // Only the height can have auto or stretch sizes
                if(isHeight)
                {
                    // If the received string is not auto or stretch
                    if (!isPixelHeight(dimension))
                    {
                        var heightType = dimension.ToLower();
                        if (String.Compare(dimension, AdaptiveHeightType.Stretch.ToString(), true) == 0)
                        {
                            return new AdaptiveHeight(AdaptiveHeightType.Stretch);
                        }
                        return new AdaptiveHeight(AdaptiveHeightType.Auto);
                    }
                }

                if (dimension.Length < 3)
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return GenerateReturnValue(0U);
                }

                var unit = dimension.Substring(dimension.Length - 2);
                if (String.Compare(unit, "px", false) != 0)
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{unit}\" was not specified as a proper unit(px), it will be ignored."));
                    return GenerateReturnValue(0U);
                }

                if (double.TryParse(dimension.Substring(0, dimension.Length - 2), NumberStyles.AllowDecimalPoint, null, out double dimensionInPix))
                {
                    // we need check this because AllowDecimalPoint flags allows TryParse to accept number in .\d+ format
                    if (dimension[0] == '.')
                    {
                        Warnings.Add(new AdaptiveWarning(-1,
                            $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    }
                    return GenerateReturnValue((uint)dimensionInPix);
                }
                else
                {
                    Warnings.Add(new AdaptiveWarning(-1,
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?px), it will be ignored."));
                    return GenerateReturnValue(0U);
                }
            }

            Warnings.Add(new AdaptiveWarning(-1, $"The Value \"{reader.Value}\" for field \"{reader.Path}\" of type \"{reader.TokenType}\" was not proper type, it will be ignored."));
            return GenerateReturnValue(0U);
        }

        public override bool CanWrite { get { return true; } }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            if (!isHeight)
            {
                writer.WriteValue(value.ToString() + "px");
            }
            else
            {
                AdaptiveHeight adaptiveHeight = (AdaptiveHeight)value;
                if (adaptiveHeight.IsPixel())
                {
                    writer.WriteValue(adaptiveHeight.Unit.ToString() + "px");
                }
                else if (isHeight)
                {
                    writer.WriteValue(adaptiveHeight.HeightType.ToString().ToLower());
                }
            }
        }
    }
}
