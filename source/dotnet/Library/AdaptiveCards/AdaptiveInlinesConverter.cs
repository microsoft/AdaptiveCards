// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    class AdaptiveInlinesConverter : JsonConverter<List<AdaptiveInline>>
    {
        public ParseContext ParseContext { get; set; } = new ParseContext();

        public AdaptiveInlinesConverter() { }

        public AdaptiveInlinesConverter(ParseContext parseContext)
        {
            ParseContext = parseContext ?? new ParseContext();
        }

        public override List<AdaptiveInline> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var array = JsonNode.Parse(ref reader)?.AsArray();
            var arrayList = new List<AdaptiveInline>();

            if (array == null) return arrayList;

            foreach (var node in array)
            {
                if (node is JsonValue val && val.TryGetValue<string>(out var s))
                {
                    arrayList.Add(new AdaptiveTextRun(s));
                }
                else if (node is JsonObject jobj)
                {
                    var typeValue = jobj["type"]?.GetValue<string>();
                    if (typeValue != AdaptiveTextRun.TypeName)
                    {
                        throw new AdaptiveSerializationException($"Property 'type' must be '{AdaptiveTextRun.TypeName}'");
                    }

                    var textRun = node.Deserialize<AdaptiveTextRun>(options);
                    if (textRun != null)
                    {
                        arrayList.Add(textRun);
                    }
                }
            }
            return arrayList;
        }

        public override void Write(Utf8JsonWriter writer, List<AdaptiveInline> value, JsonSerializerOptions options)
        {
            writer.WriteStartArray();
            foreach (var item in value)
            {
                JsonSerializer.Serialize(writer, item, item.GetType(), options);
            }
            writer.WriteEndArray();
        }
    }
}
