using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using Newtonsoft.Json;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardClient
{

    /// <summary>
    /// LiveCard for clients, exposes clientAPI to remote server 
    /// </summary>
    public class LiveCard : ILiveCard
    {
        private AdaptiveCard card;
        private Uri uri;
        private ClientWebSocket webSocket;
        private JsonRpc rpc;

        public LiveCard(Uri uri)
        {
            this.uri = uri;
        }
        
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

        public async Task StartListening()
        {
            if (this.rpc == null)
            {
                var wsUri = new Uri(this.uri.ToString().Replace("http:", "ws:").Replace("https:", "wss:"));

                // connect to service via WebSocket
                this.webSocket = new ClientWebSocket();
                this.webSocket.Options.AddSubProtocol("json-rpc");

                await this.webSocket.ConnectAsync(wsUri, CancellationToken.None);

                // hook up JSON-RPC to websocket streams 
                this.Client = new LiveCardClientAPI(this);
                this.rpc = new JsonRpc(new WebSocketMessageHandler(this.webSocket), this.Client);
                this.rpc.JsonSerializer.Converters.Add(new AdaptiveCardConverter());
                this.rpc.JsonSerializer.Converters.Add(new AdaptiveTypedElementConverter());
                this.rpc.JsonSerializer.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveAction>());
                this.rpc.JsonSerializer.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveElement>());

                this.Server = new LiveCardServerAPI(rpc);

                EventBinder.Bind(this.Server, this.card);
                this.rpc.StartListening();
            }
        }

        public event EventHandler<CardChangedArgs> OnCardChanged;
        public event EventHandler<ElementChangedArgs> OnElementChanged;
 
        public async Task LoadCard(string json = null)
        {
            HttpClient client = new HttpClient();
            if (json == null)
                json = await client.GetStringAsync(uri);
            var parseResult = AdaptiveCard.FromJson(json);
            this.card = parseResult.Card;
        }

        /// <summary>
        /// Activate LiveCard
        /// </summary>
        /// <returns></returns>
        public virtual async Task Activate()
        {
            // tell server we activated the card
            await this.Server.OnActivate();
        }

        private async Task _closeSocket()
        {
            if (this.webSocket != null)
            {
                await this.webSocket.CloseAsync(WebSocketCloseStatus.NormalClosure, "deactivated", CancellationToken.None);
                this.webSocket = null;
            }
        }

        /// <summary>
        /// Deactive live card
        /// </summary>
        /// <returns></returns>
        public virtual async Task DeActivate()
        {
            // tell server we are deactivating
            await this.Server.OnDeactivate();
            await _closeSocket();
        }

        public virtual Task FireElementChanged(AdaptiveElement element)
        {
            EventBinder.Bind(this.Server, element);
            this.OnElementChanged(element, new ElementChangedArgs() { Element = element });
            return Task.CompletedTask;
        }

        public virtual Task FireCardChanged(AdaptiveCard card)
        {
            EventBinder.Bind(this.Server, card);
            this.OnCardChanged(card, new CardChangedArgs() { Card = card });
            return Task.CompletedTask;
        }

        public virtual Task SaveCard(AdaptiveCard card = null)
        {
            return Task.CompletedTask;
        }

        public async virtual Task CloseCard()
        {
            await _closeSocket();
        }

    }
}