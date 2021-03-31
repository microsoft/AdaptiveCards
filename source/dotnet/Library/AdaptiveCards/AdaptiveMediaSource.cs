// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Represents one "media source" in a Media element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType(TypeName = "MediaSource")]
#endif
    public class AdaptiveMediaSource
    {
        public AdaptiveMediaSource()
        { }

        public AdaptiveMediaSource(string mimeType, string url)
        {
            MimeType = mimeType;
            Url = url;
        }

        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string MimeType { get; set; }

        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Url { get; set; }
    }
}
