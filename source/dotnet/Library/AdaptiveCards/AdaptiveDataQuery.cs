// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Data.Query data structure for filtered choicesets.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [XmlType("Data.Query")]
    public class AdaptiveDataQuery
    {
        /// <summary>
        /// separator
        /// </summary>
        [JsonIgnore]
        public const char Separator = '#';

        /// <summary>
        /// Specifies that it's a Data.Query object.
        /// </summary>
        [JsonProperty]
        [XmlIgnore]
        public string Type { get; set; } = "Data.Query";

        /// <summary>
        /// Specifies the name of dataset that is fetched dynamically.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Dataset { get; set; }

        /// <summary>
        /// Populates the input 
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        /// Populates the suggested page size or number of items to request
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public int Count { get; set; }

        /// <summary>
        /// Populates the skip value for paging
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public int Skip { get; set; }
    }
}
