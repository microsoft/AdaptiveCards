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

        // does this api handles the case where json template also has data in it?
        public string Transform(string jsonTemplate, string jsonData)
        {
            ICharStream stream = CharStreams.fromstring(jsonTemplate);
            ITokenSource lexer = new JSONLexer(stream);
            ITokenStream tokens = new CommonTokenStream(lexer);
            JSONParser parser = new JSONParser(tokens);
            parser.BuildParseTree = true;
            IParseTree tree = parser.json();
            JSONTemplateVisitor eval = new JSONTemplateVisitor();
            return eval.Visit(tree).ToString();
        }
    }
}
