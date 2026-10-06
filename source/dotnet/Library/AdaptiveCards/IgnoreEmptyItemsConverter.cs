// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// JSON converter that will drop empty element items.
    /// </summary>
    /// <typeparam name="T">Type of the objects to be converted.</typeparam>
    public class IgnoreEmptyItemsConverter<T> : JsonConverter<List<T>>
    {
        /// <summary>
        /// The <see cref="ParseContext"/> for element tracking.
        /// </summary>
        public ParseContext ParseContext { get; set; } = new ParseContext();

        private readonly List<AdaptiveWarning> _warnings;

        /// <summary>
        /// Initializes a new instance with a default ParseContext.
        /// </summary>
        public IgnoreEmptyItemsConverter() { _warnings = new List<AdaptiveWarning>(); }

        /// <summary>
        /// Initializes a new instance with the given ParseContext.
        /// </summary>
        public IgnoreEmptyItemsConverter(ParseContext parseContext)
        {
            ParseContext = parseContext ?? new ParseContext();
            _warnings = new List<AdaptiveWarning>();
        }

        /// <summary>
        /// Initializes a new instance with the given ParseContext and warnings list.
        /// </summary>
        public IgnoreEmptyItemsConverter(ParseContext parseContext, List<AdaptiveWarning> warnings)
        {
            ParseContext = parseContext ?? new ParseContext();
            _warnings = warnings ?? new List<AdaptiveWarning>();
        }

        /// <inheritdoc />
        public override List<T> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var node = JsonNode.Parse(ref reader);

            JsonArray jArray;

            if (node is JsonObject jObj && jObj.Count > 0 && jObj.ContainsKey("$values"))
            {
                jArray = jObj["$values"]?.AsArray() ?? new JsonArray();
            }
            else if (node is JsonArray arr)
            {
                jArray = arr;
            }
            else
            {
                return new List<T>();
            }

            ParseContext.Type = (typeof(T) == typeof(AdaptiveElement)) ? ParseContext.ContextType.Element : ParseContext.ContextType.Action;

            // Check if T is an AdaptiveTypedElement - if so, use the inner converter directly
            bool isTypedElement = typeof(AdaptiveTypedElement).IsAssignableFrom(typeof(T));

            var result = new List<T>();
            foreach (var item in jArray)
            {
                if (item is JsonObject obj && obj.Count > 0)
                {
                    T deserialized;
                    if (isTypedElement)
                    {
                        // Use the inner converter directly to handle polymorphic dispatch
                        var innerConverter = new AdaptiveTypedElementInnerConverter(_warnings, ParseContext);
                        var bytes = System.Text.Encoding.UTF8.GetBytes(obj.ToJsonString());
                        var readerCopy = new Utf8JsonReader(bytes);
                        deserialized = (T)(object)innerConverter.Read(ref readerCopy, typeof(T), options);
                    }
                    else
                    {
                        deserialized = obj.Deserialize<T>(options);
                    }
                    
                    if (deserialized != null)
                    {
                        result.Add(deserialized);
                    }
                }
            }

            return result;
        }

        /// <inheritdoc />
        public override void Write(Utf8JsonWriter writer, List<T> value, JsonSerializerOptions options)
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
