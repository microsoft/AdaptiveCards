using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public interface ILiveCardClientAPI
    {
        /// <summary>
        /// Called when a Property is changed
        /// </summary>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        Task PropertyChanged(string id, string name, object value);

        /// <summary>
        /// called when a collection is modified
        /// </summary>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="changes"></param>
        /// <returns></returns>
        Task CollectionChanged(string id, string name, NotifyCollectionChangedEventArgs changes);

        /// <summary>
        /// Save the card
        /// </summary>
        /// <returns></returns>
        Task SaveCard(AdaptiveCard card = null);

        /// <summary>
        /// Close the card
        /// </summary>
        /// <returns></returns>
        Task CloseCard();
    }
}
