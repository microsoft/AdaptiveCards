using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class JSONTemplateVisitor : JSONBaseVisitor<string>
    {

        public override string VisitTemplateData([NotNull] JSONParser.TemplateDataContext context)
        {
            string json = Visit(context.children[0]) + Visit(context.children[1]);
            string childJson = Visit(context.children[2]);
            JObject o = JObject.Parse(childJson);
            string name = o["employee"]["name"].ToString();
            return json;
        }

        public override string VisitJsonPair([NotNull] JSONParser.JsonPairContext context)
        {
            string json = "";
            foreach (var child in context.children)
            {
                json += Visit(child);
            }
            return json;
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

        public override string VisitChildren(IRuleNode node)
        {
            return base.VisitChildren(node);
        }

        public override string VisitObj([NotNull] JSONParser.ObjContext context)
        {
            string json = "";
            foreach (var child in context.children)
            {
                json += Visit(child);
            }
            return json;
        }

        public override string VisitValue([NotNull] JSONParser.ValueContext context)
        {
            return base.VisitValue(context);
        }

        public override string VisitTerminal(ITerminalNode node)
        {
            return node.GetText();
        }
    }
}
