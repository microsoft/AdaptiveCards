using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards.Templating
{
    public class AdaptiveCardsTemplate
    {
        private IParseTree parseTree;

        public AdaptiveCardsTemplate(object jsonTemplate)
        {
            if (jsonTemplate != null)
            {
                string jsonTemplateString = "";
                jsonTemplateString = (jsonTemplate is string) ? jsonTemplate as string : JsonConvert.SerializeObject(jsonTemplate);
                AntlrInputStream stream = new AntlrInputStream(jsonTemplateString);
                ITokenSource lexer = new AdaptiveCardsTemplateLexer(stream);
                ITokenStream tokens = new CommonTokenStream(lexer);
                AdaptiveCardsTemplateParser parser = new AdaptiveCardsTemplateParser(tokens)
                {
                    BuildParseTree = true
                };

                parseTree = parser.json();
            }
        }

        public string Expand(AdaptiveCardEvaluationContext context)
        {
            string jsonData = "";

            if (context != null && context.Root != null)
            {
                if (context.Root is string)
                {
                    jsonData = context.Root as string;
                }
                else
                {
                    jsonData = JsonConvert.SerializeObject(context.Root);
                }
            }

            AdaptiveCardsTemplateVisitor eval = new AdaptiveCardsTemplateVisitor(jsonData);
            return eval.Visit(parseTree).ToString();
        }
    }
}
