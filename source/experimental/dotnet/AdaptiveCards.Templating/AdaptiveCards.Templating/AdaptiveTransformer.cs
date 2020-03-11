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
            AntlrInputStream stream = new AntlrInputStream(jsonTemplate);
            ITokenSource lexer = new JSONLexer(stream);
            ITokenStream tokens = new CommonTokenStream(lexer);
            JSONParser parser = new JSONParser(tokens)
            {
                BuildParseTree = true
            };
            IParseTree tree = parser.json();
            JSONTemplateVisitor eval = new JSONTemplateVisitor(jsonData);
            return eval.Visit(tree).ToString();
        }
    }
}
