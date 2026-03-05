// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Converter for AdaptiveTargetElement lists. Handles both string and object entries.
    /// </summary>
    public class ToggleElementsConverter : JsonConverter<List<AdaptiveTargetElement>>
    {
        /// <inheritdoc/>
        public override List<AdaptiveTargetElement> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var arrayList = new List<AdaptiveTargetElement>();

            if (reader.TokenType != JsonTokenType.StartArray)
            {
                return arrayList;
            }

            var array = JsonNode.Parse(ref reader)?.AsArray();
            if (array == null) return arrayList;

            foreach (var node in array)
            {
                if (node is JsonValue val && val.TryGetValue<string>(out var s))
                {
                    arrayList.Add(new AdaptiveTargetElement(s));
                }
                else if (node is JsonObject obj)
                {
                    var targetElement = obj.Deserialize<AdaptiveTargetElement>(options);
                    if (targetElement != null)
                    {
                        arrayList.Add(targetElement);
                    }
                }
            }

            return arrayList;
        }

        /// <inheritdoc/>
        public override void Write(Utf8JsonWriter writer, List<AdaptiveTargetElement> value, JsonSerializerOptions options)
        {
            writer.WriteStartArray();
            foreach (var el in value)
            {
                if (el.IsVisible == null)
                {
                    writer.WriteStringValue(el.ElementId);
                }
                else
                {
                    JsonSerializer.Serialize(writer, el, options);
                }
            }
            writer.WriteEndArray();
        }
    }
}
