// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Submit action gathers up input fields, merges with optional data field and generates event to client
    ///     asking for data to be submitted. It is up to the client to determine how that data is processed. For
    ///     example: With BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveSubmitAction.TypeName)]
#endif
    public class AdaptiveSubmitAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.Submit";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
        ///     {"id":"123123123"}
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public object Data { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Get or set the data as a JSON string.
        /// </summary>
        [JsonIgnore]
        [XmlText]
        [DefaultValue(null)]
        public string _Data
        {
            get => (Data != null) ? JsonConvert.SerializeObject(Data, Formatting.Indented) : null;
            set => Data = (value != null) ? JsonConvert.DeserializeObject(value, new JsonSerializerSettings { Converters = { new StrictIntConverter() } }) : null;
        }
#endif

        /// <summary>
        ///     Controls which inputs are associated with the submit action
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveAssociatedInputs), "auto")]
        public AdaptiveAssociatedInputs AssociatedInputs { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(AssociatedInputs))]
        [DefaultValue(null)]
        public string _AssociatedInputs
        {
            get => JToken.FromObject(AssociatedInputs).ToString();
            set => AssociatedInputs = (AdaptiveAssociatedInputs)Enum.Parse(typeof(AdaptiveAssociatedInputs), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_AssociatedInputs() => AssociatedInputs != AdaptiveAssociatedInputs.Auto;
#endif

    }
}
