using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class AdaptiveTransformer
    {
        public AdaptiveTransformer()
        {
        }

        public string Transform(string jsonTemplate, string jsonData)
        {
            ICharStream stream = CharStreams.fromstring(jsonTemplate);
            ITokenSource lexer = new AdaptiveCardsTemplatingLexer(stream);
            ITokenStream tokens = new CommonTokenStream(lexer);
            AdaptiveCardsTemplatingParser parser = new AdaptiveCardsTemplatingParser(tokens);
            parser.BuildParseTree = true;
            return "Work In Progress";
        }
    }
}
