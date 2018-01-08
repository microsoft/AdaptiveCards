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
            return rpc.NotifyAsync("SetProperty", elementId, name, value);
        }

        /// <summary>
        /// Add elements to collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="insertIndex"></param>
        /// <param name="newItems"></param>
        /// <returns></returns>
        public Task AddElements(string elementId, int insertIndex, AdaptiveElement[] newItems)
        {
            return rpc.NotifyAsync("AddElements", elementId, insertIndex, newItems);
        }

        /// <summary>
        /// Remove elements from collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        public Task RemoveElements(string elementId, string[] elementIds)
        {
            return rpc.NotifyAsync("RemoveElements", elementId, elementIds);
        }

        /// <summary>
        /// Replace elements in collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        public Task ReplaceElements(string elementId, AdaptiveElement[] elements)
        {
            return rpc.NotifyAsync("ReplaceElements", elementId, elements );
        }


        /// <summary>
        /// Reset collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <returns></returns>
        public Task ResetElements(string elementId)
        {
            return rpc.NotifyAsync("ResetElements", elementId);
        }

        /// <summary>
        /// Replace entire card
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public Task ReplaceCard(AdaptiveCard card)
        {
            return rpc.NotifyAsync("ReplaceCard", card);
        }

        /// <summary>
        /// Save the card
        /// </summary>
        /// <returns></returns>
        public Task SaveCard(AdaptiveCard card = null)
        {
            return rpc.NotifyAsync("SaveCard", card);
        }

        /// <summary>
        /// Close the card
        /// </summary>
        /// <returns></returns>
        public Task CloseCard()
        {
            return rpc.NotifyAsync("CloseCard");
        }

    }
}