using AdaptiveCards;
using System;
using System.Collections;
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
        /// <param name="elementId"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        Task SetProperty(string elementId, string name, object value);

        /// <summary>
        /// Add elements to collection
        /// </summary>
        /// <param name="elementId">collection element Id</param>
        /// <param name="insertIndex">use -1 to append</param>
        /// <param name="newItems"></param>
        /// <returns></returns>
        Task AddElements(string elementId, int insertIndex, AdaptiveElement[] newItems);

        /// <summary>
        /// Remove elements from collection
        /// </summary>
        /// <param name="elementId">collection element Id</param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        Task RemoveElements(string elementId, string[] elementIds);

        /// <summary>
        /// Replace elements in collection
        /// </summary>
        /// <param name="elementId">collection element Id</param>
        /// <param name="elements"></param>
        /// <returns></returns>
        Task ReplaceElements(string elementId, AdaptiveElement[] elements);

        /// <summary>
        /// Reset element to default
        /// </summary>
        /// <param name="elementId">collection element Id</param>
        /// <returns></returns>
        Task ResetElements(string elementId);
       
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
