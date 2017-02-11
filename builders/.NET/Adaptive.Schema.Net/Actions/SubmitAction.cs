using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// Submit action gathers up input fields, merges with optional data field and generates event to client asking for data to be submitted. It is up to the client to determine how that data is processed. For example: With BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
    public class SubmitAction : ActionBase
    {
        public SubmitAction()
        {

        }

        /// <summary>
        /// initial data that input fields will be combined with. This is essentially 'hidden' properties, Example: {"id":"123123123"}
        /// </summary>
        public object Data { get; set; }
    }
}
