using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using AdaptiveCards;
using LiveCardServer;
using Microsoft.AspNetCore.Mvc;

namespace HelloWorldServer.Controllers
{
    public class MyData
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }

        public DateTime Birthday { get; set; } = DateTime.MinValue;
    }

    [Route("api/[controller]")]
    public class EditFormController : Controller
    {
        public LiveCard LiveCard { get; private set; }

        private MyData MyData { get; set; } = new MyData();

        [HttpGet]
        public async Task<AdaptiveCard> Get()
        {
            AdaptiveCard staticForm = new AdaptiveCard()
            {
                Id = "EditForm",
            };
            BindData(staticForm, this.MyData);
            staticForm.OnCardActivate += StaticForm_OnCardActivate;

            // start with deactivated card, but if client hooks up WebSocket then it becomes activated live card
            if (this.HttpContext.WebSockets.IsWebSocketRequest)
            {
                // Response.StatusCode = (int)HttpStatusCode.SwitchingProtocols;
                var webSocket = await HttpContext.WebSockets.AcceptWebSocketAsync("json-rpc");

                // initialize livecard on RPC channel
                this.LiveCard = new LiveCard(staticForm, webSocket);

                // start listening
                await this.LiveCard.StartListening();

                // wait as long as client keeps connection open
                await this.LiveCard.ListeningTask;
            }
            return staticForm;
        }

        private static void BindData(AdaptiveCard staticForm, MyData data)
        {
            staticForm.Body.Add(new AdaptiveTextBlock() { Text = $"First Name: {data.FirstName ?? String.Empty}" });
            staticForm.Body.Add(new AdaptiveTextBlock() { Text = $"Last Name: {data.LastName ?? String.Empty}" });
            staticForm.Body.Add(new AdaptiveTextBlock() { Text = $"Birthday: {data.Birthday.ToShortDateString()}" });
        }

        private void StaticForm_OnCardActivate(object sender, EventArgs e)
        {
            AdaptiveCard card = (AdaptiveCard)sender;
            card.Body.Clear();

            card.Body.Add(new AdaptiveTextBlock() { Text = $"First Name" });
            card.Body.Add(new AdaptiveTextInput()
            {
                Id = "FirstName",
                Placeholder = "Enter first name",
                Value = this.MyData.FirstName
            });

            card.Body.Add(new AdaptiveTextBlock() { Text = $"Last Name" });
            card.Body.Add(new AdaptiveTextInput()
            {
                Id = "LastName",
                Placeholder = "Enter last name",
                Value = this.MyData.LastName
            });

            card.Body.Add(new AdaptiveTextBlock() { Text = $"Birthday" });
            card.Body.Add(new AdaptiveDateInput()
            {
                Id = "Birthday",
                Placeholder = "Enter birthday",
                Value = this.MyData.Birthday.ToString("r")
            });
        }

    }
}