using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    public class StringSizeWithUnitConverter : JsonConverter, ILogWarnings
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
            if (reader.TokenType == JsonToken.String)
            {
                var dimension = defaultSerializer.Deserialize(reader) as string;
                if(uint.TryParse(dimension.Substring(0, dimension.Length - 2), out uint dimensionInPix)) {
                    return dimensionInPix;
                } else {
                    Warnings.Add(new AdaptiveWarning(-1, 
                        $"The Value \"{reader.Value}\" for field \"{reader.Path}\" was not specified as a proper dimension in the format (\\d+(.\\d+)?pix), it will be ignored."));
                    return 0U;
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
