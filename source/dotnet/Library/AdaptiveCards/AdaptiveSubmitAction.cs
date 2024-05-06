// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Submit action gathers up input fields, merges with optional data field and generates event to client
    ///     asking for data to be submitted. It is up to the client to determine how that data is processed. For
    ///     example: With BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
    [XmlType(TypeName = AdaptiveSubmitAction.TypeName)]
    public class AdaptiveSubmitAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.Submit";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
        ///     {"id":"123123123"}
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlIgnore]
        public object Data { get; set; }

        /// <summary>
        ///     Controls which inputs are associated with the submit action
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveAssociatedInputs), "auto")]
        public AdaptiveAssociatedInputs AssociatedInputs { get; set; }

        /// <summary>
        /// Get or set the data as a JSON string.
        /// </summary>
        [JsonIgnore]
        [XmlText]
        public string DataJson
        {
            get
            {
                if (Data != null)
                {
                    return JsonConvert.SerializeObject(Data, Formatting.Indented);
                }
                else
                {
                    return null;
                }
            }
            set
            {
                if (value == null)
                {
                    Data = null;
                }
                else
                {
                    Data = JsonConvert.DeserializeObject(value, new JsonSerializerSettings
                    {
                        Converters = { new StrictIntConverter() }
                    });
                }
            }
        }
    }
}
