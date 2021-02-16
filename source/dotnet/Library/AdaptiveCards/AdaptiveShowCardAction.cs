// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Action.ShowCard element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveShowCardAction.TypeName)]
#endif
    public class AdaptiveShowCardAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.ShowCard";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// <see cref="AdaptiveCard"/> to show when the action is invoked.
        /// </summary>
        [JsonProperty(Required = Required.Always)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveCard), ElementName = AdaptiveCard.TypeName)]
#endif
        public AdaptiveCard Card { get; set; }
    }
}
