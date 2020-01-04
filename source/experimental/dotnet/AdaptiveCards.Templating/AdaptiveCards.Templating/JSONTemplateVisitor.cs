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
    public class JSONTemplateVisitor : JSONBaseVisitor<string>
    {
        public JObject data = null;

        public JSONTemplateVisitor(JObject data = null)
        {
            this.data = data;
        }

        public override string VisitTemplateData([NotNull] JSONParser.TemplateDataContext context)
        {
            string childJson = Visit(context.children[2]);
            data = JObject.Parse(childJson);
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
            return node.GetText();
        }

        public string BoundString(Match match)
        {
            ICharStream stream = CharStreams.fromstring(match.Value);
            AdaptiveCardsTemplatingLexer lexer = new AdaptiveCardsTemplatingLexer(stream);
            ITokenStream tokens = new CommonTokenStream(lexer);
            AdaptiveCardsTemplatingParser parser = new AdaptiveCardsTemplatingParser(tokens);
            parser.BuildParseTree = true;
            IParseTree tree = parser.template();
            AdaptiveCardsTemplatingTreeVisitor eval = new AdaptiveCardsTemplatingTreeVisitor();
            var processed = eval.Visit(tree);

            // nice place to add error handling
            if (this.data != null && processed != null && processed.Keys.Count > 0)
            {
                // need a error handling when user put template with no matching data
                // continuing as need to finish skelectal codes
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

            return match.Value; 
        }
        public override string VisitValueString([NotNull] JSONParser.ValueStringContext context)
        {
            string pattern = @"{[\w\n\.\[\]]+}";
            Regex rgx = new Regex(pattern);
            string text = context.GetText();
            MatchEvaluator evaluator = new MatchEvaluator(BoundString);
            var matches = Regex.Matches(text, pattern);
            return Regex.Replace(text, pattern, evaluator);
        }
    }
}
