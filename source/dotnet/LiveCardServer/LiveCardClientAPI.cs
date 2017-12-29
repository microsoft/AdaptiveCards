using AdaptiveCards;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardServer
{
    /// <summary>
    /// 
    /// </summary>
    public class LiveCardClientAPI : ILiveCardClientAPI
    {
        JsonRpc rpc;

        public LiveCardClientAPI(JsonRpc rpc)
        {
            this.rpc = rpc;
        }

        /// <summary>
        /// Tell client that property value changed
        /// </summary>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public Task PropertyChanged(string id, string name, object value)
        {
            return rpc.NotifyAsync(new object[] { id, name, value });
        }

        /// <summary>
        /// Tell client that collection has changed.
        /// </summary>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="changes"></param>
        /// <returns></returns>
        public Task CollectionChanged(string id, string name, NotifyCollectionChangedEventArgs changes)
        {
            return rpc.NotifyAsync(new object[] { id, name, changes });
        }

        /// <summary>
        /// Save the card
        /// </summary>
        /// <returns></returns>
        public Task SaveCard(AdaptiveCard card = null)
        {
            return rpc.NotifyAsync(card);
        }

        /// <summary>
        /// Close the card
        /// </summary>
        /// <returns></returns>
        public Task CloseCard()
        {
            return rpc.NotifyAsync();
        }

    }
}