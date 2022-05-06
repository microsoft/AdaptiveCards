// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Newtonsoft.Json;
using System;
using System.Collections;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// The main <c>AdaptiveCardTemplate</c> class
    /// Contain all methods for performaing data binding to <c>AdaptiveCardTemplate</c>
    /// <list type="bullet">
    /// <item>
    /// <term>Expand</term>
    /// <description></description>
    /// </item>
    /// </list>
    /// </summary>
    public sealed class AdaptiveCardTemplate
    {
        private IParseTree parseTree;
        private string jsonTemplateString;

        /// <summary>
        /// <para>Creates an instance of AdaptiveCardTemplate</para>
        /// </summary>
        /// <remarks>
        /// <para>Once created, it will contain a parsed tree based on jsonTemplate</para>
        /// <para>Data is bound by calling <c>Expand</c> on the object</para>
        /// <para>The intance can be rebound with different data by calling <c>Expand</c></para>
        /// <see cref="Expand(EvaluationContext, Func{string, object})"/>
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
        /// var template = new AdaptiveCardTemplate(jsonTemplate);
        /// </code>
        /// </example>
        /// <param name="jsonTemplate">string in json or seriazable object</param>
        public AdaptiveCardTemplate(object jsonTemplate)
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
        /// Wrapper method to maintain functionality if caller decides not to use log files
        /// This method will call the base Expand(context, errorLog, nullSubstitutionOption)
        /// with errorLog as a discarded parameter
        /// </summary>
        /// <param name="context">provides data context</param>
        /// <param name="nullSubstitutionOption">defines behavior when no suitable data is found for a template entry</param>
        /// <returns>json as string</returns>
        public string Expand(EvaluationContext context, Func<string, object> nullSubstitutionOption = null)
        {
            // Use discarded out parameter since caller didn't use errorLog implementation
            return Expand(context, out _, nullSubstitutionOption);
        }

        /// <summary>
        /// Wrapper method to maintain functionality if caller decides not to use log files
        /// This method will call the base Expand(rootData, errorLog, nullSubstitutionOption)
        /// with errorLog as a discarded parameter
        /// </summary>
        /// <param name="rootData">Serializable object or a string in valid json format that will be used as data context</param>
        /// <param name="nullSubstitutionOption">Defines behavior when no suitable data is found for a template entry</param>
        /// <returns>json as string</returns>
        public string Expand(object rootData, Func<string, object> nullSubstitutionOption = null)
        {
            // Use discarded out parameter since caller didn't use errorLog implementation
            return Expand(rootData, out _, nullSubstitutionOption);
        }

        /// <summary>
        /// Bind data in <paramref name="context"/> to the instance of AdaptiveCardTemplate
        /// </summary>
        /// <remarks>
        /// <para> Data can be also inlined in AdaptiveCardTemplate payload</para>
        /// <para> Expand can be called multiple times with different or same <paramref name="context"/></para>
        /// <para> Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser</para>
        /// <para> <paramref name="nullSubstitutionOption"/> defines behavior when no suitable data is found for a template entry</para>
        /// <para> Default behavior is leaving templated string unchanged</para>
        /// <para> Method has been updated to include error logging. Use Expand(context, nullSubstitutionOption) if you don't want errorLogs.</para>
        /// </remarks>
        /// <param name="context">provides data context</param>
        /// <param name="errorLog">stores the outputed log statements from parsing the template</param>
        /// <param name="nullSubstitutionOption">defines behavior when no suitable data is found for a template entry</param>
        /// <example>
        /// <code>
        /// var template = new AdaptiveCardTemplate(jsonTemplate);
        /// var context = new AdaptiveCardsEvaluationContext(jsonData);
        /// template.Expand(context);
        /// </code>
        /// </example>
        /// <seealso cref="EvaluationContext"/>
        /// <returns>json as string</returns>
        public string Expand(EvaluationContext context, out ArrayList errorLog, Func<string, object> nullSubstitutionOption = null)
        {
        
            if (parseTree == null)
            {
                // Create empty array list so that `out` parameter has a value
                errorLog = new ArrayList();
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

            AdaptiveCardsTemplateResult result = eval.Visit(parseTree);

            errorLog = eval.getTemplateLog();

            return result.ToString();
        }

        /// <summary>
        /// Create a root data context using <paramref name="rootData"/>, and bind it to the instance of AdaptiveCardTemplate
        /// </summary>
        /// <remarks>
        /// <para> Data can be also inlined in AdaptiveCardTemplate payload</para>
        /// <para> Expand can be called multiple times with different or same <paramref name="rootData"/></para>
        /// <para> Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser</para>
        /// <para> <paramref name="nullSubstitutionOption"/> defines behavior when no suitable data is found for a template entry</para>
        /// <para> Default behavior is leaving templated string unchanged</para>
        /// <para> Method has been updated to include error logging. Use Expand(rootData, nullSubstitutionOption) if you don't want errorLogs.</para>
        /// </remarks>
        /// <param name="rootData">Serializable object or a string in valid json format that will be used as data context</param>
        /// <param name="errorLog">stores the outputed log statements from parsing the template</param>
        /// <param name="nullSubstitutionOption">Defines behavior when no suitable data is found for a template entry</param>
        /// <example>
        /// <code>
        /// var template = new AdaptiveCardTemplate(jsonTemplate);
        /// template.Expand(rootData);
        /// </code>
        /// </example>
        /// <seealso cref="EvaluationContext"/>
        /// <returns>json as string</returns>
        public string Expand(object rootData, out ArrayList errorLog, Func<string, object> nullSubstitutionOption = null)
        {
            var context = new EvaluationContext(rootData);
            return Expand(context, out errorLog, nullSubstitutionOption);
        }
    }
}
