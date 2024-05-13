// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the ActionSet element.
    /// </summary>
    [XmlType(TypeName = AdaptiveActionSet.TypeName)]
    public class AdaptiveActionSet : AdaptiveElement
    {
        /// <summary>
        /// The AdaptiveCard element that this class implements.
        /// </summary>
        public const string TypeName = "ActionSet";

        /// <summary>
        /// The JSON property name that this class implements.
        /// </summary>
        [XmlIgnore]
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// The actions contained within this ActionSet.
        /// </summary>
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveAction>))]
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveExecuteAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();
    }
}
