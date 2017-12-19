using AdaptiveCards;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardClient
{
    /// <summary>
    /// api exposed to LiveCardServer so that it can manipulate the dom 
    /// </summary>
    public class LiveCardClientAPI : ILiveCardClientAPI
    {
        AdaptiveCard card;
        Action<AdaptiveElement> binder;

        public LiveCardClientAPI(AdaptiveCard card, Action<AdaptiveElement> binder)
        {
            this.card = card;
            this.binder = binder;
        }

        /// <summary>
        /// Insert new element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public Task InsertElement(string id, InsertPosition position, AdaptiveElement element)
        {
            this.binder(element);
            return this.card.InsertElement(id, position, element);
        }

        /// <summary>
        /// Replace element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public Task ReplaceElement(AdaptiveElement element)
        {
            this.binder(element);
            return this.card.ReplaceElement(element);
        }

        /// <summary>
        /// Remove element
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public Task RemoveElement(string id)
        {
            return this.card.RemoveElement(id);
        }

        /// <summary>
        /// SetProperties on element
        /// </summary>
        /// <param name="id"></param>
        /// <param name="properties"></param>
        /// <returns></returns>
        public Task SetProperties(string id, IEnumerable<SetProperty> properties)
        {
            return this.card.SetProperties(id, properties);
        }

        /// <summary>
        /// Save the card
        /// </summary>
        /// <returns></returns>
        public Task SaveCard(AdaptiveCard card = null)
        {
            return Task.CompletedTask;
        }

        /// <summary>
        /// Close the card
        /// </summary>
        /// <returns></returns>
        public Task CloseCard()
        {
            return Task.CompletedTask;
        }
    }
}