using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardServer
{
    public class LiveCard : ILiveCardClientAPI
    {
        private AdaptiveCard card;

        public LiveCard(AdaptiveCard card, JsonRpc rpc)
        {
            this.card = card;
            this.Client = new LiveCardClientAPI(rpc);
            this.Server = new LiveCardServerAPI(card);
            rpc.AddLocalRpcTarget(this.Server);
        }

        /// <summary>
        /// Class which exposes sending changes to the client
        /// </summary>
        public ILiveCardClientAPI Client { get; set; }

        /// <summary>
        /// Class which handles client events -> code behind
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

        public Task CloseCard()
        {
            this.Client.CloseCard();
            return Task.CompletedTask;
        }

        public async Task OnInsertElement(string id, InsertPosition position, AdaptiveElement element)
        {
            await this.Card.InsertElement(id, position, element);
            await this.Client.OnInsertElement(id, position, element);
        }

        public async Task OnRemoveElement(string id)
        {
            await this.Card.RemoveElement(id);
            await this.Client.OnRemoveElement(id);
        }

        public async Task OnReplaceElement(AdaptiveElement element)
        {
            await this.Card.ReplaceElement(element);
            await this.Client.OnReplaceElement(element);
        }

        public async Task SaveCard(AdaptiveCard card = null)
        {
            await this.Client.SaveCard(card);
        }

        public async Task OnSetProperties(string id, IEnumerable<SetProperty> properties)
        {
            await this.Card.SetProperties(id, properties);
            await this.Client.OnSetProperties(id, properties);
        }
    }


}