using Nerdbank;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web;
using System.Web.WebSockets;

namespace LiveCardServerSample
{
    public class StreamingWebSocketHandler
    {
        private int BUFFERSIZE;
        private AspNetWebSocketContext context;
        private WebSocket webSocket;
        private CancellationTokenSource cancelationSource = new CancellationTokenSource();

        public StreamingWebSocketHandler(AspNetWebSocketContext context, int bufferSize = 65535)
        {
            this.context = context;
            this.webSocket = context.WebSocket;
            this.BUFFERSIZE = bufferSize;
            var streams = FullDuplexStream.CreateStreams();
            this.SendStream = streams.Item1;
            this.ReceiveStream = streams.Item2;
        }

        public Stream ReceiveStream { get; private set; }

        public Stream SendStream { get; private set; }


        public async Task StartAsync()
        {
            await Task.WhenAll(WriteTask(), ReadTask());
        }

        public async Task Stop()
        {
            cancelationSource.Cancel();
        }


        // MUST read if we want the socket state to be updated
        private async Task ReadTask()
        {
            var buffer = new ArraySegment<byte>(new byte[BUFFERSIZE]);
            using (TextWriter receiveWriter = new StreamWriter(this.ReceiveStream))
            {
                while (webSocket.State == WebSocketState.Open)
                {
                    var result = await webSocket.ReceiveAsync(buffer, this.cancelationSource.Token).ConfigureAwait(false);
                    var line = Encoding.UTF8.GetString(buffer.Array, 0, result.Count);
                    await receiveWriter.WriteLineAsync(line);
                }
            }
        }

        private async Task WriteTask()
        {
            using (TextReader sendReader = new StreamReader(this.SendStream))
            {
                while (webSocket.State == WebSocketState.Open)
                {
                    var line = await sendReader.ReadLineAsync();
                    var buffer = Encoding.UTF8.GetBytes(line);
                    await this.webSocket.SendAsync(new ArraySegment<byte>(buffer), WebSocketMessageType.Text, true, this.cancelationSource.Token)
                        .ConfigureAwait(false);
                }
            }
        }
    }
}