using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardServer
{
    public class LiveCard : ILiveCard
    {
        private AdaptiveCard card;
        private WebSocket webSocket;
        private JsonRpc rpc;

        public LiveCard(AdaptiveCard card, WebSocket webSocket)
        {
            this.card = card;
            this.Server = new LiveCardServerAPI(card);
            this.rpc = new JsonRpc(new WebSocketMessageHandler(webSocket), this.Server);
            this.Client = new LiveCardClientAPI(rpc);
        }

        /// <summary>
        /// Class which exposes Client methods to server
        /// </summary>
        public ILiveCardClientAPI Client { get; set; }

        /// <summary>
        /// Class which exposes Server methods to client
        /// </summary>
        public ILiveCardServerAPI Server { get; set; }

        /// <summary>
        /// Card which is being worked on
        /// </summary>
        public AdaptiveCard Card
        {
            get { return this.card; }
            set { this.card = value; }
        }

        public Task StartListening()
        {
            rpc.StartListening();
            return Task.CompletedTask;
        }

        public Task ListeningTask {  get { return this.rpc.ListeningTask; } }

        public Task CloseCard()
        {
            this.Client.CloseCard();
            return Task.CompletedTask;
        }

        //public async Task InsertElement(InsertPosition position, string id, AdaptiveElement element)
        //{
        //    new SetEventsVisitor().Visit(null, element);
        //    await this.Card.InsertElement(position, id, element);
        //}

        //public async Task RemoveElement(string id)
        //{
        //    await this.Card.RemoveElement(id);
        //    await this.Client.OnRemoveElement(id);
        //}

        //public async Task ReplaceElement(AdaptiveElement element)
        //{
        //    new SetEventsVisitor().Visit(null, element);

        //    await this.Card.ReplaceElement(element);
        //    await this.Client.OnReplaceElement(element);
        //}

        //public async Task SaveCard(AdaptiveCard card = null)
        //{
        //    new SetEventsVisitor().VisitCard(card);
        //    await this.Client.SaveCard(card);
        //}

        //public async Task SetProperties(string id, IEnumerable<SetProperty> properties)
        //{
        //    await this.Card.SetProperties(id, properties);
        //    await this.Client.OnSetProperties(id, properties);
        //}
    }


}