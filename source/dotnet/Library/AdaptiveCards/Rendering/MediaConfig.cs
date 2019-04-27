// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of media
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class MediaConfig
    {
        /// <summary>
        /// Default poster URL to use for media thumbnail
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string DefaultPoster { get; set; }

        /// <summary>
        /// Play button URL to use for media thumbnail
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string PlayButton { get; set; }

        /// <summary>
        /// Controls whether the media is played in the card or sent to host
        /// </summary>
        public bool AllowInlinePlayback { get; set; } = true;
    }
}
