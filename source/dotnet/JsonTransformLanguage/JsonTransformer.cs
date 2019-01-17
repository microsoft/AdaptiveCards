using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;

namespace JsonTransformLanguage
{
    public static class JsonTransformer
    {
        internal const string PROP_DATA = "$data";

        public static JToken Transform(JToken input, JToken data, Dictionary<string, JToken> additionalReservedProperties)
        {
            return Transform(input, data, index: -1, parentIsArray: false, context: new JsonTransformerContext(data, additionalReservedProperties));
        }

        private static JToken Transform(JToken input, JToken parentData, int index, bool parentIsArray, JsonTransformerContext context)
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
                    return TransformArray(input as JArray, parentData, index, context);

                case JTokenType.String:
                    return JsonStringTransformer.Transform(input.Value<string>(), parentData, index, context);

                case JTokenType.Object:
                    return TransformObject(input as JObject, parentData, index, false, context).FirstOrDefault();
            }

            return input.DeepClone();
        }

        private static JArray TransformArray(JArray inputArray, JToken parentData, int index, JsonTransformerContext context)
        {
            var newArray = new JArray();
            foreach (var child in inputArray)
            {
                if (child is JObject childObj)
                {
                    var newChildren = TransformObject(childObj, parentData, index, true, context);
                    foreach (var newChild in newChildren)
                    {
                        newArray.Add(newChild);
                    }
                }
                else
                {
                    var newChild = Transform(child, parentData, index, true, context);
                    if (newChild != null)
                    {
                        newArray.Add(newChild);
                    }
                }
            }
            return newArray;
        }

        private static List<JObject> TransformObject(JObject input, JToken parentData, int index, bool parentIsArray, JsonTransformerContext context)
        {
            List<JObject> answer = new List<JObject>();
            JToken currData = null;

            // If data is specified
            if (input.TryGetValue(PROP_DATA, out JToken dataVal))
            {
                // Transform and use the data
                currData = Transform(dataVal, parentData, index, false, context);

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
                        answer.AddRange(TransformObject(newRepeatedItem, dataItem, i, true, context));
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
                var transformedPropertyValue = Transform(p.Value, currData, index, false, context);
                if (transformedPropertyValue != null)
                {
                    newItem.Add(p.Name, transformedPropertyValue);
                }
            }

            answer.Add(newItem);
            return answer;
        }
    }
}
