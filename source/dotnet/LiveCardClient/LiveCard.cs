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
using System.Threading;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardClient
{

    public class LiveCard 
    {
        private AdaptiveCard card;
        private Uri uri;
        private ClientWebSocket socket;
        private StreamingWebSocketHandler handler;

        public LiveCard(Uri uri)
        {
            this.uri = uri;
        }

        public async Task LoadCard(string json = null)
        {
            HttpClient client = new HttpClient();
            if (json == null)
                json = await client.GetStringAsync(uri);
            this.card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
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

        public bool IsConnected
        {
            get { return (this.handler != null && this.socket.State == WebSocketState.Open); }
        }

        /// <summary>
        /// Activate LiveCard
        /// </summary>
        /// <returns></returns>
        public virtual async Task Activate()
        {
            // connect to service via WebSocket
            this.socket = new ClientWebSocket();
            await this.socket.ConnectAsync(this.uri, CancellationToken.None);
            this.handler = new StreamingWebSocketHandler(this.socket);

            // hook up JSON-RPC to websocket streams 
            JsonRpc rpc = new JsonRpc(handler.SendStream, handler.ReceiveStream);

            // initialize livecard procies
            this.Client = new LiveCardClientAPI(this);
            this.Server = new LiveCardServerAPI(rpc);
            rpc.AddLocalRpcTarget(this);

            EventBinder.Bind(this.Server, this.card);

#pragma warning disable CS4014 // Because this call is not awaited, execution of the current method continues before the call is completed
            this.handler.StartAsync();
#pragma warning restore CS4014 // Because this call is not awaited, execution of the current method continues before the call is completed

            // tell server we activated the card
            await this.Server.OnActivate();
        }

        private async Task _closeSocket()
        {
            if (this.handler != null)
            {
                await this.handler.Stop();
                this.handler = null;
                await this.socket.CloseAsync(WebSocketCloseStatus.NormalClosure, "deactivated", CancellationToken.None);
                this.socket = null;
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

        public virtual Task OnElementChanged(AdaptiveElement element)
        {
            EventBinder.Bind(this.Server, element);
            return Task.CompletedTask;
        }

        public virtual Task OnCardChanged(AdaptiveCard card)
        {
            EventBinder.Bind(this.Server, card);
            return Task.CompletedTask;
        }

        public virtual Task SaveCard( AdaptiveCard card = null)
        {
            return Task.CompletedTask;
        }

        public async virtual Task CloseCard()
        {
            await _closeSocket();
        }
    }
}