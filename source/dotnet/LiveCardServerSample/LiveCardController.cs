using AdaptiveCards;
using LiveCardServer;
using Newtonsoft.Json;
using StreamJsonRpc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Web;
using System.Web.Http;

namespace LiveCardServerSample
{
    public class LiveCardController : ApiController
    {
        public LiveCard LiveCard { get; private set; }

        protected HttpResponseMessage ServiceLiveCard(AdaptiveCard card)
        {
            HttpContext currentContext = HttpContext.Current;
            if (currentContext.IsWebSocketRequest || currentContext.IsWebSocketRequestUpgrading)
            {
                currentContext.AcceptWebSocketRequest((webSockContext) =>
                {
                    var handler = new StreamingWebSocketHandler(webSockContext);

                    // hook up jsonrpc to streams
                    JsonRpc rpc = new JsonRpc(handler.SendStream, handler.ReceiveStream);

                    // initialize livecard on RPC channel
                    this.LiveCard = new LiveCard(card, rpc);

                    // hooking up websocket activates the card
                    card.Activate();
                    // start processing of send/receive streams...
                    rpc.StartListening();
                    return handler.StartAsync();
                });
                return Request.CreateResponse(HttpStatusCode.SwitchingProtocols);
            }
            var repsonse = new HttpResponseMessage()
            {
                Content = new StringContent(JsonConvert.SerializeObject(card, Formatting.Indented))
            };
            repsonse.Content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
            return repsonse;
        }
    }
}
