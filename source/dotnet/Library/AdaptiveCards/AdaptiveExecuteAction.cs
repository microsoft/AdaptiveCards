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
    ///     Execute action gathers up input fields, merges with optional data field and generates event to client
    ///     asking for data to be submitted. 
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveExecuteAction.TypeName)]
#endif
    public class AdaptiveExecuteAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.Execute";

        /// <inheritdoc />
        [JsonProperty(Order = -10, DefaultValueHandling = DefaultValueHandling.Include)]
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
        [DefaultValue(null)]
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
        ///     Controls which inputs are associated with the execute action
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

        /// <summary>
        ///     The card author-defined verb associated with this action.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Verb { get; set; }
    }
}
