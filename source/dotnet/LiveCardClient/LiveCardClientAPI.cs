using AdaptiveCards;
using LiveCardAPI;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
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
        LiveCard liveCard;

        public LiveCardClientAPI(LiveCard card)
        {
            this.liveCard = card;
        }

        /// <summary>
        /// apply remote property change
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public Task SetProperty(string elementId, string name, object value)
        {
            lock (this.liveCard.Card)
            {
                if (this.liveCard.Card.TryGetElementById(elementId, out AdaptiveTypedElement el))
                {
                    var propertyInfo = el.GetType().GetProperty(name);
                    propertyInfo.SetValue(el, value);
                }
            }
            return Task.CompletedTask;
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
            lock (this.liveCard.Card)
            {
                if (this.liveCard.Card.TryGetElementById(elementId, out AdaptiveTypedElement element))
                {
                    IList<AdaptiveElement> elements = element.GetChildElements();
                    if (elements == null)
                        throw new ArgumentNullException("This is not an collection of elements");
                    int pos = insertIndex;
                    foreach (var newItem in newItems)
                    {
                        if (pos == -1)
                            elements.Add(newItem);
                        else if (pos > elements.Count)
                            elements.Add(newItem);
                        else
                            elements.Insert(pos++, newItem);
                    }
                }
            }
            return Task.CompletedTask;
        }


        /// <summary>
        /// Remove elements from collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="elementIds"></param>
        /// <returns></returns>
        public Task RemoveElements(string elementId, string[] elementIds)
        {
            lock (this.liveCard.Card)
            {
                if (this.liveCard.Card.TryGetElementById(elementId, out AdaptiveTypedElement element))
                {
                    IList<AdaptiveElement> elements = element.GetChildElements();
                    if (elements == null)
                        throw new ArgumentNullException("This is not an collection of elements");

                    foreach (var removeId in elementIds)
                    {
                        int pos = 0;
                        foreach (var el in elements)
                        {
                            if (el.Id == removeId)
                            {
                                elements.RemoveAt(pos);
                                break;
                            }
                            pos++;
                        }
                    }
                }
            }
            return Task.CompletedTask;
        }

        /// <summary>
        /// Replace Elements in collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <param name="newElements"></param>
        /// <returns></returns>
        public Task ReplaceElements(string elementId, AdaptiveElement[] newElements)
        {
            lock (this.liveCard.Card)
            {
                if (this.liveCard.Card.TryGetElementById(elementId, out AdaptiveTypedElement element))
                {
                    IList<AdaptiveElement> elements = element.GetChildElements();
                    if (elements == null)
                        throw new ArgumentNullException("This is not an collection of elements");

                    foreach (var newElement in newElements)
                    {
                        int pos = 0;
                        foreach (var el in elements)
                        {
                            if (el.Id == newElement.Id)
                            {
                                elements[pos] = newElement;
                                break;
                            }
                            pos++;
                        }
                    }
                }
            }
            return Task.CompletedTask;
        }

        /// <summary>
        /// Reset collection
        /// </summary>
        /// <param name="elementId"></param>
        /// <returns></returns>
        public Task Reset(string elementId)
        {
            lock (this.liveCard.Card)
            {
                if (this.liveCard.Card.TryGetElementById(elementId, out AdaptiveTypedElement element))
                {
                    IList<AdaptiveElement> elements = element.GetChildElements();
                    if (elements == null)
                        throw new ArgumentNullException("This is not an collection of elements");
                    elements.Clear();
                }
            }
            return Task.CompletedTask;
        }

        /// <summary>
        /// Save the card
        /// </summary>
        /// <returns></returns>
        public virtual Task SaveCard(AdaptiveCard card = null)
        {
            return this.liveCard.SaveCard(card);
        }

        /// <summary>
        /// Close the card
        /// </summary>
        /// <returns></returns>
        public async virtual Task CloseCard()
        {
            await this.liveCard.CloseCard();
        }

    }
}
