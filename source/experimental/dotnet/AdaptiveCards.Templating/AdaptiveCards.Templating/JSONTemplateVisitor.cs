using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitor : JSONParserBaseVisitor<string>
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

        public override string VisitTemplateData([NotNull] JSONParser.TemplateDataContext context)
        {
            // when this node is visited, the children of this node is shown as below: 
            // this node is visited only when parsing was correctly done
            // [ '{', '$data', ':', ',', 'val'] 
            IParseTree templateDataValueNode = context.GetChild(4);
            string childJson = templateDataValueNode.GetText();
            PushDataContext(childJson);
            return null;
        }

        public override string VisitJsonPair([NotNull] JSONParser.JsonPairContext context)
        {
            StringBuilder sb = new StringBuilder();
            foreach (var child in context.children)
            {
                 var returnedJson = Visit(child);
                sb.Append(returnedJson);
            }
            return sb.ToString();
        }

        public override string VisitArray([NotNull] JSONParser.ArrayContext context)
        {
            string json = "";
            foreach (var child in context.children)
            {
                json += Visit(child);
            }
            return json;
        }

        public override string VisitObj([NotNull] JSONParser.ObjContext context)
        {
            StringBuilder sb = new StringBuilder();
            var HasDataContext = false;

            // vist the first data context availble, the rest ignored
            // data context node is the first node that has to be acquired amongst the children
            for (var i = 0; i < context.ChildCount; i++)
            { 
                var child = context.children[i];
                if (child is JSONParser.TemplateDataContext)
                {
                    Visit(child);
                    HasDataContext = true;
                    break;
                }
            }

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
                    var parsedJson = Visit(child);
                    sb.Append(parsedJson);
                }
            }

            // restore data context
            if (HasDataContext)
            {
                PopDataContext();
            }
            return sb.ToString();
        }

        public override string VisitTerminal(ITerminalNode node)
        {
            var tokenType = node.Symbol.Type;
            if (node.Symbol.Type == JSONLexer.TEMPLATELITERAL)
            {
                // This is the code where we replace it with CEL
                ICharStream stream = CharStreams.fromstring(node.GetText());
                AdaptiveCardsTemplatingLexer lexer = new AdaptiveCardsTemplatingLexer(stream);
                ITokenStream tokens = new CommonTokenStream(lexer);
                AdaptiveCardsTemplatingParser parser = new AdaptiveCardsTemplatingParser(tokens)
                {
                    BuildParseTree = true
                };
                IParseTree tree = parser.template();
                AdaptiveCardsTemplatingTreeVisitor eval = new AdaptiveCardsTemplatingTreeVisitor();
                var processed = eval.Visit(tree);

                // nice place to add error handling
                if (HasDataContext() && processed != null && processed.Keys.Count > 0)
                {
                    // need a error handling when user put template with no matching data
                    // continuing as need to finish skelectal codes
                    DataContext currentDataContext = GetCurrentDataContext();
                    if (currentDataContext.IsArrayType)
                    {
                    }
                    else
                    {
                        JObject data = GetCurrentDataContext().templateData;
                        var obj = data[processed.Keys[0]];
                        for (var idx = 1; idx < processed.Keys.Count; idx++)
                        {
                            var val = processed.Keys[idx];
                            if (int.TryParse(val, out int arrayIdx))
                            {
                                obj = obj[arrayIdx];
                            }
                            else
                            {
                                obj = obj[val];
                            }
                        }
                        return obj.ToString();
                    }
                }
            }

            if (tokenType == JSONLexer.TemplateOpen || tokenType == JSONLexer.TEMPLATECLOSE)
            {
                return "";
            }

            return node.GetText();
        }

        public override string VisitValueTemplateString([NotNull] JSONParser.ValueTemplateStringContext context)
        {
            StringBuilder sb = new StringBuilder("\"");
            sb.Append(Visit(context.children[1])).Append("\"");
            return sb.ToString(); 
        }

        public override string VisitValueString([NotNull] JSONParser.ValueStringContext context)
        {
            return context.GetText(); 
        }

        public override string VisitTemplateString([NotNull] JSONParser.TemplateStringContext context)
        {
            StringBuilder sb = new StringBuilder();
            foreach (var child in context.children)
            {
                sb.Append(Visit(child));
            }
            return sb.ToString(); 
        }
    }
}
