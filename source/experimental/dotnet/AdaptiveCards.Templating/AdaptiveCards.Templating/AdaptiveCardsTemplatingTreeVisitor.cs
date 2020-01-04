using System;
using System.Collections.Generic;
using System.Text;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;

namespace AdaptiveCards.Templating
{
    class AdaptiveCardsTemplatingTreeVisitor : AdaptiveCardsTemplatingBaseVisitor<AdaptiveCardsTemplatingVisitorResult>
    {
        public override AdaptiveCardsTemplatingVisitorResult VisitPropArray([NotNull] AdaptiveCardsTemplatingParser.PropArrayContext context)
        {
            var result = Visit(context.children[0]);
            result.Keys.Add(result.Tokens);
            result.Keys.Add(Visit(context.children[2]).Tokens);
            return result; 
        }

        public override AdaptiveCardsTemplatingVisitorResult VisitPropID([NotNull] AdaptiveCardsTemplatingParser.PropIDContext context)
        {
            var result = Visit(context.children[0]);
            result.Keys.Add(result.Tokens);
            return result;
        }

        public override AdaptiveCardsTemplatingVisitorResult VisitTemplate([NotNull] AdaptiveCardsTemplatingParser.TemplateContext context)
        {
            AdaptiveCardsTemplatingVisitorResult result = new AdaptiveCardsTemplatingVisitorResult();
            foreach (var child in context.children)
            {
                if (child is AdaptiveCardsTemplatingParser.PropContext)
                {
                    result.Keys.AddRange(Visit(child).Keys);
                }
            }

            if (result.Keys.Count > 0)
            {
                return result;
            }

            return base.VisitTemplate(context);
        }

        public override AdaptiveCardsTemplatingVisitorResult VisitTerminal(ITerminalNode node)
        {
            var result = new AdaptiveCardsTemplatingVisitorResult(node.GetText());
            return result; 
        }
    }
}
