using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardClient
{

    public class LiveCard
    {
        private AdaptiveCard card;

        public LiveCard(AdaptiveCard card, JsonRpc rpc)
        {
            this.card = card;
            this.Client = new LiveCardClientAPI(card);
            this.Server = new LiveCardServerAPI(rpc);
            rpc.AddLocalRpcTarget(this.Client);
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
    }
}