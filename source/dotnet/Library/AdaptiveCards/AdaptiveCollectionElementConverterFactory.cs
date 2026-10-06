// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Converter that forces System.Text.Json to treat AdaptiveCollectionElement subclasses
    /// as JSON objects rather than collections.
    /// </summary>
    /// <remarks>
    /// <para>
    /// <b>Why this is needed:</b> <see cref="AdaptiveCollectionElement"/> implements
    /// <see cref="System.Collections.Generic.IEnumerable{AdaptiveElement}"/> so that C# developers
    /// can use <c>foreach</c> and collection initializer syntax on containers. However, System.Text.Json
    /// automatically treats any type implementing <c>IEnumerable&lt;T&gt;</c> as a JSON array. The
    /// Adaptive Card spec defines containers as JSON objects (with an <c>items</c> array property),
    /// not as arrays themselves.
    /// </para>
    /// <para>
    /// This converter intercepts serialization/deserialization of concrete <see cref="AdaptiveCollectionElement"/>
    /// subclasses (<see cref="AdaptiveContainer"/>, <see cref="AdaptiveColumn"/>,
    /// <see cref="AdaptiveColumnSet"/>, <see cref="AdaptiveTable"/>, <see cref="AdaptiveTableCell"/>,
    /// <see cref="AdaptiveTableRow"/>) and uses reflection to read/write each property individually,
    /// ensuring they are treated as JSON objects.
    /// </para>
    /// <para>
    /// In the previous Newtonsoft.Json implementation, this was handled by the <c>[JsonObject]</c>
    /// attribute which explicitly marked these types as objects. System.Text.Json has no equivalent
    /// attribute, so this converter is required.
    /// </para>
    /// </remarks>
    internal class AdaptiveCollectionElementConverterFactory : JsonConverterFactory
    {
        public override bool CanConvert(Type typeToConvert)
        {
            return typeof(AdaptiveCollectionElement).IsAssignableFrom(typeToConvert) && !typeToConvert.IsAbstract;
        }

        public override JsonConverter CreateConverter(Type typeToConvert, JsonSerializerOptions options)
        {
            var converterType = typeof(AdaptiveCollectionElementConverter<>).MakeGenericType(typeToConvert);
            return (JsonConverter)Activator.CreateInstance(converterType);
        }
    }

    internal class AdaptiveCollectionElementConverter<T> : JsonConverter<T> where T : AdaptiveCollectionElement, new()
    {
        public override T Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            // Parse the JSON into a JsonObject
            var doc = JsonDocument.ParseValue(ref reader);
            var jsonObj = SafeJsonHelper.SafeCreateJsonObject(doc.RootElement);
            if (jsonObj == null) return new T();

            // Create the instance  
            var instance = new T();
            
            // Populate each property manually using the JsonSerializerOptions' naming policy
            var namingPolicy = options.PropertyNamingPolicy;
            
            foreach (var prop in typeToConvert.GetProperties(BindingFlags.Public | BindingFlags.Instance))
            {
                if (!prop.CanWrite) continue;
                if (prop.GetIndexParameters().Length > 0) continue; // Skip indexers
                if (prop.GetCustomAttribute<JsonIgnoreAttribute>() is JsonIgnoreAttribute ignore && ignore.Condition == JsonIgnoreCondition.Always) continue;

                // Determine the JSON property name
                string jsonName;
                var nameAttr = prop.GetCustomAttribute<JsonPropertyNameAttribute>();
                if (nameAttr != null)
                {
                    jsonName = nameAttr.Name;
                }
                else if (namingPolicy != null)
                {
                    jsonName = namingPolicy.ConvertName(prop.Name);
                }
                else
                {
                    jsonName = prop.Name;
                }

                if (string.IsNullOrEmpty(jsonName) || !jsonObj.ContainsKey(jsonName)) continue;
                
                var jsonNode = jsonObj[jsonName];
                if (jsonNode == null) continue;

                try
                {
                    object value;
                    
                    // Check for property-level [JsonConverter] attribute
                    var converterAttr = prop.GetCustomAttribute<JsonConverterAttribute>();
                    if (converterAttr != null && converterAttr.ConverterType != null)
                    {
                        // Deserialize using the property's specific converter
                        var jsonString = jsonNode.ToJsonString();
                        var bytes = System.Text.Encoding.UTF8.GetBytes(jsonString);
                        value = JsonSerializer.Deserialize(bytes, prop.PropertyType, 
                            new JsonSerializerOptions(options)
                            {
                                Converters = { (JsonConverter)Activator.CreateInstance(converterAttr.ConverterType) }
                            });
                    }
                    else
                    {
                        // Use default deserialization for the property type
                        value = jsonNode.Deserialize(prop.PropertyType, options);
                    }
                    
                    if (value != null)
                    {
                        prop.SetValue(instance, value);
                    }
                }
                catch
                {
                    // Skip properties that fail to deserialize (matches Newtonsoft error-swallowing behavior)
                }
            }

            // Handle [JsonExtensionData] — additional properties
            foreach (var prop in typeToConvert.GetProperties(BindingFlags.Public | BindingFlags.Instance))
            {
                if (prop.GetCustomAttribute<JsonExtensionDataAttribute>() != null && prop.CanRead)
                {
                    var dict = prop.GetValue(instance) as System.Collections.Generic.Dictionary<string, JsonElement>;
                    if (dict != null)
                    {
                        var knownNames = new System.Collections.Generic.HashSet<string>();
                        foreach (var p in typeToConvert.GetProperties(BindingFlags.Public | BindingFlags.Instance))
                        {
                            if (p.GetCustomAttribute<JsonExtensionDataAttribute>() != null) continue;
                            if (p.GetCustomAttribute<JsonIgnoreAttribute>() is JsonIgnoreAttribute ig && ig.Condition == JsonIgnoreCondition.Always) continue;
                            var n = p.GetCustomAttribute<JsonPropertyNameAttribute>()?.Name ?? (namingPolicy?.ConvertName(p.Name) ?? p.Name);
                            knownNames.Add(n);
                        }

                        foreach (var kvp in jsonObj)
                        {
                            if (!knownNames.Contains(kvp.Key) && kvp.Value != null)
                            {
                                dict[kvp.Key] = kvp.Value.Deserialize<JsonElement>();
                            }
                        }
                    }
                    break;
                }
            }

            return instance;
        }

        public override void Write(Utf8JsonWriter writer, T value, JsonSerializerOptions options)
        {
            // Write as a JSON object manually
            writer.WriteStartObject();
            
            var namingPolicy = options.PropertyNamingPolicy;
            
            foreach (var prop in typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance))
            {
                if (!prop.CanRead) continue;
                if (prop.GetIndexParameters().Length > 0) continue; // Skip indexers
                if (prop.GetCustomAttribute<JsonExtensionDataAttribute>() != null) continue;

                var ignoreAttr = prop.GetCustomAttribute<JsonIgnoreAttribute>();
                if (ignoreAttr != null && ignoreAttr.Condition == JsonIgnoreCondition.Always) continue;

                string jsonName;
                var nameAttr = prop.GetCustomAttribute<JsonPropertyNameAttribute>();
                if (nameAttr != null)
                {
                    jsonName = nameAttr.Name;
                }
                else if (namingPolicy != null)
                {
                    jsonName = namingPolicy.ConvertName(prop.Name);
                }
                else
                {
                    jsonName = prop.Name;
                }

                if (string.IsNullOrEmpty(jsonName)) continue;

                var propValue = prop.GetValue(value);
                var propType = prop.PropertyType;

                // Determine the effective ignore condition: per-property attribute overrides the global option.
                var effectiveCondition = (ignoreAttr != null)
                    ? ignoreAttr.Condition
                    : options.DefaultIgnoreCondition;

                // Apply the effective ignore condition
                if (effectiveCondition == JsonIgnoreCondition.WhenWritingNull && propValue == null) continue;
                if (effectiveCondition == JsonIgnoreCondition.WhenWritingDefault)
                {
                    if (propValue == null) continue;
                    // For value types compare against the type's default (e.g. false for bool, 0 for enum).
                    // Activator.CreateInstance always returns a non-null boxed value for value types so
                    // the null-conditional guard here is purely defensive.
                    if (propType.IsValueType)
                    {
                        var underlyingType = Nullable.GetUnderlyingType(propType) ?? propType;
                        var typeDefault = Activator.CreateInstance(underlyingType);
                        if (typeDefault == null || propValue.Equals(typeDefault)) continue;
                    }
                }

                writer.WritePropertyName(jsonName);
                JsonSerializer.Serialize(writer, propValue, propType, options);
            }

            // Write extension data
            foreach (var prop in typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance))
            {
                if (prop.GetCustomAttribute<JsonExtensionDataAttribute>() != null)
                {
                    var dict = prop.GetValue(value) as System.Collections.Generic.Dictionary<string, JsonElement>;
                    if (dict != null)
                    {
                        foreach (var kvp in dict)
                        {
                            writer.WritePropertyName(kvp.Key);
                            kvp.Value.WriteTo(writer);
                        }
                    }
                    break;
                }
            }

            writer.WriteEndObject();
        }
    }
}
