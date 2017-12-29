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
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public Task PropertyChanged(string id, string name, object value)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveTypedElement el))
            {
                var propertyInfo = el.GetType().GetProperty(name);
                propertyInfo.SetValue(el, value);
            }
            return Task.CompletedTask;
        }

        /// <summary>
        /// apply Remote collection change
        /// </summary>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="changes"></param>
        /// <returns></returns>
        public Task CollectionChanged(string id, string name, NotifyCollectionChangedEventArgs changes)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveTypedElement el))
            {
                var propertyInfo = el.GetType().GetProperty(name);
                object objs = propertyInfo.GetValue(el);

                if (objs is IList<AdaptiveElement>)
                    ApplyCollectionChanges<AdaptiveElement>(changes, objs, (item) => item.Id);
                else if (objs is IList<AdaptiveAction>)
                    ApplyCollectionChanges<AdaptiveAction>(changes, objs, (item) => item.Id);
                // TODO handle other collections
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

        private static void ApplyCollectionChanges<T>(NotifyCollectionChangedEventArgs changes, object objs, Func<T, object> selectIdentity)
        {
            var items = (ObservableCollection<T>)objs;
            switch (changes.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    AddNewItems(changes, items);
                    break;

                case NotifyCollectionChangedAction.Replace:
                    RemoveItems(changes, items, selectIdentity);
                    AddNewItems(changes, items);
                    break;

                case NotifyCollectionChangedAction.Remove:
                    RemoveItems(changes, items, selectIdentity);
                    break;

                case NotifyCollectionChangedAction.Reset:
                    items.Clear();
                    break;

                case NotifyCollectionChangedAction.Move:
                    // TODO
                    break;
            }
        }

        private static void RemoveItems<T>(NotifyCollectionChangedEventArgs changes, IList<T> items, Func<T, object> selectIdentity)
        {
            foreach (var oldItemId in changes.OldItems.Cast<T>().Select(selectIdentity))
            {
                int pos = 0;
                foreach (var item in items)
                {
                    if (selectIdentity(item) == oldItemId)
                    {
                        items.RemoveAt(pos);
                        break;
                    }
                    pos++;
                }
            }
        }

        private static void AddNewItems<T>(NotifyCollectionChangedEventArgs changes, IList<T> items)
        {
            int pos = changes.NewStartingIndex;
            foreach (var newItem in changes.NewItems.Cast<T>())
            {
                if (pos == -1)
                    items.Add(newItem);
                else
                    items.Insert(pos++, newItem);
            }
        }


    }
}
