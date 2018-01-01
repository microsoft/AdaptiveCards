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
            return rpc.NotifyAsync();
        }

        public Task FireDeactivate()
        {
            return rpc.NotifyAsync();
        }

        public Task FireFocus(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task FireBlur(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task FireKey(string id, string key)
        {
            return rpc.NotifyAsync(argument: new object[] { id, key });
        }

        public Task FireClick(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task FireTextChanged(string id, string text)
        {
            return rpc.NotifyAsync(argument: new object[] { id, text });
        }

        public Task FireSelectionChanged(string id, int[] selectedIndices)
        {
            return rpc.NotifyAsync(argument: new object[] { id, selectedIndices });
        }

        public Task FireMouseEnter(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task FireMouseLeave(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }
    }

}