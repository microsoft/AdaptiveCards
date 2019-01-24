using Antlr4.Runtime.Misc;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace JsonTransformLanguage.Grammars
{
    internal class BindingExpressionsVisitor : BindingExpressionsBaseVisitor<JToken>
    {
        JsonTransformerContext _transformerContext;

        public BindingExpressionsVisitor(JsonTransformerContext transformerContext)
        {
            _transformerContext = transformerContext;
        }

        public override JToken VisitBindingExpression([NotNull] BindingExpressionsParser.BindingExpressionContext context)
        {
            return Visit(context.expression());
        }

        public override JToken VisitString([NotNull] BindingExpressionsParser.StringContext context)
        {
            string stringConstant = context.string_literal().StringConstant().GetText();
            return stringConstant.Substring(1, stringConstant.Length - 2);
        }

        public override JToken VisitBoolean([NotNull] BindingExpressionsParser.BooleanContext context)
        {
            string txt = context.boolean_literal().GetText();
            return bool.Parse(txt);
        }

        public override JToken VisitInt([NotNull] BindingExpressionsParser.IntContext context)
        {
            string txt = context.DigitSequence().GetText();
            return int.Parse(txt);
        }

        public override JToken VisitDouble([NotNull] BindingExpressionsParser.DoubleContext context)
        {
            string txt = context.DoubleConstant().GetText();
            return double.Parse(txt);
        }

        public override JToken VisitNull([NotNull] BindingExpressionsParser.NullContext context)
        {
            return null;
        }

        public override JToken VisitEquality_expression([NotNull] BindingExpressionsParser.Equality_expressionContext context)
        {
            JToken leftValue = Visit(context.relational_expression()[0]);

            // If there's comparisons
            if (context.BinaryOperator().Length > 0)
            {
                var binaryOperators = context.BinaryOperator();
                var remainingRightValues = context.relational_expression().Skip(1).ToArray();

                for (int i = 0; i < binaryOperators.Length; i++)
                {
                    var op = binaryOperators[i].GetText();
                    var rightValExpression = remainingRightValues[i];

                    JToken rightValue = Visit(rightValExpression);
                    switch (op)
                    {
                        case "==":
                            leftValue = object.Equals(leftValue, rightValue);
                            break;

                        default:
                            leftValue = !object.Equals(leftValue, rightValue);
                            break;
                    }
                }
            }

            return leftValue;
        }

        public override JToken VisitIdentifier([NotNull] BindingExpressionsParser.IdentifierContext context)
        {
            string identifier = context.Identifier().GetText();
            if (identifier.StartsWith("$"))
            {
                return _transformerContext.ReservedProperties.GetValue(identifier.Substring(1));
            }
            else
            {
                return GetProperty(_transformerContext.ReservedProperties.Data, identifier);
            }
        }

        public override JToken VisitLiteral([NotNull] BindingExpressionsParser.LiteralContext context)
        {
            return base.VisitLiteral(context);
        }

        public override JToken VisitUnary_expression([NotNull] BindingExpressionsParser.Unary_expressionContext context)
        {
            if (context.primary_expression() != null)
            {
                return Visit(context.primary_expression());
            }
            return base.VisitUnary_expression(context);
        }

        public override JToken VisitPrimary_expression([NotNull] BindingExpressionsParser.Primary_expressionContext context)
        {
            JToken currValue = Visit(context.primary_expression_start());
            if (currValue == null)
            {
                return null;
            }

            foreach (var memberOrBracket in context.member_access_or_bracket_expression())
            {
                // Accessing member
                if (memberOrBracket.member_access() != null)
                {
                    string propertyName = memberOrBracket.member_access().identifier().Identifier().GetText();
                    if (propertyName == null)
                    {
                        return null;
                    }
                    currValue = GetProperty(currValue, propertyName);
                }

                // Accessing dictionary/indexer
                else if (memberOrBracket.bracket_expression() != null)
                {
                    JToken accessorValue = Visit(memberOrBracket.bracket_expression().indexer_argument());
                    if (accessorValue == null)
                    {
                        return null;
                    }
                    switch (accessorValue.Type)
                    {
                        case JTokenType.String:
                            currValue = GetProperty(currValue, accessorValue.Value<string>());
                            break;

                        case JTokenType.Integer:
                            if (currValue is JArray array)
                            {
                                currValue = array.ElementAtOrDefault(accessorValue.Value<int>());
                            }
                            else
                            {
                                return null;
                            }
                            break;

                        default:
                            return null;
                    }
                }

                else
                {
                    throw new NotImplementedException();
                }

                if (currValue == null)
                {
                    return null;
                }
            }

            return currValue;
        }

        public override JToken VisitAdditive_expression([NotNull] BindingExpressionsParser.Additive_expressionContext context)
        {
            JToken leftValue = Visit(context.multiplicative_expression()[0]);

            // If there's operations
            if (context.AdditiveOperator().Length > 0)
            {
                var additiveOperators = context.AdditiveOperator();
                var remainingRightValues = context.multiplicative_expression().Skip(1).ToArray();

                for (int i = 0; i < additiveOperators.Length; i++)
                {
                    var op = additiveOperators[i].GetText();
                    var rightValExpression = remainingRightValues[i];

                    JToken rightValue = Visit(rightValExpression);

                    // If neither are numbers, invalid
                    if (!IsNumber(leftValue) || !IsNumber(rightValue))
                    {
                        return null;
                    }

                    // If final type should be float
                    if (leftValue.Type == JTokenType.Float || rightValue.Type == JTokenType.Float)
                    {
                        double leftValueDouble = leftValue.Value<double>();
                        double rightValueDouble = rightValue.Value<double>();


                        switch (op)
                        {
                            case "+":
                                leftValue = leftValueDouble + rightValueDouble;
                                break;

                            case "-":
                                leftValue = leftValueDouble - rightValueDouble;
                                break;

                            default:
                                throw new NotImplementedException();
                        }
                    }
                    else
                    {
                        int leftValueInt = leftValue.Value<int>();
                        int rightValueInt = rightValue.Value<int>();


                        switch (op)
                        {
                            case "+":
                                leftValue = leftValueInt + rightValueInt;
                                break;

                            case "-":
                                leftValue = leftValueInt - rightValueInt;
                                break;

                            default:
                                throw new NotImplementedException();
                        }
                    }
                }
            }

            return leftValue;
        }

        public override JToken VisitMultiplicative_expression([NotNull] BindingExpressionsParser.Multiplicative_expressionContext context)
        {
            JToken leftValue = Visit(context.unary_expression()[0]);

            // If there's operations
            if (context.MultiplicativeOperator().Length > 0)
            {
                var multiplicativeOperators = context.MultiplicativeOperator();
                var remainingRightValues = context.unary_expression().Skip(1).ToArray();

                for (int i = 0; i < multiplicativeOperators.Length; i++)
                {
                    var op = multiplicativeOperators[i].GetText();
                    var rightValExpression = remainingRightValues[i];

                    JToken rightValue = Visit(rightValExpression);

                    // If neither are numbers, invalid
                    if (!IsNumber(leftValue) || !IsNumber(rightValue))
                    {
                        return null;
                    }

                    // If final type should be float
                    if (leftValue.Type == JTokenType.Float || rightValue.Type == JTokenType.Float)
                    {
                        double leftValueDouble = leftValue.Value<double>();
                        double rightValueDouble = rightValue.Value<double>();


                        switch (op)
                        {
                            case "*":
                                leftValue = leftValueDouble * rightValueDouble;
                                break;

                            case "/":
                                leftValue = leftValueDouble / rightValueDouble;
                                break;

                            case "%":
                                leftValue = leftValueDouble % rightValueDouble;
                                break;

                            default:
                                throw new NotImplementedException();
                        }
                    }
                    else
                    {
                        int leftValueInt = leftValue.Value<int>();
                        int rightValueInt = rightValue.Value<int>();


                        switch (op)
                        {
                            case "*":
                                leftValue = leftValueInt * rightValueInt;
                                break;

                            case "/":
                                leftValue = leftValueInt / rightValueInt;
                                break;

                            case "%":
                                leftValue = leftValueInt % rightValueInt;
                                break;

                            default:
                                throw new NotImplementedException();
                        }
                    }
                }
            }

            return leftValue;
        }

        private static bool IsNumber(JToken token)
        {
            if (token == null)
            {
                return false;
            }

            return token.Type == JTokenType.Integer || token.Type == JTokenType.Float;
        }

        //public override JToken VisitPostfixExpression([NotNull] BindingExpressionsParser.PostfixExpressionContext context)
        //{
        //    if (!context.primaryExpression().IsEmpty)
        //    {
        //        return base.VisitPostfixExpression(context);
        //    }
        //    else if (!context.postfixExpression().IsEmpty)
        //    {
        //        // The preceeding value, like "person" in examples below
        //        JToken precedingValue = Visit(context.postfixExpression());

        //        // Dictionary accessor person['name']
        //        if (!context.expression().IsEmpty)
        //        {
        //            JToken accessorValue = Visit(context.expression());
        //            if (accessorValue == null)
        //            {
        //                return null;
        //            }
        //            switch (accessorValue.Type)
        //            {
        //                case JTokenType.String:
        //                    return GetProperty(precedingValue, accessorValue.Value<string>());

        //                case JTokenType.Integer:
        //                    if (precedingValue is JArray array)
        //                    {
        //                        return array.ElementAtOrDefault(accessorValue.Value<int>());
        //                    }
        //                    return null;

        //                default:
        //                    return null;
        //            }
        //        }

        //        // Property accessor person.name
        //        else if (!context.identifier().IsEmpty)
        //        {
        //            string propertyName = context.identifier().Identifier().GetText();
        //            if (propertyName != null)
        //            {
        //                return GetProperty(precedingValue, propertyName);
        //            }
        //            else
        //            {
        //                return null;
        //            }
        //        }

        //        else
        //        {
        //            throw new NotImplementedException();
        //        }
        //    }
        //    else
        //    {
        //        throw new NotImplementedException();
        //    }
        //}

        //public override JToken VisitBindingExpression([NotNull] BindingExpressionsParser.BindingExpressionContext context)
        //{
        //    return Visit(context.complexExpression());
        //}

        //public override JToken VisitComplexExpression([NotNull] BindingExpressionsParser.ComplexExpressionContext context)
        //{
        //    string text = context.Identifier().GetText();
        //    return text;
        //}

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
