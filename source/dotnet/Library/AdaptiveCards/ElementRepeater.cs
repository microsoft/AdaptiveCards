using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ElementRepeater
    {
        private string _cardJson;
        public ElementRepeater(AdaptiveTypedElement sourceElement)
        {
            AdaptiveCard card = new AdaptiveCard("1.1");
            if (sourceElement is AdaptiveElement bodyElement)
            {
                card.Body.Add(bodyElement);
            }
            else if (sourceElement is AdaptiveAction action)
            {
                card.Actions.Add(action);
            }
            else
            {
                throw new Exception("Unknown type");
            }
            _cardJson = card.ToJson();
        }

        public AdaptiveTypedElement GetNewElement(JToken data)
        {
            AdaptiveCard card = AdaptiveCard.FromJson(_cardJson).Card;
            if (card.Body.Count > 0)
            {
                return card.Body[0];
            }
            if (card.Actions.Count > 0)
            {
                return card.Actions[0];
            }
            throw new Exception("Something failed");
        }
    }
}
