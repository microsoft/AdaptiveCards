// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTargetElement
    {
        public AdaptiveTargetElement() { }

        public AdaptiveTargetElement(string elementId)
        {
            ElementId = elementId;
        }

        public AdaptiveTargetElement(string elementId, bool isVisible)
        {
            ElementId = elementId;
            IsVisible = isVisible;
        }

        /// <summary>
        ///     Identifier of element to change visibility.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public string ElementId { get; set; }

        /// <summary>
        ///     Value to change visibility to.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public bool? IsVisible { get; set; } = null;

        /// <summary>
        /// Implicit conversion from <see cref="string"/> to <see cref="AdaptiveTargetElement"/>.
        /// </summary>
        /// <param name="elementId"></param>
        public static implicit operator AdaptiveTargetElement(string elementId)
        {
            return new AdaptiveTargetElement(elementId);
        }
    }
}
