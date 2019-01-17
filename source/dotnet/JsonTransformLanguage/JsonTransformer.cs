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

        public static JToken Transform(JToken input, JToken data, Dictionary<string, JToken> additionalReservedProperties)
        {
            return Transform(input, data, props: null, index: -1, parentIsArray: false, types: new JsonTransformerTypes(), context: new JsonTransformerContext(data, additionalReservedProperties));
        }

        private static JToken Transform(JToken input, JToken parentData, JToken props, int index, bool parentIsArray, JsonTransformerTypes types, JsonTransformerContext context)
        {
            if (parentData is JArray parentDataArray)
            {
                if (!parentIsArray)
                {
                    // If we can't repeat, we select the first item in the array
                    context.Warnings.AddWarning("Current data is an array, but parent item isn't an array. Selecting the first item for current data.");
                    parentData = parentDataArray.FirstOrDefault();
                }
            }

            switch (input.Type)
            {
                case JTokenType.Array:
                    return TransformArray(input as JArray, parentData, props, index, types, context);

                case JTokenType.String:
                    return JsonStringTransformer.Transform(input.Value<string>(), parentData, props, index, context);

                case JTokenType.Object:
                    return TransformObject(input as JObject, parentData, props, index, false, types, context).FirstOrDefault();
            }

            return input.DeepClone();
        }

        private static JArray TransformArray(JArray inputArray, JToken parentData, JToken props, int index, JsonTransformerTypes types, JsonTransformerContext context)
        {
            var newArray = new JArray();
            foreach (var child in inputArray)
            {
                if (child is JObject childObj)
                {
                    var newChildren = TransformObject(childObj, parentData, props, index, true, types, context);
                    foreach (var newChild in newChildren)
                    {
                        newArray.Add(newChild);
                    }
                }
                else
                {
                    var newChild = Transform(child, parentData, props, index, true, types, context);
                    if (newChild != null)
                    {
                        newArray.Add(newChild);
                    }
                }
            }
            return newArray;
        }

        private static List<JObject> TransformObject(JObject input, JToken parentData, JToken props, int index, bool parentIsArray, JsonTransformerTypes types, JsonTransformerContext context)
        {
            List<JObject> answer = new List<JObject>();
            JToken currData = null;

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
                        types = types.Merge(newTypes);
                    }
                }
                catch { }
            }

            // If data is specified
            if (input.TryGetValue(PROP_DATA, out JToken dataVal))
            {
                // Transform and use the data
                currData = Transform(dataVal, parentData, props, index, false, types, context);

                // If we couldn't find the data, we drop the entire element
                if (currData == null)
                {
                    return answer;
                }
            }
            else
            {
                // Otherwise, inherit parent's data
                currData = parentData;
            }

            // If current data is an array
            if (currData != null && currData is JArray array)
            {
                // If our parent is an array type, we repeat
                if (parentIsArray)
                {
                    int i = 0;
                    foreach (var dataItem in array)
                    {
                        JObject newRepeatedItem = input.DeepClone() as JObject;
                        newRepeatedItem.Remove(PROP_DATA);

                        foreach (var transformed in TransformObject(newRepeatedItem, dataItem, props, i, true, types, context))
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
                    currData = array.FirstOrDefault();
                }
            }

            // Evaluate when clause
            // TODO

            var newItem = new JObject();

            // Transform each property value
            foreach (var p in input.Properties().ToArray())
            {
                var transformedPropertyValue = Transform(p.Value, currData, props, index, false, types, context);
                if (transformedPropertyValue != null)
                {
                    newItem.Add(p.Name, transformedPropertyValue);
                }
            }

            // If custom type
            if (newItem.TryGetValue(PROP_TYPE, out JToken typeToken) && typeToken.Type == JTokenType.String)
            {
                var typeString = typeToken.Value<string>();
                if (types.TryGetDefinition(typeString, out JToken definition) && definition is JObject definitionObj)
                {
                    foreach (var newTransformedItem in TransformObject(definitionObj, currData, newItem, index, parentIsArray, types, context))
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
