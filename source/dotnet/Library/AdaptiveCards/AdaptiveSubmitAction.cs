using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Submit action gathers up input fields, merges with optional data field and generates event to client asking for
    ///     data to be submitted. It is up to the client to determine how that data is processed. For example: With
    ///     BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
    public class AdaptiveSubmitAction : AdaptiveAction
    {
        public const string TypeName = "Action.Submit";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
        ///     {"id":"123123123"}
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public object Data { get; set; }

        [JsonIgnore]
        public string DataJson
        {
            get
            {
                if (Data != null)
                    return JsonConvert.SerializeObject(Data, Formatting.Indented);
                return null;
            }
            set
            {
                if (value == null)
                    Data = null;
                else
                    Data = JsonConvert.DeserializeObject(value);
            }
        }
    }
}