// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards.Templating.Projection
{
    public sealed class Template
    {
        private AdaptiveCards.Templating.AdaptiveCardTemplate? cardTemplate;

        public Template() { }

        public Template(string templateJson)
        {
            cardTemplate = new AdaptiveCards.Templating.AdaptiveCardTemplate(templateJson);
        }

        public string Expand(string rootData)
        {
            return cardTemplate.Expand(new EvaluationContext { Root = rootData });
        }

        public string Expand(string rootData, string hostData)
        {
            return cardTemplate.Expand(new EvaluationContext { Root = rootData, Host = hostData });
        }

        static public string ExpandWithData(string json, string data)
        {
            var template = new Template(json);
            return template.Expand(json);
        }
    }
}
