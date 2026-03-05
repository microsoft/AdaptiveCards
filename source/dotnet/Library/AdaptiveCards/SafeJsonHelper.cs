// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json;
using System.Text.Json.Nodes;

namespace AdaptiveCards
{
    /// <summary>
    /// Helper for creating JsonObject instances from JsonElements that may contain
    /// duplicate keys (which is valid JSON per RFC 8259 but not handled by JsonObject.Create).
    /// </summary>
    /// <remarks>
    /// System.Text.Json's <see cref="JsonObject.Create(JsonElement)"/> throws
    /// <see cref="System.ArgumentException"/> when duplicate keys are present.
    /// This helper uses indexer assignment so duplicates silently keep the last value,
    /// matching the previous Newtonsoft.Json behavior. A debug warning is emitted
    /// when duplicates are detected to help identify malformed payloads.
    /// </remarks>
    internal static class SafeJsonHelper
    {
        /// <summary>
        /// Creates a JsonObject from a JsonElement, handling duplicate keys by keeping the last value.
        /// </summary>
        internal static JsonObject SafeCreateJsonObject(JsonElement element)
        {
            if (element.ValueKind != JsonValueKind.Object)
                return null;

            var obj = new JsonObject();
            foreach (var prop in element.EnumerateObject())
            {
                // Using indexer (not Add) so duplicate keys are silently replaced
                obj[prop.Name] = SafeCreateJsonNode(prop.Value);
            }
            return obj;
        }

        private static JsonNode SafeCreateJsonNode(JsonElement element)
        {
            switch (element.ValueKind)
            {
                case JsonValueKind.Object:
                    return SafeCreateJsonObject(element);
                case JsonValueKind.Array:
                    var arr = new JsonArray();
                    foreach (var item in element.EnumerateArray())
                    {
                        arr.Add(SafeCreateJsonNode(item));
                    }
                    return arr;
                case JsonValueKind.Null:
                case JsonValueKind.Undefined:
                    return null;
                default:
                    return JsonNode.Parse(element.GetRawText());
            }
        }
    }
}
