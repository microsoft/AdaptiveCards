// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// AdaptiveCards template windows runtime component library
namespace AdaptiveCards.Templating.WinRT
{
    /// <summary>
    /// AdaptiveCards template windows runtime component library
    /// </summary>
    public sealed class AdaptiveCardTemplate
    {
        /// <summary>
        /// Given a JSON template, create a AdaptiveCardTemplate object that can be used to expand the template
        /// </summary>
        /// <param name="jsonTemplate">JSON serialized AdaptiveCard Template</param>
        public AdaptiveCardTemplate(String jsonTemplate)
        {
            adaptiveCardTemplate = new AdaptiveCards.Templating.AdaptiveCardTemplate(jsonTemplate);
        }

        /// <summary>
        /// Expands the template with the given data
        /// </summary>
        /// <param name="rootData">JSON serialized data for AdaptiveCard template</param>
        /// <returns></returns>
        public string Expand(String rootData)
        {
            return adaptiveCardTemplate.Expand(rootData);
        }

        /// <summary>
        /// Expand the template with root data and host data
        /// </summary>
        /// <param name="rootData">JSON serialized data for AdaptiveCard template</param>
        /// <param name="hostData">JSON serialized host config</param>
        /// <returns></returns>
        public string Expand(String rootData, String hostData)
        {
            AdaptiveCards.Templating.EvaluationContext evaluationContext = new(rootData, hostData);
            return adaptiveCardTemplate.Expand(evaluationContext);
        }

        private readonly AdaptiveCards.Templating.AdaptiveCardTemplate adaptiveCardTemplate;
    }
}
