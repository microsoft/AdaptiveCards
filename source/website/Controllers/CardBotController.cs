// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Bot.Connector;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace Docs.Controllers
{
    [Route("api/[controller]")]
    public class CardBotController : Controller
    {
        private IHostingEnvironment _env;
        // botId= "cardbot-test"
        public const string AppId = "4937f87d-3c07-4c9d-873f-d45b06bae832";
        public const string AppPassword = "i1ATiOTPCVxHnJNOfOpjfRg";

        public CardBotController(IHostingEnvironment env)
        {
            _env = env;
        }


        [HttpPost]
        [Authorize(Roles = "Bot")]
        public async Task<HttpResponseMessage> Post([FromBody] Activity activity)
        {
            if (activity != null)
            {
                // one of these will have an interface and process it
                switch (activity.GetActivityType())
                {
                    case ActivityTypes.Message:
                        return await ProcessMessage(activity);
                    case ActivityTypes.ConversationUpdate:
                    case ActivityTypes.ContactRelationUpdate:
                    case ActivityTypes.Typing:
                    case ActivityTypes.DeleteUserData:
                    case ActivityTypes.Invoke:
                    case ActivityTypes.Ping:
                        break;
                }
            }
            return new HttpResponseMessage(HttpStatusCode.OK);
        }

        [HttpGet]
        public async Task<ContentResult> Get(string cardName)
        {
            cardName = cardName.Replace("_", " ");
            var path = Path.Combine(_env.WebRootPath, $@"samples\cards\{cardName}.json");
            if (System.IO.File.Exists(path))
            {
                string json = System.IO.File.ReadAllText(path);
                if (json != null)
                {
                    AdaptiveCard card = JsonConvert.DeserializeObject<AdaptiveCard>(json);

#if HTML
                    var hostConfig = new HostConfig() { SupportsInteractivity = false };
                    HtmlRenderer renderer = new HtmlRenderer(hostConfig);
                    var html = renderer.RenderAdaptiveCard(card);
                    return new ContentResult()
                    {
                        Content = $@"
<html lang='en'>
<head>
    <meta charset = 'utf-8' />
    <title>Adaptive Cards</title>

    <link rel='stylesheet' href='/content/fonts.css'>
	<link rel='stylesheet' href='/content/shared.css'>
	<link rel='stylesheet' href='/content/card.css'>
	<link rel='stylesheet' href='/explorer/explorer.css'>
    <script src='/node_modules/jquery/dist/jquery.min.js'></script>
    <script src='/node_modules/adaptive-cards/dist/adaptive-cards.js'></script>
	<script src='/explorer/explorer.js'></script>
<style>
body {{
    margin:0px;
}}
.card {{
    margin:0px;
    width:100%;
}}
</style>

</head>
<body>
<div id='kikCard' class='card' ></div>
<script>renderCard('kikCard', {json});</script>
</body>
</html>",
                        ContentType = "text/html"
                    };
#else
                    var hostConfig = new HostConfig() { SupportsInteractivity = false, };
                    hostConfig.TextBlock.Separations.Small.Spacing = 2;
                    hostConfig.TextBlock.Separations.Medium.Spacing = 2;
                    hostConfig.TextBlock.Separations.Large.Spacing = 2;
                    hostConfig.TextBlock.Separations.ExtraLarge.Spacing = 2;
                    hostConfig.TextBlock.Separations.Normal.Spacing = 2;
                    hostConfig.Image.Separation.Spacing = 2;
                    hostConfig.Container.Separation.Spacing = 2;
                    hostConfig.Column.Separation.Spacing = 2;
                    hostConfig.ColumnSet.Separation.Spacing = 2;
                    hostConfig.FactSet.Separation.Spacing = 2;
                    hostConfig.ImageSet.Separation.Spacing = 2;
                    hostConfig.StrongSeparation.Spacing = 6;
                    HtmlRenderer renderer = new HtmlRenderer(hostConfig);
                    var html = renderer.RenderAdaptiveCard(card);
                    return new ContentResult()
                    {
                        Content = $@"
<html lang='en'>
<head>
    <meta charset='utf-8' />
    <title>Adaptive Cards</title>
    <meta name='viewport' content='width=220, initial-scale=1'/>

    <link rel='stylesheet' href='/content/fonts.css'/>
	<link rel='stylesheet' href='/content/shared.css'/>
	<link rel='stylesheet' href='/content/card.css'/>
<style>
body {{
    margin:0px;
    width:220px;
}}
.card {{
    padding:10px 10px 10px 10px;
}}
</style>

</head>
<body>
<div id='kikCard' class='card' >{html.ToString()}</div>
</body>
</html>",
                        ContentType = "text/html"
                    };
#endif
                }
            }
            return null;
        }

        private async Task<HttpResponseMessage> SendReply(IMessageActivity message, string text, Attachment[] attachments = null, object channelData = null)
        {
            var reply = ((Activity)message).CreateReply(text);
            reply.Attachments = attachments;
            reply.ChannelData = channelData;

            var connectorAPI = new ConnectorClient(new Uri(message.ServiceUrl), new MicrosoftAppCredentials(AppId, AppPassword));
            await connectorAPI.Conversations.ReplyToActivityAsync(reply);
            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }

        private async Task<HttpResponseMessage> ProcessMessage(IMessageActivity message)
        {
            if (message.Text.ToLower().Contains("cards"))
                return await ListCards(message);
            if (message.Text.ToLower().Contains("help"))
                return await SendHelp(message);

            return await SendCard((Activity)message, message.Text.ToLower());
        }

        private async Task<HttpResponseMessage> SendHelp(IMessageActivity message)
        {
            return await SendReply(message, "* type **cards** to get a list of cards\n* type ***cardname* ** to display a given card by name");
        }

        private async Task<HttpResponseMessage> SendCard(Activity activity, string cardName)
        {
            var path = Path.Combine(_env.WebRootPath, $@"samples\cards\{cardName}.json");
            if (System.IO.File.Exists(path))
            {
                var incomingChannelData = JsonConvert.DeserializeObject<KikMessages>((string)activity.ChannelData);
                var json = $@"
 {{
    'messages': [
        {{
            'type': 'widget',
            'chatId': '{incomingChannelData.messages[0].chatId}',
            'to': '{incomingChannelData.messages[0].from}',
            'url': 'http://adaptivecards-staging.azurewebsites.net/api/CardBot?cardName={cardName.Replace(" ", "_")}',
            'size': {{
                'width': 220,
                'height': 300
            }},
            'static': false,
        }}
    ]
}}
";
                dynamic channelData = JsonConvert.DeserializeObject(json);

                return await SendReply(activity, String.Empty, attachments: null, channelData: channelData);
            }
            await SendReply(activity, $"I could not find a card for {activity.Text}");
            return await SendHelp(activity);
        }


        private async Task<HttpResponseMessage> ListCards(IMessageActivity message)
        {
            Activity activity = (Activity)message;
            var path = Path.Combine(_env.WebRootPath, @"samples\cards");

            StringBuilder sb = new StringBuilder();
            foreach (var file in Directory.GetFiles(path).Where(f => f.EndsWith(".json")))
            {
                sb.AppendLine($"* {Path.GetFileNameWithoutExtension(file)}");
            }

            return await SendReply(message, sb.ToString());
        }
    }

    public class KikMessage
    {
        // Conversation bot is involved in.  Must be sent back in all responses
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string chatId { get; set; }

        // Id for this particular message
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string id { get; set; }

        // "text", "link", "picture", "video", "start-chatting", "scan-data", "sticker", "is-typing", "delivery-receipt", "read-receipt"
        public string type { get; set; }

        // Kik username of message sender
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string from { get; set; }

        // List of particpants in conversation
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public List<string> participants { get; set; }

        // Text of the message when message is of type 'text'
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string body { get; set; }

        // Data coming from a scan code
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string data { get; set; }

        // Epoch in milliseconds when message was send
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public long? timestamp { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? readReceiptRequested { get; set; }

        // Url to an image when message is of type 'picture'
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string picUrl { get; set; }

        // The URL of the video or GIF you wish to send.
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string videoUrl { get; set; }

        // Url to a sticker image when message is of type 'sticker'
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string stickerUrl { get; set; }

        // Link Url
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string url { get; set; }

        // Not sent in JSON but as part of request header
        public string to { get; set; }
    }

    public class KikMessages
    {
        public List<KikMessage> messages { get; set; }

    }

}
