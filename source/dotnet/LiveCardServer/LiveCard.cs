using AdaptiveCards;
using AdaptiveCards.Rendering;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
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
        private AdaptiveElementMemory domEvents = new AdaptiveElementMemory();

        public LiveCard(AdaptiveCard card, WebSocket webSocket)
        {
            this.card = card;
            BindDomChanges();

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

        public Task ListeningTask { get { return this.rpc.ListeningTask; } }

        public Task CloseCard()
        {
            this.Client.CloseCard();
            return Task.CompletedTask;
        }

        /// <summary>
        /// send property changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void Element_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            AdaptiveElement element = (AdaptiveElement)sender;
            var value = element.GetType().GetProperty(e.PropertyName).GetValue(element);
            await this.Client.SetProperty(element.Id, e.PropertyName, value);
        }

        /// <summary>
        /// send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void Items_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            // TODO optomize this
            var container = this.Card.GetAllElements()
                .Where(el => el is AdaptiveContainer)
                .Cast<AdaptiveContainer>()
                .Where(c => c.Items == sender)
                .FirstOrDefault();
            await processCollectionChanges(container.Id, e);
        }


        /// <summary>
        /// Send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void Body_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            // TODO this is not doing cards correctly, will only work for root card and needs to be mo better
            await processCollectionChanges(this.card.Id, e);
        }

        /// <summary>
        /// Send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void Columns_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            // TODO optomize this
            var columnSet = this.Card.GetAllElements()
                .Where(el => el is AdaptiveColumnSet)
                .Cast<AdaptiveColumnSet>()
                .Where(cs => cs.Columns == sender)
                .FirstOrDefault();
            if (columnSet != null)
                await processCollectionChanges(columnSet.Id, e);
        }

        private async Task processCollectionChanges(string containerId, NotifyCollectionChangedEventArgs e)
        {
            BindDomChanges();
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    await this.Client.AddElements(containerId, e.NewStartingIndex, e.NewItems.Cast<AdaptiveElement>().ToArray());
                    break;
                case NotifyCollectionChangedAction.Remove:
                    await this.Client.RemoveElements(containerId, e.OldItems.Cast<AdaptiveElement>().Select(it => it.Id).ToArray());
                    break;
                case NotifyCollectionChangedAction.Replace:
                    await this.Client.ReplaceElements(containerId, e.NewItems.Cast<AdaptiveElement>().ToArray());
                    break;
                case NotifyCollectionChangedAction.Reset:
                    await this.Client.Reset(containerId);
                    break;
                case NotifyCollectionChangedAction.Move:
                    //TODO
                    break;
            }
        }

        private void BindDomChanges()
        {
            if (this.domEvents.UnProcessed(this.Card))
            {
                this.Card.Body.CollectionChanged += Body_CollectionChanged;
                this.domEvents.MarkProcessed(this.Card);
            }

            foreach (var element in card.GetAllElements().Where(item => this.domEvents.UnProcessed(item)))
            {
                this.domEvents.MarkProcessed(element);
                element.PropertyChanged += Element_PropertyChanged;

                if (element is AdaptiveContainer)
                {
                    AdaptiveContainer container = element as AdaptiveContainer;
                    container.Items.CollectionChanged += Items_CollectionChanged;
                }
                else if (element is AdaptiveColumnSet)
                {
                    AdaptiveColumnSet columnSet = element as AdaptiveColumnSet;
                    columnSet.Columns.CollectionChanged += Columns_CollectionChanged;
                }
            }
        }
    }
}