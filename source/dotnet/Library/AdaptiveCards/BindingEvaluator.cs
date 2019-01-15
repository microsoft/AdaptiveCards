using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public static class BindingEvaluator
    {
        private const string REGEX_PROPERTY_NAME = @"[a-zA-Z_$@][0-9a-zA-Z_$@]*";
        private const string REGEX_PROPERTY_ACCESSOR = @"\.(" + REGEX_PROPERTY_NAME + @")";
        private const string REGEX_DICTIONARY_LOOKUP = @"\['(([^']|\\')+)'\]";
        private const string REGEX_BINDING_EXPRESSION = @"\{(" + REGEX_PROPERTY_NAME + @"((" + REGEX_DICTIONARY_LOOKUP + @")|(" + REGEX_PROPERTY_ACCESSOR + @"))*)\}";

        public static T EvaluateBinding<T>(JObject data, string bindingExpression)
        {
            object answer = EvaluateBinding(data, bindingExpression);
            if (answer is T)
            {
                return (T)answer;
            }
            if (typeof(T) == typeof(string) && answer != null)
            {
                object answerAsString = answer.ToString();
                return (T)(answerAsString);
            }

            return default(T);
        }

        public static object EvaluateBinding(JObject data, string bindingExpression)
        {
            // If it's all one single expression
            // (This is a temporary hack for resolving correct data types)
            if (Regex.IsMatch(bindingExpression, "^" + REGEX_BINDING_EXPRESSION + "$"))
            {
                return EvaluateSingleBinding(data, bindingExpression);
            }

            Regex regex = new Regex(REGEX_BINDING_EXPRESSION);
            var evaluator = new MyMatchEvaluator(data);

            string replaced = regex.Replace(bindingExpression, evaluator.ReplaceBinding);

            return replaced;
        }

        public static object EvaluateSingleBinding(JObject data, string singleBindingExpression)
        {
            var match = Regex.Match(singleBindingExpression, "^" + REGEX_BINDING_EXPRESSION + "$");
            if (match.Success && match.Groups[1].Success)
            {
                string insideBindingBrackets = match.Groups[1].Value;
                Match firstPropertyMatch = Regex.Match(insideBindingBrackets, "^" + REGEX_PROPERTY_NAME);
                if (firstPropertyMatch.Success)
                {
                    // First property must be data
                    if (firstPropertyMatch.Value == "data")
                    {
                        if (insideBindingBrackets.Length > firstPropertyMatch.Length)
                        {
                            return EvalulatePropertyExpression(data, insideBindingBrackets.Substring(firstPropertyMatch.Length));
                        }
                    }
                }
            }

            return null;
        }

        private class MyMatchEvaluator
        {
            private JObject _data;
            public MyMatchEvaluator(JObject data)
            {
                _data = data;
            }

            public string ReplaceBinding(Match m)
            {
                return EvaluateSingleBinding(_data, m.Value)?.ToString();
            }
        }

        /// <summary>
        /// Evaluates full property accessor expressions, like ".person.name" or ".person['First Name']", etc
        /// </summary>
        /// <param name="data"></param>
        /// <param name="propertyExpression"></param>
        /// <returns></returns>
        public static object EvalulatePropertyExpression(JObject data, string propertyExpression)
        {
            if (data == null)
            {
                return null;
            }

            object nextData = null;
            string matchedText = null;

            Regex regex = new Regex("^" + REGEX_PROPERTY_ACCESSOR);
            var matchPropertyAccessor = regex.Match(propertyExpression);
            if (matchPropertyAccessor.Success && matchPropertyAccessor.Groups[1].Success)
            {
                string property = matchPropertyAccessor.Groups[1].Value;
                nextData = GetProperty(data, property);
                matchedText = matchPropertyAccessor.Value;
            }
            else
            {
                regex = new Regex("^" + REGEX_DICTIONARY_LOOKUP);
                var matchDictionary = regex.Match(propertyExpression);
                if (matchDictionary.Success && matchDictionary.Groups[1].Success)
                {
                    string dictionaryAccessor = matchDictionary.Groups[1].Value;
                    nextData = GetProperty(data, dictionaryAccessor);
                    matchedText = matchDictionary.Value;
                }
            }

            if (nextData != null)
            {
                if (matchedText.Length < propertyExpression.Length)
                {
                    return EvalulatePropertyExpression(nextData as JObject, propertyExpression.Substring(matchedText.Length));
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
        public static object GetProperty(JObject data, string property)
        {
            if (data != null && data.TryGetValue(property, out JToken value))
            {
                switch (value.Type)
                {
                    case JTokenType.String:
                        return value.Value<string>();

                    case JTokenType.Date:
                        // Temporary hack for date binding. Note that this will modify format of other date-like strings, which could be undesired.
                        return value.Value<DateTime>().ToUniversalTime().ToString("s") + "Z";
                }
                return value;
            }

            return null;
        }
    }
}
