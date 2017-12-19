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

        public Task OnActivate()
        {
            return rpc.NotifyAsync();
        }

        public Task OnDeactivate()
        {
            return rpc.NotifyAsync();
        }

        public Task OnFocus(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task OnBlur(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task OnKey(string id, string key)
        {
            return rpc.NotifyAsync(argument: new object[] { id, key });
        }

        public Task OnClick(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task OnDoubleClick(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task OnTextChanged(string id, string text)
        {
            return rpc.NotifyAsync(argument: new object[] { id, text });
        }

        public Task OnSelectionChanged(string id, int[] selectedIndices)
        {
            return rpc.NotifyAsync(argument: new object[] { id, selectedIndices });
        }

        public Task OnMouseEnter(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }

        public Task OnMouseLeave(string id)
        {
            return rpc.NotifyAsync(argument: id);
        }
    }

}