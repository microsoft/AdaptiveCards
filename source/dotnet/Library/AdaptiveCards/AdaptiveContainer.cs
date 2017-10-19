using System.Collections.Generic;
using Newtonsoft.Json;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class AdaptiveContainer : AdaptiveElement
    {
        public const string TypeName = "Container";

        public AdaptiveContainer()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Elements of the container
        /// </summary>
        [JsonRequired]
        public List<AdaptiveElement> Items { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveActionBase SelectAction { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveContainerStyle Style { get; set; }
    }

    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
    {
        /// <summary>
        /// The container is a default container
        /// </summary>
        Default = 0,

        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 0,

        /// <summary>
        /// The container should be emphasized as a grouping of elements
        /// </summary>
        Emphasis = 1
    }
}