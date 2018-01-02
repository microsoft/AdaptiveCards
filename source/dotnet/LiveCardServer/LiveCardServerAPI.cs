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
        private AdaptiveCard card;

        public LiveCardServerAPI(AdaptiveCard card)
        {
            this.card = card;
        }

        public Task FireActivate()
        {
            lock (this.card)
                this.card.FireActivate();
            return Task.CompletedTask;
        }

        public Task FireDeactivate()
        {
            lock (this.card)
                this.card.FireDeactivate();
            return Task.CompletedTask;
        }

        public Task FireFocus(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.card)
                    element.FireFocus();
            }
            return Task.CompletedTask;
        }

        public Task FireBlur(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.card)
                    element.FireBlur();
            }
            return Task.CompletedTask;
        }

        public Task FireKey(string id, string key)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.card)
                    element.FireKey(key);
            }
            return Task.CompletedTask;
        }

        public Task FireClick(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.card)
                    element.FireClick();
            }
            return Task.CompletedTask;
        }

        public Task FireTextChanged(string id, string text)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.card)
                    element.FireTextChanged(text);
            }
            return Task.CompletedTask;
        }

        public Task FireSelectionChanged(string id, int[] selectedIndices)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                lock (this.card)
                    element.FireSelectionChanged(selectedIndices);
            }
            return Task.CompletedTask;
        }

        public Task FireMouseEnter(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.card)
                    element.FireMouseEnter();
            }
            return Task.CompletedTask;
        }

        public Task FireMouseLeave(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                lock (this.card)
                    element.FireMouseLeave();
            }
            return Task.CompletedTask;
        }
    }

}