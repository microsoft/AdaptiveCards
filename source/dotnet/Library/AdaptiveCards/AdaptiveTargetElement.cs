// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the target of an Action.ToggleVisibility element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTargetElement
    {
        /// <summary>
        /// Initializes an empty <see cref="AdaptiveTargetElement"/>.
        /// </summary>
        public AdaptiveTargetElement()
        {
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveTargetElement"/> instance with the supplied properties.
        /// </summary>
        /// <param name="elementId">The id of the target element.</param>
        public AdaptiveTargetElement(string elementId)
        {
            ElementId = elementId;
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveTargetElement"/> instance with the supplied properties.
        /// </summary>
        /// <param name="elementId">The Id of the target element.</param>
        /// <param name="isVisible">Initial visible state.</param>
        public AdaptiveTargetElement(string elementId, bool isVisible)
        {
            ElementId = elementId;
            IsVisible = isVisible;
        }

        /// <summary>
        /// Target element Id.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string ElementId { get; set; }

        /// <summary>
        /// Target element visibility.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public bool? IsVisible { get; set; } = null;

#if !NETSTANDARD1_3
        /// <summary>
        /// Helper to do custom serialization of <see cref="AdaptiveTargetElement.IsVisible"/> property for XML.
        /// </summary>
        [JsonIgnore]
        [XmlAttribute("IsVisible")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool IsVisibleXml { get { return IsVisible.HasValue ? IsVisible.Value : true; } set { IsVisible = value; } }

        /// <summary>
        /// Determines whether the <see cref="AdaptiveTargetElement.IsVisibleXml"/> property should be serialized.
        /// </summary>
        public bool ShouldSerializeIsVisibleXml() => this.IsVisible.HasValue;
#endif

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
