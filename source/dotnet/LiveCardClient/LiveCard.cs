using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using Newtonsoft.Json;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Diagnostics;
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
    public class LiveCard : ObservableObject, ILiveCard
    {
        private AdaptiveCard card;
        private Uri uri;
        private ClientWebSocket webSocket;
        private JsonRpc rpc;
        private AdaptiveElementMemory serverEvents = new AdaptiveElementMemory();

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
            set { this.SetPropertyValue(ref card, value); }
        }

        public bool Active { get { return this.webSocket?.State == WebSocketState.Open; } }

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
                this.rpc.Disconnected += Rpc_Disconnected;
                FirePropertyChanged("Active");

                this.Server = new LiveCardServerAPI(rpc);

                // bind events for Client->server notifications
                BindEvents();
                this.rpc.StartListening();
            }
        }

        private void Rpc_Disconnected(object sender, JsonRpcDisconnectedEventArgs e)
        {
            FirePropertyChanged("Active");
        }

        public async Task LoadCard(string json = null)
        {
            HttpClient client = new HttpClient();
            if (json == null)
                json = await client.GetStringAsync(uri);
            var parseResult = AdaptiveCard.FromJson(json);
            this.Card = parseResult.Card;
        }

        /// <summary>
        /// Activate LiveCard
        /// </summary>
        /// <returns></returns>
        public virtual async Task Activate()
        {
            // tell server we activated the card
            await this.Server.FireActivate();
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
        public virtual async Task Deactivate()
        {
            // tell server we are deactivating
            await this.Server.FireDeactivate();
            await _closeSocket();
        }

        public virtual Task SaveCard(AdaptiveCard card = null)
        {
            return Task.CompletedTask;
        }

        public async virtual Task CloseCard()
        {
            await _closeSocket();
        }

        public void BindEvent(AdaptiveTypedElement element)
        {
            this.serverEvents.Reset(element);
            BindEvents();
        }

        public void BindEvents()
        {
            lock (this.Card)
            {
                // foreach unprocessed element
                foreach (var element in this.Card.GetAllElements().Where(item => this.serverEvents.UnProcessed(item)))
                {
                    Trace.TraceInformation($"[{element.Type}] {element.Id} Events={String.Join(",", element.Events)}");

                    // mark it as processed 
                    this.serverEvents.MarkProcessed(element);

                    if (element.Events != null)
                    {
                        foreach (var eventName in element.Events)
                        {
                            switch (eventName)
                            {
                                case "onClick":
                                    element.OnClick += async (sender, e) => await this.Server.FireClick(element.Id);
                                    break;
                                case "onMouseEnter":
                                    element.OnMouseEnter += async (sender, e) => await this.Server.FireMouseEnter(element.Id);
                                    break;
                                case "onMouseLeave":
                                    element.OnMouseLeave += async (sender, e) => await this.Server.FireMouseLeave(element.Id);
                                    break;
                                default:
                                    if (element is AdaptiveInput)
                                    {
                                        AdaptiveInput input = element as AdaptiveInput;
                                        switch (eventName)
                                        {
                                            case "onKey":
                                                input.OnKey += async (sender, e) => await this.Server.FireKey(element.Id, e.Key);
                                                break;
                                            case "onTextChanged":
                                                input.OnTextChanged += async (sender, e) => await this.Server.FireTextChanged(element.Id, e.Text);
                                                break;
                                            case "onSelectionChanged":
                                                input.OnSelectionChanged += async (sender, e) => await this.Server.FireSelectionChanged(element.Id, e.Selection);
                                                break;
                                            case "onFocus":
                                                input.OnFocus += async (sender, e) => await this.Server.FireFocus(element.Id);
                                                break;
                                            case "onBlur":
                                                input.OnBlur += async (sender, e) => await this.Server.FireBlur(element.Id);
                                                break;
                                            default:
                                                throw new ArgumentException($"{eventName} is not known");
                                        }
                                    }
                                    else
                                    {
                                        throw new ArgumentException($"{eventName} is not known");
                                    }
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
}