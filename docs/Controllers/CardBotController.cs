using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using Microsoft.Bot.Connector;
using System.Threading;
using System.IO;
using System.Text;
using Microsoft.AspNetCore.Hosting;
using Newtonsoft.Json;
using AdaptiveCards;
using Microsoft.AspNetCore.Authorization;

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
            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }

        private async Task<HttpResponseMessage> SendReply(IMessageActivity message, string text, Attachment[] attachments = null)
        {
            var reply = ((Activity)message).CreateReply(text);
            reply.Attachments = attachments;

            //MicrosoftAppCredentials.TrustServiceUrl(message.ServiceUrl);
            var connectorAPI = new ConnectorClient(new Uri(message.ServiceUrl), new MicrosoftAppCredentials(AppId, AppPassword));
            await connectorAPI.Conversations.ReplyToActivityAsync(reply);
            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }

        private async Task<HttpResponseMessage> ProcessMessage(IMessageActivity message)
        {
            if (message.Text.Contains("cards"))
                return await ListCards(message);

            return await SendCard((Activity)message, message.Text.Replace(" ", ""));
        }


        private async Task<HttpResponseMessage> SendCard(Activity activity, string cardName)
        {
            var path = Path.Combine(_env.WebRootPath, $@"samples\{cardName}.json");
            if (System.IO.File.Exists(path))
            {
                string json = System.IO.File.ReadAllText(path);
                if (json != null)
                {
                    AdaptiveCard card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
                    var attachments = new Attachment[] { new Attachment(AdaptiveCard.ContentType, content: card) };
                    return await SendReply(activity, String.Empty, attachments);
                }
            }
            return await SendReply(activity, $"Could not find a card for {activity.Text}");
            return await SendReply(activity, "* type **cards** to get a list of cards\n* type **card *cardname* ** to display a given card by name");
        }


        private async Task<HttpResponseMessage> ListCards(IMessageActivity message)
        {
            Activity activity = (Activity)message;
            var path = Path.Combine(_env.WebRootPath, "samples");

            StringBuilder sb = new StringBuilder();
            foreach (var file in Directory.GetFiles(path).Where(f => f.EndsWith(".json")))
            {
                sb.AppendLine($"* {Path.GetFileNameWithoutExtension(file)}");
            }

            return await SendReply(message, sb.ToString());
        }
    }
}