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
    public class LiveCardServerAPI : ILiveCardServerAPI
    {
        private JsonRpc rpc;

        public LiveCardServerAPI(JsonRpc rpc)
        {
            this.rpc = rpc;
        }

        public Task FireActivate()
        {
            return rpc.NotifyAsync("FireActivate");
        }

        public Task FireDeactivate()
        {
            return rpc.NotifyAsync("FireDeactivate");
        }

        public Task FireFocus(string id)
        {
            return rpc.NotifyAsync("FireFocus", id);
        }

        public Task FireBlur(string id)
        {
            return rpc.NotifyAsync("FireBlur", id);
        }

        public Task FireKey(string id, string key)
        {
            return rpc.NotifyAsync("FireKey", id, key);
        }

        public Task FireClick(string id)
        {
            return rpc.NotifyAsync("FireClick", id);
        }

        public Task FireTextChanged(string id, string text)
        {
            return rpc.NotifyAsync("FireTextChanged", id, text);
        }

        public Task FireSelectionChanged(string id, int[] selectedIndices)
        {
            return rpc.NotifyAsync("FireSelectionChanged", id, selectedIndices);
        }

        public Task FireMouseEnter(string id)
        {
            return rpc.NotifyAsync("FireMouseEnter", id);
        }

        public Task FireMouseLeave(string id)
        {
            return rpc.NotifyAsync("FireMouseLeave", id);
        }
    }

}