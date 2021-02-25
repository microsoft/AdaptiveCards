// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Action.ToggleVisibility element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveToggleVisibilityAction.TypeName)]
#endif
    public class AdaptiveToggleVisibilityAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.ToggleVisibility";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Ids of elements whose visibility this element should change.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonConverter(typeof(ToggleElementsConverter))]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        public List<AdaptiveTargetElement> TargetElements { get; set; } = new List<AdaptiveTargetElement>();
    }
}
