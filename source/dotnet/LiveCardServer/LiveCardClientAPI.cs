using AdaptiveCards;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
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

        protected class LocalLiveCard
        {
        }

        /// <summary>
        /// Insert new element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public Task OnInsertElement(InsertPosition position, string id, AdaptiveElement element)
        {
            return rpc.NotifyAsync(new object[] { position.ToString(), id, element });
        }

        /// <summary>
        /// Replace element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public Task OnReplaceElement(AdaptiveElement element)
        {
            return rpc.NotifyAsync(new object[] { element });
        }

        /// <summary>
        /// Remove element
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public Task OnRemoveElement(string id)
        {
            return rpc.NotifyAsync(new object[] { id });
        }

        /// <summary>
        /// SetProperties on element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="properties"></param>
        /// <returns></returns>
        public Task OnSetProperties(string id, IEnumerable<SetProperty> properties)
        {
            return rpc.NotifyAsync(new object[] { id, properties });
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