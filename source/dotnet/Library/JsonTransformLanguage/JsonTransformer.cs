using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;

namespace JsonTransformLanguage
{
    public static class JsonTransformer
    {
        private const string PROP_DATA = "$data";
        private const string PROP_TYPE = "$type";
        private const string PROP_TYPES = "$types";
        private const string PROP_WHEN = "$when";

        public static JToken Transform(JToken input, JToken data, Dictionary<string, JToken> additionalReservedProperties)
        {
            return Transform(input, new JsonTransformerContext(data, additionalReservedProperties));
        }

        private static JToken Transform(JToken input,  JsonTransformerContext context)
        {
            if (context.ReservedProperties.Data is JArray dataArray)
            {
                if (!context.ParentIsArray)
                {
                    // If we can't repeat, we select the first item in the array
                    context.Warnings.AddWarning("Current data is an array, but parent item isn't an array. Selecting the first item for current data.");
                    context.ReservedProperties.Data = dataArray.FirstOrDefault();
                }
            }

            switch (input.Type)
            {
                case JTokenType.Array:
                    return TransformArray(input as JArray, new JsonTransformerContext(context));

                case JTokenType.String:
                    return JsonStringTransformer.Transform(input.Value<string>(), new JsonTransformerContext(context));

                case JTokenType.Object:
                    return TransformObject(input as JObject, new JsonTransformerContext(context)).FirstOrDefault();
            }

            return input.DeepClone();
        }

        private static JArray TransformArray(JArray inputArray, JsonTransformerContext context)
        {
            var newArray = new JArray();
            foreach (var child in inputArray)
            {
                if (child is JObject childObj)
                {
                    var newChildren = TransformObject(childObj, new JsonTransformerContext(context)
                    {
                        ParentIsArray = true
                    });
                    foreach (var newChild in newChildren)
                    {
                        newArray.Add(newChild);
                    }
                }
                else
                {
                    var newChild = Transform(child, new JsonTransformerContext(context)
                    {
                        ParentIsArray = true
                    });
                    if (newChild != null)
                    {
                        newArray.Add(newChild);
                    }
                }
            }
            return newArray;
        }

        private static List<JObject> TransformObject(JObject input, JsonTransformerContext context)
        {
            List<JObject> answer = new List<JObject>();

            // Clone it since we'll be modifying it
            input = input.DeepClone() as JObject;

            // If new custom types are declared
            if (input.TryGetValue(PROP_TYPES, out JToken typesAsToken))
            {
                input.Remove(PROP_TYPES);
                try
                {
                    // We need to obtain them before applying data binding
                    var newTypes = typesAsToken.ToObject<JsonTransformerTypes>();
                    if (newTypes != null)
                    {
                        context.Types = context.Types.Merge(newTypes);
                    }
                }
                catch { }
            }

            // If data is specified
            if (input.TryGetValue(PROP_DATA, out JToken dataVal))
            {
                // Remove the data property
                input.Remove(PROP_DATA);

                // Transform and use the data
                context.ReservedProperties.Data = Transform(dataVal, new JsonTransformerContext(context)
                {
                    ParentIsArray = false
                });

                // If we couldn't find the data, we drop the entire element
                if (context.ReservedProperties.Data == null)
                {
                    return answer;
                }
            }
            else
            {
                // Otherwise, inherit parent's data
            }

            // If current data is an array
            if (context.ReservedProperties.Data != null && context.ReservedProperties.Data is JArray array)
            {
                // If our parent is an array type, we repeat
                if (context.ParentIsArray)
                {
                    int i = 0;
                    foreach (var dataItem in array)
                    {
                        JObject newRepeatedItem = input.DeepClone() as JObject;
                        newRepeatedItem.Remove(PROP_DATA);

                        foreach (var transformed in TransformObject(newRepeatedItem, new JsonTransformerContext(context)
                        {
                            ReservedProperties = new JsonTransformerReservedProperties(context.ReservedProperties)
                            {
                                Data = dataItem,
                                Index = i
                            }
                        }))
                        {
                            answer.Add(transformed);
                        }
                        i++;
                    }
                    return answer;
                }
                else
                {
                    context.Warnings.AddWarning("Data was an array on item that isn't a child of an array. Selecting first item of data array.");
                    context.ReservedProperties.Data = array.FirstOrDefault();
                }
            }

            // Evaluate when clause
            if (input.TryGetValue(PROP_WHEN, out JToken whenToken))
            {
                input.Remove(PROP_WHEN);

                var transformedWhenValue = Transform(whenToken, new JsonTransformerContext(context)
                {
                    ParentIsArray = false
                });

                // If it evaluated to true
                if (transformedWhenValue != null && transformedWhenValue.Type == JTokenType.Boolean && transformedWhenValue.Value<bool>())
                {
                    // Keep it
                }
                else
                {
                    // Otherwise, drop it
                    return answer;
                }
            }

            var newItem = new JObject();

            // Transform each property value
            foreach (var p in input.Properties().ToArray())
            {
                var transformedPropertyValue = Transform(p.Value, new JsonTransformerContext(context)
                {
                    ParentIsArray = false
                });
                if (transformedPropertyValue != null)
                {
                    newItem.Add(p.Name, transformedPropertyValue);
                }
            }

            // If custom type
            if (newItem.TryGetValue(PROP_TYPE, out JToken typeToken) && typeToken.Type == JTokenType.String)
            {
                var typeString = typeToken.Value<string>();
                if (context.Types.TryGetDefinition(typeString, out JToken definition) && definition is JObject definitionObj)
                {
                    foreach (var newTransformedItem in TransformObject(definitionObj, new JsonTransformerContext(context)
                    {
                        ReservedProperties = new JsonTransformerReservedProperties(context.ReservedProperties)
                        {
                            Props = newItem
                        }
                    }))
                    {
                        answer.Add(newTransformedItem);
                    }
                    return answer;
                }
            }

            answer.Add(newItem);
            return answer;
        }
    }
}
