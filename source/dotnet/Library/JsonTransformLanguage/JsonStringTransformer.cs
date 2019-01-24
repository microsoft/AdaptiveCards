using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using JsonTransformLanguage.Grammars;
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

        private const string REGEX_OPERATOR = @"\s*((==)|(!=))\s*";
        private const string REGEX_PROPERTY_NAME = @"[a-zA-Z_$@][0-9a-zA-Z_$@]*";
        private const string REGEX_PROPERTY_ACCESSOR = @"\.(" + REGEX_PROPERTY_NAME + @")";
        private const string REGEX_DICTIONARY_LOOKUP = @"\['(([^']|\\')+)'\]";
        private const string REGEX_INDEX_ACCESSOR = @"\[(\d+)\]";
        private const string REGEX_ACCESSOR_EXPRESSION = @"((" + REGEX_DICTIONARY_LOOKUP + @")|(" + REGEX_INDEX_ACCESSOR + @")|(" + REGEX_PROPERTY_ACCESSOR + @"))";
        private const string REGEX_OBJECT_EXPRESSION = REGEX_PROPERTY_NAME + "(" + REGEX_ACCESSOR_EXPRESSION + ")*"; // In future this will also have constants like strings and ints
        private const string REGEX_BINARY_EXPRESSION = "(" + REGEX_OBJECT_EXPRESSION + ")(" + REGEX_OPERATOR + ")(" + REGEX_OBJECT_EXPRESSION + ")";
        private const string REGEX_COMPLEX_EXPRESSION = "((" + REGEX_OBJECT_EXPRESSION + ")|(" + REGEX_BINARY_EXPRESSION + "))";
        private const string REGEX_BINDING_EXPRESSION = @"\{(" + REGEX_COMPLEX_EXPRESSION + @")\}";

        private class ErrorListener : IAntlrErrorListener<IToken>
        {
            public void SyntaxError([NotNull] IRecognizer recognizer, [Nullable] IToken offendingSymbol, int line, int charPositionInLine, [NotNull] string msg, [Nullable] RecognitionException e)
            {
                System.Diagnostics.Debug.WriteLine(msg);
            }
        }

        public static JToken EvaluateBinding(string bindingExpression, JsonTransformerContext context)
        {
            string remainingBindingExpression = bindingExpression;
            string answer = "";
            bool first = true;
            bool found = false;
            while (true)
            {
                int startIndex = remainingBindingExpression.IndexOf('{');
                if (startIndex != -1)
                {
                    string substr = remainingBindingExpression.Substring(startIndex);
                    var inputStream = new AntlrInputStream(substr);
                    var lexer = new BindingExpressionsLexer(inputStream);
                    var tokenStream = new CommonTokenStream(lexer);
                    var parser = new BindingExpressionsParser(tokenStream);
                    parser.AddErrorListener(new ErrorListener());

                    var foundExpression = parser.bindingExpression();

                    // If it actually found something
                    if (foundExpression.Stop.StopIndex < substr.Length && parser.NumberOfSyntaxErrors == 0)
                    {
                        var visitor = new BindingExpressionsVisitor(context);
                        JToken result = visitor.Visit(foundExpression);

                        answer += remainingBindingExpression.Substring(0, startIndex);
                        answer += result;

                        remainingBindingExpression = substr;
                        remainingBindingExpression = remainingBindingExpression.Substring(foundExpression.Stop.StopIndex + 1);

                        // If whole expression was the binding expression, don't do any string concatenation
                        if (first && startIndex == 0 && remainingBindingExpression.Length == 0)
                        {
                            return result;
                        }

                        found = true;
                    }

                    else
                    {
                        // Otherwise, increment past there and try again
                        answer += remainingBindingExpression.Substring(startIndex + 1);
                        remainingBindingExpression = remainingBindingExpression.Substring(startIndex + 1);
                    }
                }
                else
                {
                    answer += remainingBindingExpression;
                    break;
                }

                first = false;
            }

            if (found)
            {
                return answer;
            }

            return bindingExpression;

            //var inputStream = new AntlrInputStream(bindingExpression);
            //var lexer = new BindingExpressionsLexer(inputStream);
            //var tokenStream = new CommonTokenStream(lexer);
            //var parser = new BindingExpressionsParser(tokenStream);

            //var foundExpression = parser.input_string();
            //if (foundExpression.IsEmpty)
            //{
            //    //return bindingExpression;
            //}
            //var visitor = new BindingExpressionsVisitor(context);
            //JToken result = visitor.Visit(foundExpression);
            //return result;
            

                // If it's all one single expression, we don't do any string concatenation and we return the actual type
                var match = Regex.Match(bindingExpression, "^" + REGEX_BINDING_EXPRESSION + "$");
            if (match.Success && match.Groups[1].Success)
            {
                return EvaluateComplexExpression(match.Groups[1].Value, context);
            }

            Regex regex = new Regex(REGEX_BINDING_EXPRESSION);
            var evaluator = new MyMatchEvaluator(context);

            string replaced = regex.Replace(bindingExpression, evaluator.ReplaceBinding);

            return replaced;
        }

        /// <summary>
        /// A complex expression, like "person.name", "person['details'].name", "name == 'Andrew'", or even nested complex expressions
        /// </summary>
        /// <param name="complexExpression"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public static JToken EvaluateComplexExpression(string complexExpression, JsonTransformerContext context)
        {
            var complexMatch = Regex.Match(complexExpression, "^" + REGEX_COMPLEX_EXPRESSION + "$");
            if (complexMatch.Success)
            {

            }

            Match firstPropertyMatch = Regex.Match(complexExpression, "^" + REGEX_PROPERTY_NAME);
            if (firstPropertyMatch.Success)
            {
                string remainingToParse = complexExpression;
                JToken data;
                if (firstPropertyMatch.Value.StartsWith("$"))
                {
                    data = context.ReservedProperties.GetValue(firstPropertyMatch.Value.Substring(1));
                    if (data == null)
                    {
                        return null;
                    }

                    remainingToParse = remainingToParse.Substring(firstPropertyMatch.Length);
                }
                else
                {
                    remainingToParse = "." + remainingToParse;
                    data = context.ReservedProperties.Data;
                }

                if (remainingToParse.Length > 0)
                {
                    data = EvaluateAccessorExpression(remainingToParse, data, context);
                }

                string remainingExpression = complexExpression.Substring(firstPropertyMatch.Value.Length);

                // See if there's a binary operator following this object
                var regexOperator = new Regex("^" + REGEX_OPERATOR);
                var matchOperator = regexOperator.Match(remainingExpression);
                if (matchOperator.Success && matchOperator.Groups[1].Success)
                {
                    string operatorStr = matchOperator.Groups[1].Value;

                    // Get the second object of the binary operation
                    // Note this is slightly incorrect, since it'll join chained operations from the end to the front. For example,
                    // true == 'Andrew' == 'Andrew' would evaluate to true, as (true == ('Andrew' == 'Andrew')), but it should be the other way around
                    // Plus I'm temporarily hacking this by appending { at the start, need to split this out into different methods better
                    JToken secondObject = EvaluateComplexExpression("{" + remainingExpression.Substring(matchOperator.Value.Length), context);

                    switch (operatorStr)
                    {
                        case "==":
                            return object.Equals(data, secondObject);
                    }
                }

                return data;
            }

            return null;
        }

        /// <summary>
        /// Evaluates a simple object expression, like "reportsTo.name" or "people[0].name" or even "'Andrew'" or "4"
        /// </summary>
        /// <param name="objectExpression"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        private static JToken EvaluateObjectExpression(string objectExpression, JsonTransformerContext context)
        {
            Match firstPropertyMatch = Regex.Match(objectExpression, "^" + REGEX_PROPERTY_NAME);
            if (firstPropertyMatch.Success)
            {
                string remainingToParse = objectExpression;
                JToken data;
                if (firstPropertyMatch.Value.StartsWith("$"))
                {
                    data = context.ReservedProperties.GetValue(firstPropertyMatch.Value.Substring(1));
                    if (data == null)
                    {
                        return null;
                    }

                    remainingToParse = remainingToParse.Substring(firstPropertyMatch.Length);
                }
                else
                {
                    remainingToParse = "." + remainingToParse;
                    data = context.ReservedProperties.Data;
                }

                if (remainingToParse.Length > 0)
                {
                    data = EvaluateAccessorExpression(remainingToParse, data, context);
                }

                return data;
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
                return EvaluateComplexExpression(m.Value, _context)?.ToString();
            }
        }

        /// <summary>
        /// Evaluates full property accessor expressions, like ".person.name" or ".person['First Name']", etc
        /// </summary>
        /// <param name="data"></param>
        /// <param name="propertyExpression"></param>
        /// <returns></returns>
        public static JToken EvaluateAccessorExpression(string propertyExpression, JToken currData, JsonTransformerContext context)
        {
            if (currData == null)
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
                nextData = GetProperty(currData, property);
                matchedText = matchPropertyAccessor.Value;
            }
            else
            {
                regex = new Regex("^" + REGEX_DICTIONARY_LOOKUP);
                var matchDictionary = regex.Match(propertyExpression);
                if (matchDictionary.Success && matchDictionary.Groups[1].Success)
                {
                    string dictionaryAccessor = matchDictionary.Groups[1].Value;
                    nextData = GetProperty(currData, dictionaryAccessor);
                    matchedText = matchDictionary.Value;
                }
                else
                {
                    regex = new Regex("^" + REGEX_INDEX_ACCESSOR);
                    var matchIndex = regex.Match(propertyExpression);
                    if (matchIndex.Success && matchIndex.Groups[1].Success && int.TryParse(matchIndex.Groups[1].Value, out int indexToAccess))
                    {
                        nextData = currData.ElementAtOrDefault(indexToAccess);
                        matchedText = matchIndex.Value;
                    }
                }
            }

            if (nextData != null)
            {
                if (matchedText.Length < propertyExpression.Length)
                {
                    return EvaluateAccessorExpression(propertyExpression.Substring(matchedText.Length), nextData, context);
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
