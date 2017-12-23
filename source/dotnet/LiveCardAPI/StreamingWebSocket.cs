//using Nerdbank;
//using System;
//using System.Collections.Generic;
//using System.Diagnostics;
//using System.IO;
//using System.Linq;
//using System.Net.WebSockets;
//using System.Text;
//using System.Threading;
//using System.Threading.Tasks;
//using System.Web;

//namespace LiveCardAPI
//{
//    public class WebSocketStream : Stream
//    {
//        private WebSocket socket;
//        public WebSocketStream(WebSocket socket)
//        {
//            this.socket = socket;
//        }

//        public override bool CanRead => true;

//        public override bool CanSeek => false;

//        public override bool CanWrite => true;

//        public override long Length => throw new NotImplementedException();

//        public override long Position { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

//        public override void Flush()
//        {
//        }

//        public override int Read(byte[] buffer, int offset, int count)
//        {
//            throw new NotImplementedException();
//        }

//        public override long Seek(long offset, SeekOrigin origin)
//        {
//            throw new NotImplementedException();
//        }

//        public override void SetLength(long value)
//        {
//            throw new NotImplementedException();
//        }

//        public override void Write(byte[] buffer, int offset, int count)
//        {
//            throw new NotImplementedException();
//        }

//        public override async Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
//        {
//            var result = await this.socket.ReceiveAsync(new ArraySegment<byte>(buffer, offset, count), cancellationToken);
//            return result.Count;
//        }

//        public async override Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
//        {
//            await this.socket.SendAsync(new ArraySegment<byte>(buffer, offset, count), WebSocketMessageType.Text, true, cancellationToken);
//        }

//    }


//    public class StreamingWebSocket
//    {
//        private int BUFFERSIZE;
//        private WebSocket webSocket;
//        private CancellationTokenSource cancelationSource = new CancellationTokenSource();

//        public StreamingWebSocket(WebSocket socket, int bufferSize = 65535)
//        {
//            this.webSocket = socket;
//            this.BUFFERSIZE = bufferSize;
//            var streams = FullDuplexStream.CreateStreams();
//            this.SendStream = streams.Item1;
//            this.ReceiveStream = streams.Item2;
//        }

//        public Stream ReceiveStream { get; private set; }

//        public Stream SendStream { get; private set; }


//        public async Task StartAsync()
//        {
//            await Task.WhenAll(WriteTask(), ReadTask());
//        }

//        public async Task Stop()
//        {
//            cancelationSource.Cancel();
//        }


//        // MUST read if we want the socket state to be updated
//        private async Task ReadTask()
//        {
//            var buffer = new ArraySegment<byte>(new byte[BUFFERSIZE]);
//            using (TextWriter receiveWriter = new StreamWriter(this.ReceiveStream))
//            {
//                while (webSocket.State == WebSocketState.Open)
//                {
//                    try
//                    {
//                        var result = await webSocket.ReceiveAsync(buffer, this.cancelationSource.Token).ConfigureAwait(false);
//                        var line = Encoding.UTF8.GetString(buffer.Array, 0, result.Count);
//                        await receiveWriter.WriteLineAsync(line);
//                    }
//                    catch (Exception err)
//                    {
//                        Trace.TraceError(err.ToString());
//                    }
//                }
//            }
//        }

//        private async Task WriteTask()
//        {
//            using (TextReader sendReader = new StreamReader(this.SendStream))
//            {
//                while (webSocket.State == WebSocketState.Open)
//                {
//                    try
//                    {
//                        var line = await sendReader.ReadLineAsync();
//                        var buffer = Encoding.UTF8.GetBytes(line);
//                        await this.webSocket.SendAsync(new ArraySegment<byte>(buffer), WebSocketMessageType.Text, true, this.cancelationSource.Token)
//                            .ConfigureAwait(false);
//                    }
//                    catch (Exception err)
//                    {
//                        Trace.TraceError(err.ToString());
//                    }
//                }
//            }
//        }
//    }
//}