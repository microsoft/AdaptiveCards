using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace JsonTransformLanguage
{
    internal static class JsonStringTransformer
    {
        private const string ID_DATA = "$data";
        private const string ID_PROPS = "$props";

        internal static JToken Transform(string input, JsonTransformerContext context)
        {
            return EvaluateBinding(input, context);
        }

        private const string REGEX_PROPERTY_NAME = @"[a-zA-Z_$@][0-9a-zA-Z_$@]*";
        private const string REGEX_PROPERTY_ACCESSOR = @"\.(" + REGEX_PROPERTY_NAME + @")";
        private const string REGEX_DICTIONARY_LOOKUP = @"\['(([^']|\\')+)'\]";
        private const string REGEX_INDEX_ACCESSOR = @"\[(\d+)\]";
        private const string REGEX_BINDING_EXPRESSION = @"\{(" + REGEX_PROPERTY_NAME + @"((" + REGEX_DICTIONARY_LOOKUP + @")|(" + REGEX_INDEX_ACCESSOR + @")|(" + REGEX_PROPERTY_ACCESSOR + @"))*)\}";

        public static JToken EvaluateBinding(string bindingExpression, JsonTransformerContext context)
        {
            // If it's all one single expression
            // (This is a temporary hack for resolving correct data types)
            if (Regex.IsMatch(bindingExpression, "^" + REGEX_BINDING_EXPRESSION + "$"))
            {
                return EvaluateSingleBinding(bindingExpression, context);
            }

            Regex regex = new Regex(REGEX_BINDING_EXPRESSION);
            var evaluator = new MyMatchEvaluator(context);

            string replaced = regex.Replace(bindingExpression, evaluator.ReplaceBinding);

            return replaced;
        }

        public static JToken EvaluateSingleBinding(string singleBindingExpression, JsonTransformerContext context)
        {
            var match = Regex.Match(singleBindingExpression, "^" + REGEX_BINDING_EXPRESSION + "$");
            if (match.Success && match.Groups[1].Success)
            {
                string insideBindingBrackets = match.Groups[1].Value;
                Match firstPropertyMatch = Regex.Match(insideBindingBrackets, "^" + REGEX_PROPERTY_NAME);
                if (firstPropertyMatch.Success)
                {
                    string remainingToParse = insideBindingBrackets;
                    JToken data;
                    if (firstPropertyMatch.Value.StartsWith("$"))
                    {
                        if (firstPropertyMatch.Value == ID_DATA)
                        {
                            data = context.ParentData;
                        }
                        else if (firstPropertyMatch.Value == ID_PROPS)
                        {
                            data = context.Props;
                        }
                        else if (context.AdditionalReservedProperties.TryGetValue(firstPropertyMatch.Value, out JToken reservedData))
                        {
                            data = reservedData;
                        }
                        else
                        {
                            return null;
                        }

                        remainingToParse = remainingToParse.Substring(firstPropertyMatch.Length);
                    }
                    else
                    {
                        remainingToParse = "." + remainingToParse;
                        data = context.ParentData;
                    }

                    if (remainingToParse.Length > 0)
                    {
                        return EvalulatePropertyExpression(remainingToParse, new JsonTransformerContext(context)
                        {
                            ParentData = data
                        });
                    }

                    return data;
                }
            }

            return null;
        }

        private class MyMatchEvaluator
        {
            private JsonTransformerContext _context;
            public MyMatchEvaluator(JsonTransformerContext context)
            {
                _context = context;
            }

            public string ReplaceBinding(Match m)
            {
                return EvaluateSingleBinding(m.Value, _context)?.ToString();
            }
        }

        /// <summary>
        /// Evaluates full property accessor expressions, like ".person.name" or ".person['First Name']", etc
        /// </summary>
        /// <param name="data"></param>
        /// <param name="propertyExpression"></param>
        /// <returns></returns>
        public static JToken EvalulatePropertyExpression(string propertyExpression, JsonTransformerContext context)
        {
            if (context.ParentData == null)
            {
                return null;
            }

            JToken nextData = null;
            string matchedText = null;

            Regex regex = new Regex("^" + REGEX_PROPERTY_ACCESSOR);
            var matchPropertyAccessor = regex.Match(propertyExpression);
            if (matchPropertyAccessor.Success && matchPropertyAccessor.Groups[1].Success)
            {
                string property = matchPropertyAccessor.Groups[1].Value;
                nextData = GetProperty(context.ParentData, property);
                matchedText = matchPropertyAccessor.Value;
            }
            else
            {
                regex = new Regex("^" + REGEX_DICTIONARY_LOOKUP);
                var matchDictionary = regex.Match(propertyExpression);
                if (matchDictionary.Success && matchDictionary.Groups[1].Success)
                {
                    string dictionaryAccessor = matchDictionary.Groups[1].Value;
                    nextData = GetProperty(context.ParentData, dictionaryAccessor);
                    matchedText = matchDictionary.Value;
                }
                else
                {
                    regex = new Regex("^" + REGEX_INDEX_ACCESSOR);
                    var matchIndex = regex.Match(propertyExpression);
                    if (matchIndex.Success && matchIndex.Groups[1].Success && int.TryParse(matchIndex.Groups[1].Value, out int indexToAccess))
                    {
                        nextData = context.ParentData.ElementAtOrDefault(indexToAccess);
                        matchedText = matchIndex.Value;
                    }
                }
            }

            if (nextData != null)
            {
                if (matchedText.Length < propertyExpression.Length)
                {
                    return EvalulatePropertyExpression(propertyExpression.Substring(matchedText.Length), new JsonTransformerContext(context)
                    {
                        ParentData = nextData
                    });
                }
                else
                {
                    return nextData;
                }
            }

            return null;
        }

        /// <summary>
        /// Gets one level property
        /// </summary>
        /// <param name="data"></param>
        /// <param name="property"></param>
        /// <returns></returns>
        public static JToken GetProperty(JToken data, string property)
        {
            if (data is JObject dataObj && dataObj.TryGetValue(property, out JToken value))
            {
                return value;
            }

            return null;
        }
    }
}
