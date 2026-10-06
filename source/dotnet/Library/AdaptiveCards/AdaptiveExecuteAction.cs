// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json;
using System.Text.Json.Serialization;
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
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlIgnore]
        public object Data { get; set; }

        /// <summary>
        ///     Controls which inputs are associated with the execute action
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveAssociatedInputs), "auto")]
        public AdaptiveAssociatedInputs AssociatedInputs { get; set; }


        /// <summary>
        ///     The card author-defined verb associated with this action.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
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
                    return JsonSerializer.Serialize(Data, new JsonSerializerOptions { WriteIndented = true });
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
                    Data = JsonSerializer.Deserialize<object>(value, new JsonSerializerOptions
                    {
                        Converters = { new StrictIntConverter() }
                    });
                }
            }
        }
    }
}
