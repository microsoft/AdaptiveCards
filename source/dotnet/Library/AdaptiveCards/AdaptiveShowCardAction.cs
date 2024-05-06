// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Action.ShowCard element.
    /// </summary>
    [XmlType(TypeName = AdaptiveShowCardAction.TypeName)]
    public class AdaptiveShowCardAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.ShowCard";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// <see cref="AdaptiveCard"/> to show when the action is invoked.
        /// </summary>
        [JsonProperty(Required = Required.Always)]
        [XmlElement(typeof(AdaptiveCard), ElementName = AdaptiveCard.TypeName)]
        public AdaptiveCard Card { get; set; }
    }
}
