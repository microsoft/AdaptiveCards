using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    internal class StringSizeWithUnitConverter : JsonConverter, ILogWarnings
    {
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        readonly JsonSerializer defaultSerializer = new JsonSerializer();

        private readonly bool isExplicitSize;

        public StringSizeWithUnitConverter()
        {
            isExplicitSize = true;
        }

        public StringSizeWithUnitConverter(bool isExplicit)
        {
            isExplicitSize = isExplicit;
        }

        public override bool CanConvert(Type objectType)
        {
            // Only use this converter for string types that match our format
            return (objectType == typeof(string));
        }

        // Checks if the size string was never intended to be explicit size
        private bool isNotExplicitSize(String size)
        {
            foreach(AdaptiveHeight height in (AdaptiveHeight[])Enum.GetValues(typeof(AdaptiveHeight)))
            {
                if(String.Compare(size, height.ToString(), true) == 0)
                    return true;
            }
            return false;
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.String)
            {
                var dimension = defaultSerializer.Deserialize(reader) as string;

                if (isExplicitSize)
                {
                    if (uint.TryParse(dimension.Substring(0, dimension.Length - 2), out uint dimensionInPix))
                    {
                        return dimensionInPix;
                    }
                    else
                    {
                        // If it's not auto or stretch, add a warning
                        if(!isNotExplicitSize(dimension))
                        {
                            Warnings.Add(new AdaptiveWarning(-1,
                            $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?pix), it will be ignored."));
                        }
                        return 0U;
                    }
                }
                else
                {
                    var heightType = dimension.ToLower();
                    if (String.Compare(dimension, AdaptiveHeight.Stretch.ToString(), true) == 0)
                        return AdaptiveHeight.Stretch;
                    return AdaptiveHeight.Auto;
                }
            }

            Warnings.Add(new AdaptiveWarning(-1, $"The Value \"{reader.Value}\" for field \"{reader.Path}\" of type \"{reader.TokenType}\" was not proper type, it will be ignored."));
            return 0U;
        }

        public override bool CanWrite { get { return false; } }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

    }
}
