using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace LiveCardAPI
{
    public class WebSocketMessageHandler : DelimitedMessageHandler
    {
        private int bufferSize;

        public WebSocketMessageHandler(WebSocket webSocket, int bufferSize = 65535) : base(Stream.Null, Stream.Null, Encoding.UTF8)
        {
            this.WebSocket = webSocket;
            this.bufferSize = bufferSize;
        }

        public WebSocket WebSocket { get; set; }

        protected async override Task<string> ReadCoreAsync(CancellationToken cancellationToken)
        {
            var buffer = new ArraySegment<byte>(new byte[this.bufferSize]);
            var result = await WebSocket.ReceiveAsync(buffer, cancellationToken).ConfigureAwait(false);
            var json = Encoding.UTF8.GetString(buffer.Array, 0, result.Count);
            return json;
        }

        protected async override Task WriteCoreAsync(string content, Encoding contentEncoding, CancellationToken cancellationToken)
        {
            var buffer = Encoding.UTF8.GetBytes(content);
            await this.WebSocket.SendAsync(new ArraySegment<byte>(buffer), WebSocketMessageType.Text, true, cancellationToken)
                .ConfigureAwait(false);
        }
    }
}
