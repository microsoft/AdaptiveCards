using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System.Text.RegularExpressions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitor : JSONParserBaseVisitor<string>
    {
        public ArrayList<JObject> data = new ArrayList<JObject>();

        public JSONTemplateVisitor(JObject data = null)
        {
            if(data != null)
            {
                this.data.Add(data);
            }
        }

        public override string VisitTemplateData([NotNull] JSONParser.TemplateDataContext context)
        {
            IParseTree templateDataValueNode = context.GetChild(4);
            if (templateDataValueNode is JSONParser.ValueArrayContext)
            {
                var arrayParseTree = templateDataValueNode.GetChild(0);
                for(var i = 0; i < arrayParseTree.ChildCount; i++)
                {
                    var child = arrayParseTree.GetChild(i);
                    if (child is JSONParser.ValueObjectContext)
                    {
                        var o = JObject.Parse(child.GetText());
                            data.Add(o);
                    }
                }
            }
            else
            {
                string childJson = templateDataValueNode.GetText();
                data.Add(JObject.Parse(childJson));
            }
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
            for(var i = 0; i < context.ChildCount; i++)
            {
                var child = context.children[i];
                var parsedJson = Visit(child);
                // if it's data context, skip nex terminal token
                if (child is JSONParser.TemplateDataContext)
                {
                    i++;
                }
                else
                {
                    sb.Append(parsedJson);
                }
            }
            return sb.ToString();
        }

        public override string VisitTerminal(ITerminalNode node)
        {
            var tokenType = node.Symbol.Type;
            if (node.Symbol.Type == JSONLexer.TEMPLATELITERAL)
            {
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
                if (this.data != null && processed != null && processed.Keys.Count > 0)
                {
                    // need a error handling when user put template with no matching data
                    // continuing as need to finish skelectal codes
                    var obj = data[0][processed.Keys[0]];
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
