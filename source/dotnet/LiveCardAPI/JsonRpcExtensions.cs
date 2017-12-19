using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Web;

namespace LiveCardAPI
{

    public static class JsonRpcExtensions
    {
        public static Task InvokeAsync(this JsonRpc rpc, object argument, [CallerMemberName] string targetName = null)
        {
            return rpc.InvokeAsync(targetName, argument);
        }

        public static Task InvokeAsync(this JsonRpc rpc, object[] arguments, [CallerMemberName] string targetName = null)
        {
            return rpc.InvokeAsync(targetName, arguments);
        }

        public static Task<TResult> InvokeAsync<TResult>(this JsonRpc rpc, object argument, [CallerMemberName] string targetName = null)
        {
            return rpc.InvokeAsync<TResult>(targetName, argument);
        }

        public static Task<TResult> InvokeAsync<TResult>(this JsonRpc rpc, object[] arguments, [CallerMemberName] string targetName = null)
        {
            return rpc.InvokeAsync<TResult>(targetName, arguments);
        }

        public static Task NotifyAsync(this JsonRpc rpc, object argument = null, [CallerMemberName] string targetName = null)
        {
            return rpc.NotifyAsync(targetName, argument);
        }

        public static Task NotifyAsync(this JsonRpc rpc, object[] arguments, [CallerMemberName] string targetName = null)
        {
            return rpc.NotifyAsync(targetName, arguments);
        }

        public static Task NotifyWithParameterObjectAsync(this JsonRpc rpc, object argument = null, [CallerMemberName] string targetName = null)
        {
            return rpc.NotifyWithParameterObjectAsync(targetName, argument);
        }
    }
}