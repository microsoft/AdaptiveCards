using CardHub.Interfaces;
using MiniGuids;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Web;

namespace CardHub.Models
{
    public class StoredCards
    {
        public static readonly StoredCards Current = new StoredCards();

        private Dictionary<string, StoredCard> _cards = new Dictionary<string, StoredCard>();

        public string Create(CardData cardData)
        {
            // First we'll clean up old cards
            CleanupOldCards();

            int attempts = 0;
            while (true)
            {
                string id = MiniGuid.NewGuid();
                id = id.Substring(0, attempts > 20 ? 12 : 6);

                lock (_cards)
                {
                    if (!_cards.ContainsKey(id))
                    {
                        _cards[id] = new StoredCard(cardData);
                        return id;
                    }
                }

                attempts++;

                if (attempts > 50)
                {
                    throw new Exception("Couldn't generate a unique ID");
                }
            }
        }

        private void CleanupOldCards()
        {
            lock (_cards)
            {
                var storedCards = _cards.OrderBy(i => i.Value.LastUpdated).ToList();

                var now = DateTime.Now;
                foreach (var stored in storedCards.ToArray())
                {
                    if (stored.Value.LastUpdated.AddHours(3) < now)
                    {
                        // If hasn't been updated for 3 hours, delete it
                        _cards.Remove(stored.Key);
                        storedCards.Remove(stored);
                    }
                }

                // If there's still more than 30 cards
                if (storedCards.Count > 30)
                {
                    // Only store at most 30
                    // The first ones are the oldest (already sorted earlier), so delete those
                    while (storedCards.Count > 30)
                    {
                        _cards.Remove(storedCards.First().Key);
                        storedCards.RemoveAt(0);
                    }
                }
            }
        }

        public void Update(string id, CardData cardData)
        {
            lock (_cards)
            {
                if (_cards.TryGetValue(id, out StoredCard storedCard))
                {
                    storedCard.Update(cardData);
                }
                else
                {
                    throw new KeyNotFoundException("Card ID couldn't be found. Maybe the subscription has expired?");
                }
            }
        }

        public bool TryGet(string id, out CardData cardData)
        {
            lock (_cards)
            {
                if (_cards.TryGetValue(id, out StoredCard value))
                {
                    cardData = value.CardData;
                    return true;
                }
            }

            cardData = null;
            return false;
        }

        public HttpResponseMessage AddSubscriber(string id, HttpRequestMessage request)
        {
            lock (_cards)
            {
                if (_cards.TryGetValue(id, out StoredCard value))
                {
                    return value.AddSubscriber(request);
                }
            }

            throw new KeyNotFoundException("Card ID couldn't be found. Maybe the subscription has expired?");
        }
    }
}
