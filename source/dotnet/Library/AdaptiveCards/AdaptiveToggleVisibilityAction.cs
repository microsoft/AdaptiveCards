// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Toggle visibility action changes the visibility for the specified elements. You can also specify
    ///     the visibility of a certain element to a set value instead of toggling it.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveToggleVisibilityAction.TypeName)]
#endif
    public class AdaptiveToggleVisibilityAction : AdaptiveAction
    {
        public const string TypeName = "Action.ToggleVisibility";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Identifiers of elements to change visibility. Example: "id1" or { "elementId": "id2", "isVisible": true }
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonConverter(typeof(ToggleElementsConverter))]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        public List<AdaptiveTargetElement> TargetElements { get; set; } = new List<AdaptiveTargetElement>();
    }
}
