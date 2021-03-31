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
    ///     ActionSet
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveActionSet.TypeName)]
#endif
    public class AdaptiveActionSet : AdaptiveElement
    {
        public const string TypeName = "ActionSet";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Actions of the action set
        /// </summary>
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveAction>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
#endif
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();
    }
}
