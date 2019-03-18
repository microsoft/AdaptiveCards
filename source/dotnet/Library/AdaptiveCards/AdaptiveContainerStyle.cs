using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
    {
        None = 0,

        /// <summary>
        /// The container is a default container
        /// </summary>
        Default = 1,

        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 1,

        /// <summary>
        /// The container should be emphasized as a grouping of elements
        /// </summary>
        Emphasis = 2,

        Good = 3,
        Attention = 4,
        Warning = 5,
        Accent = 6
    }
}
