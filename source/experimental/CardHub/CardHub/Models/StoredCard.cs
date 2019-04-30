using CardHub.Interfaces;
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

        public StoredCard(CardData cardData)
        {
            CardData = cardData;
            _serverSentEvent = new ServerSentEvent(2);
        }

        public CardData CardData { get; private set; }

        public DateTime LastUpdated { get; private set; } = DateTime.Now;

        public void Update(CardData cardData)
        {
            CardData = cardData;
            LastUpdated = DateTime.Now;
            _serverSentEvent.Send(JsonConvert.ToString(cardData));
        }

        public HttpResponseMessage AddSubscriber(HttpRequestMessage request)
        {
            return _serverSentEvent.AddSubscriber(request);
        }
    }
}
