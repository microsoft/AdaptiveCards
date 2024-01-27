// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// AdaptiveCards template windows runtime component library
namespace AdaptiveCards.Template
{
    public sealed class AdaptiveCardTemplate
    {
        public AdaptiveCardTemplate(String jsonTemplate)
        {
            adaptiveCardTemplate = new AdaptiveCards.Templating.AdaptiveCardTemplate(jsonTemplate);
        }

        public string Expand(String rootData)
        {
            return adaptiveCardTemplate.Expand(rootData);
        }

        private AdaptiveCards.Templating.AdaptiveCardTemplate adaptiveCardTemplate;

    }
}
