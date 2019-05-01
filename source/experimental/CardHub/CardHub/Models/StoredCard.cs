using CardHub.Interfaces;
using MiniGuids;
using Newtonsoft.Json;
using ServerSentEvent4Net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Web;

namespace CardHub.Models
{
    public class StoredCard
    {
        private ServerSentEvent _serverSentEvent;

        public StoredCard(string cardId, CardData cardData)
        {
            CardId = cardId;
            CardData = cardData;
            _serverSentEvent = new ServerSentEvent(2);
        }

        public string CardId { get; private set; }

        /// <summary>
        /// The unique token that only the host knows, so that only host can update
        /// </summary>
        public string Token { get; private set; } = MiniGuid.NewGuid() + MiniGuid.NewGuid() + MiniGuid.NewGuid() + MiniGuid.NewGuid() + MiniGuid.NewGuid() + MiniGuid.NewGuid();

        public CardData CardData { get; private set; }

        public DateTime LastUpdated { get; private set; } = DateTime.Now;

        public void Update(CardData cardData)
        {
            CardData = cardData;
            LastUpdated = DateTime.Now;
            _serverSentEvent.Send("updated");
        }

        public HttpResponseMessage AddSubscriber(HttpRequestMessage request)
        {
            return _serverSentEvent.AddSubscriber(request);
        }
    }
}
