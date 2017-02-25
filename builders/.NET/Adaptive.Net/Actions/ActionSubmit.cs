using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{

    /// <summary>
    /// Submit action gathers up input fields, merges with optional data field and generates event to client asking for data to be submitted. It is up to the client to determine how that data is processed. For example: With BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
    public partial class ActionSubmit : ActionBase
    {
        public ActionSubmit()
        {

        }

        /// <summary>
        /// initial data that input fields will be combined with. This is essentially 'hidden' properties, Example: {"id":"123123123"}
        /// </summary>
        [XmlIgnore]
        public object Data { get; set; }
    }
}
