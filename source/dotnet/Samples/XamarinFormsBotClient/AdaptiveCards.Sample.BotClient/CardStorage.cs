using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Reflection;
using System.Text;
using AdaptiveCards.Rendering;
using Xamarin.Forms;

namespace AdaptiveCards.Sample.BotClient
{
    public class CardStorage
    {
        protected List<AdaptiveCard> AdaptiveCards = new List<AdaptiveCard>();

        public AdaptiveHostConfig HostConfig { get; protected set; } = new AdaptiveHostConfig();
        public AdaptiveCard Get(int i)  
        {
            int adaptiveCardsCount = AdaptiveCards.Count;
            if (adaptiveCardsCount == 0)
            {
                return null;
            }
            return AdaptiveCards[i % adaptiveCardsCount];
        }

        public void ReadAdaptiveCards(string[] fileNames)
        {
            ICardsReader cardsReader = DependencyService.Get<ICardsReader>();
            string[] cardJsons = cardsReader.ReadAdaptiveCardsJsons(fileNames);

            foreach (var cardJson in cardJsons)
            {
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(cardJson);
                AdaptiveCards.Add(parseResult.Card);
            }
        }

        public void ReadHostConfig(string filename = null)
        {
            ICardsReader cardsReader = DependencyService.Get<ICardsReader>();

            var hostConfigJson = cardsReader.ReadHostConfigJson(filename);

            if (!string.IsNullOrWhiteSpace(hostConfigJson))
            {
                this.HostConfig = AdaptiveHostConfig.FromJson(hostConfigJson);
            }
        }

    }
}
