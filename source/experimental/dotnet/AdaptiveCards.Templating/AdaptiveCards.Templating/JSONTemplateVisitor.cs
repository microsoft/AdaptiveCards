using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using Microsoft.Bot.Expressions;
using System;
using System.Runtime.InteropServices;
using System.Xml.Serialization;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitor : JSONParserBaseVisitor<JSONTemplateVisitorResult>
    {
        public class DataContext
        {
            public JObject templateData;
            public JArray templateDataArray;
            public bool IsArrayType = false;

            public DataContext (string text)
            {
                JToken token = JToken.Parse(text);
                if (token is JArray)
                {
                    templateDataArray = JArray.Parse(text);
                    IsArrayType = true;
                }
                else
                {
                    templateData = JObject.Parse(text);
                }
            }
            public DataContext (JToken jtoken)
            {
                if (jtoken is JArray)
                {
                    templateDataArray = jtoken as JArray;
                    IsArrayType = true;
                }
                else
                {
                    templateData = jtoken as JObject;
                }
            }
        }

        private Stack<DataContext> _dataContext = new Stack<DataContext>();
        private ExpressionEngine _expressionEngine = new ExpressionEngine();

        private DataContext GetCurrentDataContext()
        { 
            return _dataContext.Count == 0 ? null : _dataContext.Peek();
        }

        private void PushDataContext(string stringToParse)
        {
            _dataContext.Push(new DataContext(stringToParse));
        }

        private void PushDataContext(string jpath, DataContext parentDataContext)
        {
            if (jpath == null || parentDataContext == null)
            {
                return;
            }

            JToken jtoken;
            if (parentDataContext.IsArrayType)
            {
                jtoken = parentDataContext.templateDataArray.SelectToken(jpath);
            }
            else
            {
                jtoken = parentDataContext.templateData.SelectToken("LineItems");
            }

            if (jtoken == null)
            {
                return;
            }
            _dataContext.Push(new DataContext(jtoken));
        }

        private void PopDataContext()
        {
            _dataContext.Pop();
        }

        private bool HasDataContext()
        {
            return _dataContext.Count != 0;
        }

        public JSONTemplateVisitor(string data = null)
        {
            if(data != null)
            {
                PushDataContext(data);
            }
        }

        public override  JSONTemplateVisitorResult VisitTemplateData([NotNull] JSONParser.TemplateDataContext context)
        {
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // [ '{', '$data', ':', ',', 'val'] 
            IParseTree templateDataValueNode = context.GetChild(4);
            if (templateDataValueNode is JSONParser.ValueObjectContext || templateDataValueNode is JSONParser.ValueArrayContext)
            {
                string childJson = templateDataValueNode.GetText();
                PushDataContext(childJson);
            }
            else if (templateDataValueNode is JSONParser.ValueTemplateStringContext)
            {
                var datacontext = GetCurrentDataContext();
                for(int i = 0; i < templateDataValueNode.ChildCount; i++)
                {
                    var child = templateDataValueNode.GetChild(i);
                    if (child is JSONParser.TemplateStringContext)
                    {
                        // template string context is { val }
                        PushDataContext(child.GetChild(1).GetText(), datacontext);
                        break;
                    }
                }
            }
            else
            {

            }

            return null;
        }

        /// <summary>
        /// return the parsed result of $when from pair context
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public override JSONTemplateVisitorResult VisitTemplateWhen([NotNull] JSONParser.TemplateWhenContext context)
        {
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // [ '{', '$when', ':', ',', 'expression'] 
            var result = Visit(context.GetChild(4));
            result.IsPair = true;
            return result;
        }
        public override JSONTemplateVisitorResult VisitValueTemplateExpression([NotNull] JSONParser.ValueTemplateExpressionContext context)
        {
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult(context.GetText());
            result.IsWhen = true;
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // ['"', '{', 'expression'] 
            result.Predicate = context.GetChild(2).GetText();
            DataContext dataContext = GetCurrentDataContext();
            if (dataContext != null && !dataContext.IsArrayType)
            {
                result.EvaluationResult = IsTrue(result.Predicate, dataContext.templateData);
            }
            return result;
        }

        public override JSONTemplateVisitorResult VisitTemplateExpression([NotNull] JSONParser.TemplateExpressionContext context)
        {
            return base.VisitTemplateExpression(context);
        }

        public override JSONTemplateVisitorResult VisitJsonPair([NotNull] JSONParser.JsonPairContext context)
        {
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult();
            foreach (var child in context.children)
            {
                result.Append(Visit(child));
            }
            return result; 
        }

        public override JSONTemplateVisitorResult VisitArray([NotNull] JSONParser.ArrayContext context)
        {
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult();

            foreach (var child in context.children)
            {
                result.Append(Visit(child));
            }

            return result;
        }

        public override JSONTemplateVisitorResult VisitObj([NotNull] JSONParser.ObjContext context)
        {
            var hasDataContext = false;
            var isArrayType = false;
            // vist the first data context availble, the rest ignored
            // data context node is the first node that has to be acquired amongst the children
            for (var i = 0; i < context.ChildCount; i++)
            { 
                var child = context.children[i];
                if (child is JSONParser.TemplateDataContext)
                {
                    Visit(child);
                    hasDataContext = true;
                    isArrayType = GetCurrentDataContext().IsArrayType;
                    break;
                }
            }

            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult();

            // capture json string in object
            bool removeComma = false;
            for(var i = 0; i < context.ChildCount; i++)
            {
                var child = context.children[i];
                // if it's data context, skip nex terminal token
                if (child is JSONParser.TemplateDataContext)
                {
                    removeComma = true;
                }
                else if (removeComma)
                {
                    // a, b, c {a} {a, b} {b, a} { a } {b, a, c}
                    removeComma = false;
                    continue;
                }
                else
                {
                    var returnedResult = Visit(child);
                    // handling of $when starts here
                    if (returnedResult.IsWhen)
                    {
                        // This Obj we are translating get this $when attirbute
                        if (returnedResult.IsPair)
                        {
                            if (!GetCurrentDataContext().IsArrayType)
                            {
                                // if evaluation fails, we drops from current context
                                if (!returnedResult.EvaluationResult)
                                {
                                    return new JSONTemplateVisitorResult();
                                }
                                else
                                {
                                    removeComma = true;
                                    continue;
                                }
                            }
                            // if it's Array Type we defer the evaluation, so store predicate and return
                            else
                            {
                                result.IsWhen = true;
                                result.IsPair = false;
                                result.Predicate = returnedResult.Predicate;
                                removeComma = true;
                                // we don't keep what's returned from $when pair
                                continue;
                            }
                        }
                        // this means that an object with when has been returned
                        // we add this object to our when list
                        else
                        {
                            result.Whens.Add(returnedResult);
                        }
                    }

                    result.Append(returnedResult);
                }
            }

            // if the current data context is array type, repeat
            // template accessing array can expand only at the node
            // that contains the data context the template is acessing.
            if (isArrayType && hasDataContext && !result.IsExpanded)
            {
                var dataContext = GetCurrentDataContext();
                var repeatsCounts = dataContext.templateDataArray.Count;
                JSONTemplateVisitorResult oldResult = result;
                result = new JSONTemplateVisitorResult();
                for (int i = 0; i < repeatsCounts; i++)
                {
                    JToken token = dataContext.templateDataArray[i];
                    if (token is JObject)
                    {
                        JObject jobject = token as JObject;
                        jobject["$index"] = i;
                        result.Append(oldResult.Expand(this, jobject));
                        if (i != repeatsCounts - 1)
                        {
                            result.Append(",");
                        }
                    }
                    // produce warning if it's not JObject type
                }
            }

            // restore data context
            if (hasDataContext)
            {
                PopDataContext();
            }

            return result; 
        }

        public override JSONTemplateVisitorResult VisitTerminal(ITerminalNode node)
        {
            var tokenType = node.Symbol.Type;
            if (node.Symbol.Type == JSONLexer.TEMPLATELITERAL)
            {
                // nice place to add error handling
                if (HasDataContext())
                {
                    // need a error handling when user put template with no matching data
                    // continuing as need to finish skelectal codes
                    DataContext currentDataContext = GetCurrentDataContext();
                    string templateString = node.GetText();
                    if (currentDataContext.IsArrayType)
                    {
                        return new JSONTemplateVisitorResult(templateString, false);
                    }
                    else
                    {
                        JObject data = GetCurrentDataContext().templateData;
                        return new JSONTemplateVisitorResult(Expand(templateString, data));
                    }
                }
            }

            if (tokenType == JSONLexer.TemplateOpen || tokenType == JSONLexer.TEMPLATECLOSE)
            {
                return new JSONTemplateVisitorResult("");
            }

            return new JSONTemplateVisitorResult(node.GetText());
        }

        public string Expand(string unboundString, JObject data)
        {
            var result = _expressionEngine.Parse(unboundString).TryEvaluate(data);
            return result.value.ToString();
        }

        public bool IsTrue(string predicate, JObject data)
        {
            var result = _expressionEngine.Parse(predicate).TryEvaluate(data);
            return (bool)result.value;
        }    

        public override JSONTemplateVisitorResult VisitValueTemplateString([NotNull] JSONParser.ValueTemplateStringContext context)
        {
            // I just need to evaluation result and return
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult("\"");
            result.Append(Visit(context.children[1]));
            result.Append("\"");
            return result; 
        }

        public override JSONTemplateVisitorResult VisitValueString([NotNull] JSONParser.ValueStringContext context)
        {
            return new JSONTemplateVisitorResult(context.GetText()); 
        }

        public override JSONTemplateVisitorResult VisitTemplateString([NotNull] JSONParser.TemplateStringContext context)
        {
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult();
            foreach (var child in context.children)
            {
                result.Append(Visit(child));
            }
            return result; 
        }
    }
}
