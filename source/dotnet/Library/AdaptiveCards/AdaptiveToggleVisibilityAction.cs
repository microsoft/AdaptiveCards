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
    [XmlType(TypeName = AdaptiveToggleVisibilityAction.TypeName)]
    public class AdaptiveToggleVisibilityAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.ToggleVisibility";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Ids of elements whose visibility this element should change.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonConverter(typeof(ToggleElementsConverter))]
        [XmlElement]
        public List<AdaptiveTargetElement> TargetElements { get; set; } = new List<AdaptiveTargetElement>();
    }
}
