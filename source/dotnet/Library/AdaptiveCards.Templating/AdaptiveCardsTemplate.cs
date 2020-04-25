// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json;
using System;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// The main <c>AdaptiveCardsTemplate</c> class
    /// Contain all methods for performaing data binding to <c>AdaptiveCardsTemplate</c>
    /// <list type="bullet">
    /// <item>
    /// <term>Expand</term>
    /// <description></description>
    /// </item>
    /// </list>
    /// </summary>
    public sealed class AdaptiveCardsTemplate
    {
        private IParseTree parseTree;
        private string jsonTemplateString;

        /// <summary>
        /// <para>Creates an instance of AdaptiveCardsTemplate</para>
        /// </summary>
        /// <remarks>
        /// <para>Once created, it will contain a parsed tree based on jsonTemplate</para>
        /// <para>Data is bound by calling <c>Expand</c> on the object</para>
        /// <para>The intance can be rebound with different data by calling <c>Expand</c></para>
        /// <see cref="Expand(AdaptiveCardsEvaluationContext, Func{string, object})"/>
        /// </remarks>
        /// <example>
        /// <code>
        /// var jsonTemplate = "
        /// {
        ///    "type": "AdaptiveCard",
        ///    "version": "1.0",
        ///    "body": [
        ///        {
        ///            "type": "TextBlock",
        ///            "text": "Hello ${person.firstName}"
        ///        }
        ///    ]
        ///}"
        /// var template = new AdaptiveCardsTemplate(jsonTemplate);
        /// </code>
        /// </example>
        /// <param name="jsonTemplate">string in json or seriazable object</param>
        public AdaptiveCardsTemplate(object jsonTemplate)
        {
            if (jsonTemplate != null)
            {
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

        /// <summary>
        /// Bind data in <paramref name="context"/> to the instance of AdaptiveCardsTemplate
        /// </summary>
        /// <remarks>
        /// <para> Data can be also inlined in AdaptiveCardsTemplate payload</para>
        /// <para> Expand can be called multiple times with different or same <paramref name="context"/></para>
        /// <para> Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser</para>
        /// <para> <paramref name="nullSubstitutionOption"/> defines behavior when no suitable data is found for a template entry</para>
        /// <para> Default behavior is leaving templated string unchanged</para>
        /// </remarks>
        /// <param name="context">provides data context</param>
        /// <param name="nullSubstitutionOption">defines behavior when no suitable data is found for a template entry</param>
        /// <example>
        /// <code>
        /// var template = new AdaptiveCardsTemplate(jsonTemplate);
        /// var context = new AdaptiveCardsEvaluationContext(jsonData);
        /// template.Expand(context);
        /// </code>
        /// </example>
        /// <seealso cref="AdaptiveCardsEvaluationContext"/>
        /// <returns>json as string</returns>
        public string Expand(AdaptiveCardsEvaluationContext context, Func<string, object> nullSubstitutionOption = null)
        {
            if (parseTree == null)
            {
                return jsonTemplateString;
            }

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

            AdaptiveCardsTemplateVisitor eval = new AdaptiveCardsTemplateVisitor(nullSubstitutionOption, jsonData);
            return eval.Visit(parseTree).ToString();
        }
    }
}
