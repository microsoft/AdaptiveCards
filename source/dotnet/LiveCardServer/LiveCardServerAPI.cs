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

        public Task OnActivate()
        {
            this.card.Activate();
            return Task.CompletedTask;
        }

        public Task OnDeactivate()
        {
            this.card.Deactivate();
            return Task.CompletedTask;
        }

        public Task OnFocus(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                element.Focus();
            }
            return Task.CompletedTask;
        }

        public Task OnBlur(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                element.Blur();
            }
            return Task.CompletedTask;
        }

        public Task OnKey(string id, string key)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                element.Key(key);
            }
            return Task.CompletedTask;
        }

        public Task OnClick(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                element.Click();
            }
            return Task.CompletedTask;
        }

        public Task OnDoubleClick(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                element.DoubleClick();
            }
            return Task.CompletedTask;
        }

        public Task OnTextChanged(string id, string text)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                element.TextChanged(text);
            }
            return Task.CompletedTask;
        }

        public Task OnSelectionChanged(string id, int[] selectedIndices)
        {
            if (this.card.TryGetElementById(id, out AdaptiveInput element))
            {
                element.SelectionChanged(selectedIndices);
            }
            return Task.CompletedTask;
        }

        public Task OnMouseEnter(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                element.MouseEnter();
            }
            return Task.CompletedTask;
        }

        public Task OnMouseLeave(string id)
        {
            if (this.card.TryGetElementById(id, out AdaptiveElement element))
            {
                element.MouseLeave();
            }
            return Task.CompletedTask;
        }
    }

}