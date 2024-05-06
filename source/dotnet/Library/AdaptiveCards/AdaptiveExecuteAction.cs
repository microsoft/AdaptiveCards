// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Execute action gathers up input fields, merges with optional data field and generates event to client
    ///     asking for data to be submitted. 
    /// </summary>
    [XmlType(TypeName = AdaptiveExecuteAction.TypeName)]
    public class AdaptiveExecuteAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.Execute";

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
        ///     Controls which inputs are associated with the execute action
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveAssociatedInputs), "auto")]
        public AdaptiveAssociatedInputs AssociatedInputs { get; set; }


        /// <summary>
        ///     The card author-defined verb associated with this action.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlAttribute]
        public string Verb { get; set; } = "";

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
