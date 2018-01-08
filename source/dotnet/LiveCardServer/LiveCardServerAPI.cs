using AdaptiveCards;
using LiveCardAPI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardServer
{
    public class LiveCardServerAPI : ILiveCardServerAPI
    {
        private LiveCard liveCard;

        public LiveCardServerAPI(LiveCard liveCard)
        {
            this.liveCard = liveCard;
        }

        public Task FireActivate()
        {
            lock (this.liveCard)
                this.liveCard.Card.FireActivate();
            return Task.CompletedTask;
        }

        public Task FireDeactivate()
        {
            lock (this.liveCard)
                this.liveCard.Card.FireDeactivate();
            return Task.CompletedTask;
        }

        public Task FireFocus(string id)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.liveCard)
                    element.FireFocus();
            }
            return Task.CompletedTask;
        }

        public Task FireBlur(string id)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.liveCard)
                    element.FireBlur();
            }
            return Task.CompletedTask;
        }

        public Task FireKey(string id, string key)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.liveCard)
                    element.FireKey(key);
            }
            return Task.CompletedTask;
        }

        public Task FireClick(string id)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.liveCard)
                    element.FireClick();
            }
            return Task.CompletedTask;
        }

        public Task FireTextChanged(string id, string text)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.liveCard)
                    element.FireTextChanged(text);
            }
            return Task.CompletedTask;
        }

        public Task FireSelectionChanged(string id, int[] selectedIndices)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.liveCard)
                    element.FireSelectionChanged(selectedIndices);
            }
            return Task.CompletedTask;
        }

        public Task FireMouseEnter(string id)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.liveCard)
                    element.FireMouseEnter();
            }
            return Task.CompletedTask;
        }

        public Task FireMouseLeave(string id)
        {
            if (this.liveCard.Card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.liveCard)
                    element.FireMouseLeave();
            }
            return Task.CompletedTask;
        }
    }

}