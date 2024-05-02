// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents how a card can be refreshed by making a request to the target Bot
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType(TypeName = "Refresh")]
#endif
    public class AdaptiveRefresh
    {
        /// <summary>
        ///    The action to be executed to refresh the card.
        ///    Clients can run this refresh action automatically or can provide an affordance for users to trigger it manually.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveExecuteAction))]
#endif
        public AdaptiveExecuteAction Action { get; set; }

        /// <summary>
        ///     A list of user Ids informing the client for which users should the refresh action should be run automatically.
        ///     Some clients will not run the refresh action automatically unless this property is specified.
        ///     Some clients may ignore this property and always run the refresh action automatically.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public List<string> UserIds { get; set; } = new List<string>();


        /// <summary>
        /// A timestamp that informs a Host when the card content has expired, and that it should trigger a refresh as appropriate. The format is ISO-8601 Instant format. E.g., 2022-01-01T12:00:00Z
        /// </summary>
        //[JsonConverter(typeof(IsoDateTimeConverter))]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public DateTime? Expires { get; set; }

#if !NETSTANDARD1_3
        [XmlAttribute]
        [JsonIgnore]
        public string ExpiresXml { get => Expires?.ToString("yyyy-MM-ddTHH:mm:ssZ", CultureInfo.InvariantCulture); set => Expires = DateTime.Parse(value); }
#endif
    }
}
