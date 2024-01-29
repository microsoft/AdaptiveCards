// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// AdaptiveCards template windows runtime component library
namespace AdaptiveCards.Template
{
    /// <summary>
    /// AdaptiveCards template windows runtime component library
    /// </summary>
    public sealed class AdaptiveCardTemplate
    {
        /// <summary>
        /// Given a JSON template, create a AdaptiveCardTemplate object that can be used to expand the template
        /// </summary>
        /// <param name="jsonTemplate"></param>
        public AdaptiveCardTemplate(String jsonTemplate)
        {
            adaptiveCardTemplate = new AdaptiveCards.Templating.AdaptiveCardTemplate(jsonTemplate);
        }

        /// <summary>
        /// Expands the template with the given data
        /// </summary>
        /// <param name="rootData"></param>
        /// <returns></returns>
        public string Expand(String rootData)
        {
            return adaptiveCardTemplate.Expand(rootData);
        }

        private AdaptiveCards.Templating.AdaptiveCardTemplate adaptiveCardTemplate;

    }
}
