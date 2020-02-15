using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using Microsoft.Bot.Expressions;
using System.Text;

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
            string childJson = templateDataValueNode.GetText();
            PushDataContext(childJson);
            return null;
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
            for(var i = 0; i < context.ChildCount; i++)
            {
                var child = context.children[i];
                // if it's data context, skip nex terminal token
                if (child is JSONParser.TemplateDataContext)
                {
                    i++;
                }
                else
                {
                    result.Append(Visit(child));
                }
            }

            // if the current data context is array type, repeat
            if (isArrayType && !result.IsExpanded)
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
                        result.Append(oldResult.Expand(this, token as JObject));
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

        public override JSONTemplateVisitorResult VisitValueTemplateString([NotNull] JSONParser.ValueTemplateStringContext context)
        {
           
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
