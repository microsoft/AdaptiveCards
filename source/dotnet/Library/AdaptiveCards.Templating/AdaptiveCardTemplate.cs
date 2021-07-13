// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveExpressions.Properties;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Linq;

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
        /// <param name="jsonTemplate">json string or seriazable object</param>
        public AdaptiveCardTemplate(object jsonTemplate)
        {
            if (jsonTemplate is string str)
            {
                Template = (JObject)JsonConvert.DeserializeObject(str);
            }
            else
            {
                Template = JObject.FromObject(jsonTemplate);
            }
        }

        /// <summary>
        /// Gets the Parsed Template.
        /// </summary>
        public JObject Template { get; private set; }

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
        public string Expand(EvaluationContext context, Func<string, object> nullSubstitutionOption = null)
        {
            var result = (JObject)this.Template.DeepClone();
            context = context ?? new EvaluationContext();
            if (nullSubstitutionOption != null)
            {
                context.NullSubstitution = nullSubstitutionOption;
            }
            context.Data = context.Root;
            BindToken(result, context);
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
        public string Expand(object rootData, Func<string, object> nullSubstitutionOption = null)
        {
            var context = new EvaluationContext(rootData)
            {
                NullSubstitution = nullSubstitutionOption
            };

            var result = (JObject)this.Template.DeepClone();
            BindToken(result, context);
            return result.ToString();
        }

        private void BindToken(JToken token, EvaluationContext context)
        {
            switch (token)
            {
                case JObject job:
                    BindObject(job, context);
                    break;

                case JArray arr:
                    BindArray(arr, context);
                    break;

                case JProperty property:
                    BindProperty(property, context);
                    break;

                case JValue value:
                    if (token.Type == JTokenType.String)
                    {
                        // if it is a run through expression parser and treat as a value
                        var (result, error) = new ValueExpression(token).TryGetValue(context);
                        token.Replace(JToken.FromObject(result));
                    }
                    break;
            }
        }

        private static string FixBoolean(string arg)
        {
            if (arg.StartsWith("${", StringComparison.Ordinal) && arg.EndsWith("}", StringComparison.Ordinal))
            {
                return arg.Substring(2, arg.Length - 3);
            }
            return arg;
        }

        private void BindObject(JObject job, EvaluationContext context)
        {
            var dataProperty = job.Property("$data");
            if (dataProperty != null)
            {
                var dataExpression = new ValueExpression(dataProperty.Value);
                var newData = dataExpression.GetValue(context);
                context = context.Clone(newData);
                job.Remove("$data");
            }

            JArray dataArray = context.Data as JArray;
            bool objIsTemplate = dataProperty != null && dataArray != null;
            if (objIsTemplate)
            {
                for (context.Index = 0; context.Index < dataArray.Count; context.Index++)
                {
                    context.Data = dataArray[context.Index];
                    var template = (JObject)job.DeepClone();
                    template.Remove("$data");

                    var whenProperty = template.Property("$when");
                    if (whenProperty != null)
                    {
                        var whenExpression = new BoolExpression(FixBoolean((String)whenProperty.Value));
                        var (value, error) = whenExpression.TryGetValue(context);
                        if (value == false)
                        {
                            //skip item
                            continue;
                        }
                        whenProperty.Remove();
                    }

                    BindObject(template, context);
                    job.AddBeforeSelf(template);
                }
                job.Remove();
            }
            else
            {
                var whenProperty = job.Property("$when");
                if (whenProperty != null)
                {
                    var whenExpression = new BoolExpression(FixBoolean((String)whenProperty.Value));
                    var (value, error) = whenExpression.TryGetValue(context);
                    if (value == false)
                    {
                        job.Remove();
                        return;
                    }
                    whenProperty.Remove();
                }

                foreach (var child in job.Properties())
                {
                    BindToken(child.Value, context);
                }
            }
        }

        private void BindArray(JArray arr, EvaluationContext context)
        {

            foreach (var item in arr.ToList())
            {
                BindToken(item, context);
            }
        }

        private void BindProperty(JProperty prop, EvaluationContext context)
        {
            BindToken(prop.Value, context);
        }
    }
}
