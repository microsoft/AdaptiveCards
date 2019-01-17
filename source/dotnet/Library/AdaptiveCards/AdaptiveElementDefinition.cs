using JsonTransformLanguage;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveElementDefinition
    {
        public JObject Element { get; set; }

        public AdaptiveElement GetNewElement(JToken data)
        {
            if (Element == null)
            {
                return null;
            }

            var newElementToken = JsonTransformer.Transform(Element, data, null) as JObject;
            if (newElementToken == null)
            {
                return null;
            }

            AdaptiveCard card = new AdaptiveCard("1.1");
            card.Body.Add(new AdaptiveTextBlock()
            {
                Text = "replace me"
            });
            var cardObj = JObject.Parse(card.ToJson());
            cardObj["body"].First.Replace(newElementToken);

            try
            {
                // If this fails to parse, we run into concurrency issues since .NET wasn't built for parsing two cards at same time
                var result = AdaptiveCard.FromJson(cardObj.ToString());
                return result.Card.Body[0];
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex);
            }
            return null;
        }
    }
}
