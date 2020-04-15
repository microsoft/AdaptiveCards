using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System;
using AdaptiveExpressions.Properties;
using AdaptiveExpressions;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class AdaptiveCardsTemplateVisitor : AdaptiveCardsTemplateParserBaseVisitor<AdaptiveCardsTemplateResult>
    {
        class DataContext
        {
            public JToken token;
            public bool IsArrayType = false;

            public JToken RootDataContext;
            public const string rootKeyword = "$root";
            public const string dataKeyword = "$data";
            public const string indexKeyword = "$index";

            public DataContext (string text, JToken rootDataContext) : this(JToken.Parse(text), rootDataContext)
            {
            }
            public DataContext (JToken jtoken, JToken rootDataContext)
            {
                token = jtoken;
                RootDataContext = rootDataContext;

                if (jtoken is JArray)
                {
                    IsArrayType = true;
                }
                else
                {
                    AddDataContext(dataKeyword, token, token.DeepClone());
                    AddDataContext(rootKeyword, token, RootDataContext);
                }
            }

            public static void AddDataContext(string key, JToken targetJObj, JToken jtoken)
            {
                if (jtoken == null)
                {
                    return;
                }

                targetJObj[key] = jtoken; 
            }
            public JObject GetDataAtIndex(int index)
            {
                if (IsArrayType)
                {
                    var jarray = token as JArray; 
                    JObject jobject = jarray[index] as JObject;
                    AddDataContext(dataKeyword, jobject, jobject.DeepClone());
                    AddDataContext(rootKeyword, jobject, RootDataContext);
                    jobject[indexKeyword] = index;
                    return jobject;
                }
                return null;
            }
        }

        private Stack<DataContext> _dataContext = new Stack<DataContext>();
        private readonly JToken root;

        private DataContext GetCurrentDataContext()
        { 
            return _dataContext.Count == 0 ? null : _dataContext.Peek();
        }

        private void PushDataContext(string stringToParse, JToken rootDataContext)
        {
            _dataContext.Push(new DataContext(stringToParse, rootDataContext));
        }

        private void PushTemplatedDataContext(string jpath)
        {
            DataContext parentDataContext = GetCurrentDataContext();
            if (jpath == null || parentDataContext == null)
            {
                return;
            }

            try
            {
                var (value, error) = new ValueExpression(jpath).TryGetValue(parentDataContext.token);
                if (error == null)
                {
                    _dataContext.Push(new DataContext(value as string, parentDataContext.RootDataContext));
                }
            }
            catch (Exception)
            {
                // we swallow up the error here
            }
        }

        private void PopDataContext()
        {
            _dataContext.Pop();
        }

        private bool HasDataContext()
        {
            return _dataContext.Count != 0;
        }

        public AdaptiveCardsTemplateVisitor(string data = null)
        {
            if(data != null && data.Length != 0)
            {
                root = JToken.Parse(data);
                PushDataContext(data, root);
            }
        }

        public override  AdaptiveCardsTemplateResult VisitTemplateData([NotNull] AdaptiveCardsTemplateParser.TemplateDataContext context)
        {
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // [ '{', '$data', ':', ',', 'val'] 
            IParseTree templateDataValueNode = context.value();
            if (templateDataValueNode is AdaptiveCardsTemplateParser.ValueObjectContext || templateDataValueNode is AdaptiveCardsTemplateParser.ValueArrayContext)
            {
                string childJson = templateDataValueNode.GetText();
                PushDataContext(childJson, root);
            }
            else if (templateDataValueNode is AdaptiveCardsTemplateParser.ValueTemplateStringWithRootContext)
            {
                Visit(templateDataValueNode);
            }
            else if (templateDataValueNode is AdaptiveCardsTemplateParser.ValueTemplateStringContext)
            {
                var templateString = (templateDataValueNode as AdaptiveCardsTemplateParser.ValueTemplateStringContext).templateString(0);
                var templateLiteral = (templateString as AdaptiveCardsTemplateParser.TemplatedStringContext).TEMPLATELITERAL();
                PushTemplatedDataContext(templateLiteral.GetText());
            }

            return null;
        }

        public override AdaptiveCardsTemplateResult VisitTemplateStringWithRoot([NotNull] AdaptiveCardsTemplateParser.TemplateStringWithRootContext context)
        {
            return Visit(context.TEMPLATEROOT());
        }

        public override AdaptiveCardsTemplateResult VisitTemplateRootData([NotNull] AdaptiveCardsTemplateParser.TemplateRootDataContext context)
        {
            var child = context.templateRoot();
            PushTemplatedDataContext(child.GetText());
            return null;
        }


        public override AdaptiveCardsTemplateResult VisitValueTemplateExpression([NotNull] AdaptiveCardsTemplateParser.ValueTemplateExpressionContext context)
        {                 
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // ['"', 'templated expression'] 
            AdaptiveCardsTemplateResult result = new AdaptiveCardsTemplateResult(context.GetText(), context.TEMPLATELITERAL().GetText());

            DataContext dataContext = GetCurrentDataContext();

            if (dataContext.IsArrayType)
            {
                return result;
            }

            if (dataContext != null && !dataContext.IsArrayType)
            {
                result.WhenEvaluationResult = IsTrue(result.Predicate, dataContext.token) ?
                    AdaptiveCardsTemplateResult.EvaluationResult.EvaluatedToTrue :
                    AdaptiveCardsTemplateResult.EvaluationResult.EvaluatedToFalse;
            }
            return result;
        }
        public override AdaptiveCardsTemplateResult VisitValueTemplateString([NotNull] AdaptiveCardsTemplateParser.ValueTemplateStringContext context)
        {
            AdaptiveCardsTemplateResult result = new AdaptiveCardsTemplateResult();
            var templateStringContexts = context.templateString();
            if (templateStringContexts.Length == 1)
            {
                var templatedStringContext = templateStringContexts.GetValue(0) as AdaptiveCardsTemplateParser.TemplatedStringContext;
                // strictly, this check is not needed since the only children the context can have is this type
                if (templatedStringContext != null)
                {
                    ITerminalNode[] stringChildren = templatedStringContext.STRING();
                    // if ther are no string tokens, we do not quates
                    if (stringChildren.Length == 0)
                    {
                        result.Append(ExpandTemplatedString(templatedStringContext.TEMPLATELITERAL(), true));
                        return result;
                    }
                }
            }

            result.Append("\"");

            foreach (var templateStringContext in templateStringContexts) 
            {
                result.Append(Visit(templateStringContext));
            }

            result.Append("\"");

            return result;

        }

        public override AdaptiveCardsTemplateResult VisitObj([NotNull] AdaptiveCardsTemplateParser.ObjContext context)
        {
            var hasDataContext = false;
            var isArrayType = false;
            // vist the first data context availble, the rest ignored
            // data context node is the first node that has to be acquired amongst the children
            for (var i = 0; i < context.ChildCount; i++)
            { 
                var child = context.children[i];
                if (child is AdaptiveCardsTemplateParser.TemplateDataContext || child is AdaptiveCardsTemplateParser.TemplateRootDataContext)
                {
                    Visit(child);
                    hasDataContext = true;
                    isArrayType = GetCurrentDataContext().IsArrayType;
                    break;
                }
            }

            AdaptiveCardsTemplateResult result = new AdaptiveCardsTemplateResult();

            bool removeComma = false;
            // capture json string in object
            for(var i = 0; i < context.ChildCount; i++)
            {
                var child = context.children[i];
                // if it's data context, skip nex terminal token
                if (child is AdaptiveCardsTemplateParser.TemplateDataContext || child is AdaptiveCardsTemplateParser.TemplateRootDataContext)
                {
                    removeComma  = !result.TryRemoveACommaAtEnd ();
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
                                if (returnedResult.WhenEvaluationResult ==
                                    AdaptiveCardsTemplateResult.EvaluationResult.EvaluatedToFalse)
                                {
                                    return new AdaptiveCardsTemplateResult();
                                }
                                else
                                {
                                    removeComma = !result.TryRemoveACommaAtEnd();
                                    continue;
                                }
                            }
                            // if it's Array Type we defer the evaluation, so store predicate and return
                            else
                            {
                                removeComma = !result.TryRemoveACommaAtEnd();
                                result.Append(returnedResult);
                                continue;
                            }
                        }
                    }

                    result.Append(returnedResult);
                    // if removed pair was the first pair in the obj, comma is needed to be removed after it was added to the result
                    if (removeComma)
                    {
                        _ = result.TryRemoveACommaAtEnd();
                        removeComma = false;
                    }
                }
            }

            if (result.IsWhen)
            {
                if (result.WhenEvaluationResult == AdaptiveCardsTemplateResult.EvaluationResult.EvaluatedToTrue)
                {
                    result.RemoveWhen();
                }
            }

            // if the current data context is array type, repeat
            // template accessing array can expand only at the node
            // that contains the data context the template is acessing.
            if (isArrayType && hasDataContext && !result.IsExpanded)
            {
                var dataContext = GetCurrentDataContext();
                var jarray = dataContext.token as JArray;
                var repeatsCounts = jarray.Count;
                AdaptiveCardsTemplateResult oldResult = result;
                result = new AdaptiveCardsTemplateResult();
                for (int i = 0; i < repeatsCounts; i++)
                {
                    JObject jobject = dataContext.GetDataAtIndex(i);
                    if (jobject != null)
                    {
                        var expaded = oldResult.Expand(this, jobject);
                        result.Append(expaded);
                        if (i != repeatsCounts - 1)
                        {
                            if (oldResult.IsWhen)
                            {
                                if (expaded.Length != 0)
                                {
                                    result.Append(",");
                                }
                            }
                            else
                            {
                                result.Append(",");
                            }

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

        public override AdaptiveCardsTemplateResult VisitTerminal(ITerminalNode node)
        {
            if (node.Symbol.Type == AdaptiveCardsTemplateLexer.TEMPLATELITERAL || node.Symbol.Type == AdaptiveCardsTemplateLexer.TEMPLATEROOT)
            {
                return ExpandTemplatedString(node);
            }

            return new AdaptiveCardsTemplateResult(node.GetText());
        }

        public AdaptiveCardsTemplateResult ExpandTemplatedString(ITerminalNode node, bool isTemplatedString = false)
        {
            if (HasDataContext())
            {
                DataContext currentDataContext = GetCurrentDataContext();
                string templateString = node.GetText();
                if (currentDataContext.IsArrayType)
                {
                    return new AdaptiveCardsTemplateResult(templateString, false, isTemplatedString);
                }
                else
                {
                    return new AdaptiveCardsTemplateResult(Expand(templateString, currentDataContext.token, isTemplatedString));
                }
            }

            return new AdaptiveCardsTemplateResult(node.GetText());
        }

        public string Expand(string unboundString, JToken data, bool isTemplatedString = false)
        {
            Expression exp;
            try
            {
                exp = Expression.Parse(unboundString.Substring(2, unboundString.Length - 3));
            }
            catch (Exception)
            {
                return unboundString;
            }

            var options = new Options
            {
                NullSubstitution = (path) => $"${{{path}}}" 
            };

            StringBuilder result = new StringBuilder();
            try
            {
                var aelEvalResult = exp.TryEvaluate(data, options);
                if (aelEvalResult.error == null)
                {
                    if (aelEvalResult.value is string && isTemplatedString)
                    {
                        result.Append("\"");
                    }

                    result.Append(aelEvalResult.value.ToString());

                    if (aelEvalResult.value is string && isTemplatedString)
                    {
                        result.Append("\"");
                    }
                }
            }
            catch (Exception)
            {
                result.Append("${" + unboundString + "}");
            }

            return result.ToString();
        }

        /// <summary>
        /// return the parsed result of $when from pair context
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public override AdaptiveCardsTemplateResult VisitTemplateWhen([NotNull] AdaptiveCardsTemplateParser.TemplateWhenContext context)
        {
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // [ '{', '$when', ':', ',', 'expression'] 
            var result = Visit(context.templateExpression());
            result.IsPair = true;
            return result;
        }

        public bool IsTrue(string predicate, JToken data)
        {
            try
            {
                var (value, error) = new ValueExpression(predicate).TryGetValue(data);
                if (error == null)
                {
                    return bool.Parse(value as string);
                }
                return true;
            }
            catch
            {
                // TODO log erros here
                return true;
            }
        }    

        public override AdaptiveCardsTemplateResult VisitChildren([NotNull] IRuleNode node)
        {
            AdaptiveCardsTemplateResult result = new AdaptiveCardsTemplateResult();

            for(int i = 0; i < node.ChildCount; i++)
            {
                result.Append(Visit(node.GetChild(i)));
            }

            return result;
        }
    }
}
