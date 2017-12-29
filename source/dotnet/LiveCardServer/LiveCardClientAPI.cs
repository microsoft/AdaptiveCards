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
        /// <param name="elementId"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public Task SetProperty(string elementId, string name, object value)
        {
            return rpc.NotifyAsync(new object[] { elementId, name, value });
        }

        /// <summary>
        /// Add elements to collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="insertIndex"></param>
        /// <param name="newItems"></param>
        /// <returns></returns>
        public Task AddElements(string elementId, int insertIndex, IEnumerable<AdaptiveElement> newItems)
        {
            return rpc.NotifyAsync(new object[] { elementId, insertIndex, newItems });
        }

        /// <summary>
        /// Remove elements from collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        public Task RemoveElements(string elementId, IEnumerable<string> elementIds)
        {
            return rpc.NotifyAsync(new object[] { elementId, elementIds});
        }

        /// <summary>
        /// Replace elements in collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        public Task ReplaceElements(string elementId, IEnumerable<AdaptiveElement> elements)
        {
            return rpc.NotifyAsync(new object[] { elementId, elements});
        }


        /// <summary>
        /// Reset collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <returns></returns>
        public Task Reset(string elementId)
        {
            return rpc.NotifyAsync(elementId);
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