// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Handles polymorphic deserialization and serialization of single-value AdaptiveAction properties
    /// (e.g., SelectAction, InlineAction). This converter is NOT stripped by
    /// GetOptionsWithoutThisConverter, so it remains available in stripped options.
    /// </summary>
    internal class AdaptiveActionPolymorphicConverter : JsonConverter<AdaptiveAction>
    {
        private readonly List<AdaptiveWarning> _warnings;
        private readonly ParseContext _parseContext;

        public AdaptiveActionPolymorphicConverter()
        {
            _warnings = new List<AdaptiveWarning>();
            _parseContext = new ParseContext();
        }

        public AdaptiveActionPolymorphicConverter(List<AdaptiveWarning> warnings, ParseContext parseContext)
        {
            _warnings = warnings ?? new List<AdaptiveWarning>();
            _parseContext = parseContext ?? new ParseContext();
        }

        /// <summary>
        /// Only handle the abstract AdaptiveAction type, not concrete subclasses.
        /// </summary>
        public override bool CanConvert(Type typeToConvert)
        {
            return typeToConvert == typeof(AdaptiveAction);
        }

        public override AdaptiveAction Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var doc = JsonDocument.ParseValue(ref reader);
            var jObject = SafeJsonHelper.SafeCreateJsonObject(doc.RootElement);

            if (jObject == null)
                return null;

            string typeName = jObject["type"]?.GetValue<string>();

            if (typeName != null &&
                AdaptiveTypedElementConverter.TypedElementTypes.Value.TryGetValue(typeName, out var type) &&
                typeof(AdaptiveAction).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
            {
                string objectId = jObject["id"]?.GetValue<string>();
                AdaptiveInternalID internalID = AdaptiveInternalID.Next();
                _parseContext.PushElement(objectId, internalID);

                try
                {
                    var result = (AdaptiveAction)jObject.Deserialize(type, options);
                    if (result != null)
                        result.InternalID = internalID;
                    return result;
                }
                catch (JsonException)
                {
                    return (AdaptiveAction)Activator.CreateInstance(type);
                }
                finally
                {
                    _parseContext.PopElement();
                }
            }
            else if (typeName != null)
            {
                // Unknown action type - for single-value action properties (SelectAction, InlineAction),
                // return null so the property stays unset, matching expected behavior
                _warnings?.Add(new AdaptiveWarning(-1, $"Unknown element '{typeName}'"));
                return null;
            }

            return null;
        }

        public override void Write(Utf8JsonWriter writer, AdaptiveAction value, JsonSerializerOptions options)
        {
            if (value == null)
            {
                writer.WriteNullValue();
                return;
            }
            JsonSerializer.Serialize(writer, value, value.GetType(), options);
        }
    }
}
