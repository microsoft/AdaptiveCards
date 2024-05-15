// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using System;
using System.Collections;
using System.Diagnostics.CodeAnalysis;
using System.Text.Json;
using System.Text.Json.Nodes;

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
        private ArrayList templateExpansionWarnings;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="jsonTemplate"></param>
        [RequiresDynamicCode("For AOT compatibility, use the overload that takes a string and call JsonSerializer.Serialize on user-defined objects")]
        [RequiresUnreferencedCode("For AOT compatibility, use the overload that takes a string and call JsonSerializer.Serialize on user-defined objects")]
        public AdaptiveCardTemplate(object jsonTemplate)
            : this(ConvertToJson(jsonTemplate))
        {
        }

        [RequiresDynamicCode("Calls JsonSerializer.Serialize")]
        [RequiresUnreferencedCode("Calls JsonSerializer.Serialize")]
        internal static string ConvertToJson(object obj)
        {
            return (obj is string json) ? json : JsonSerializer.Serialize(obj);
        }

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
        public AdaptiveCardTemplate(string jsonTemplate)
        {
            if (jsonTemplate != null)
            {
                jsonTemplateString = jsonTemplate.ToString();

                AntlrInputStream stream = new AntlrInputStream(jsonTemplate);
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
        /// Bind data in <paramref name="context"/> to the instance of AdaptiveCardTemplate
        /// </summary>
        /// <remarks>
        /// <para> Data can be also inlined in AdaptiveCardTemplate payload</para>
        /// <para> Expand can be called multiple times with different or same <paramref name="context"/></para>
        /// <para> Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser</para>
        /// <para> <paramref name="nullSubstitutionOption"/> defines behavior when no suitable data is found for a template entry</para>
        /// <para> Default behavior is leaving templated string unchanged</para>
        /// </remarks>
        /// <param name="context">provides data context</param>
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
        [UnconditionalSuppressMessage("Trimming", "IL2026:Members annotated with 'RequiresUnreferencedCodeAttribute' require dynamic access otherwise can break functionality when trimming application code", Justification = "Calls to Serialize will only happen for non-AOT callers")]
        [UnconditionalSuppressMessage("AOT", "IL3050:Calling members annotated with 'RequiresDynamicCodeAttribute' may break functionality when AOT compiling.", Justification = "Calls to Serialize will only happen for non-AOT callers")]
        public string Expand(EvaluationContext context, Func<string, object> nullSubstitutionOption = null)
        {
            if (parseTree == null)
            {
                return jsonTemplateString;
            }

            string rootJsonData = "";
            if (context?.Root != null)
            {
                if (context.Root is string json)
                {
                    rootJsonData = json;
                }
                else
                {
                    rootJsonData = JsonSerializer.Serialize(context.Root);
                }
            }

            string hostJsonData = "";
            if (context?.Host != null)
            {
                if (context.Host is string json)
                {
                    hostJsonData = json;
                }
                else
                {
                    hostJsonData = JsonSerializer.Serialize(context.Host);
                }
            }

            AdaptiveCardsTemplateVisitor eval = new AdaptiveCardsTemplateVisitor(nullSubstitutionOption, rootJsonData, hostJsonData);
            AdaptiveCardsTemplateResult result = eval.Visit(parseTree);

            templateExpansionWarnings = eval.getTemplateVisitorWarnings();

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
        /// </remarks>
        /// <param name="rootData">Serializable object or a string in valid json format that will be used as data context</param>
        /// <param name="nullSubstitutionOption">Defines behavior when no suitable data is found for a template entry</param>
        /// <example>
        /// <code>
        /// var template = new AdaptiveCardTemplate(jsonTemplate);
        /// template.Expand(rootData);
        /// </code>
        /// </example>
        /// <seealso cref="EvaluationContext"/>
        /// <returns>json as string</returns>
        [RequiresUnreferencedCode("For AOT compatibility, use overloads of Expand that take EvaluationContext or string")]
        [RequiresDynamicCode("For AOT compatibility, use overloads of Expand that take EvaluationContext or string")]
        public string Expand(object rootData, Func<string, object> nullSubstitutionOption = null)
        {
            var context = new EvaluationContext(rootData);
            return Expand(context, nullSubstitutionOption);
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
        /// </remarks>
        /// <param name="rootData">Serializable object or a string in valid json format that will be used as data context</param>
        /// <param name="nullSubstitutionOption">Defines behavior when no suitable data is found for a template entry</param>
        /// <example>
        /// <code>
        /// var template = new AdaptiveCardTemplate(jsonTemplate);
        /// template.Expand(rootData);
        /// </code>
        /// </example>
        /// <seealso cref="EvaluationContext"/>
        /// <returns>json as string</returns>
        public string Expand(string rootData, Func<string, object> nullSubstitutionOption = null)
        {
            var context = new EvaluationContext(rootData);
            return Expand(context, nullSubstitutionOption);
        }

        /// <summary>
        /// Getter method for the array of warning strings from the last template expansion
        /// </summary>
        /// <returns>ArrayList</returns>
        public ArrayList GetLastTemplateExpansionWarnings()
        {
            if (templateExpansionWarnings != null)
            {
                return templateExpansionWarnings;
            }
            return new ArrayList();
        }
    }
}
