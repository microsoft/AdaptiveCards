// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Data.Query data structure for filtered choicesets.
    /// </summary>
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
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        /// Populates the suggested page size or number of items to request
        /// </summary>
        [XmlAttribute]
        public int Count { get; set; }

        /// <summary>
        /// Populates the skip value for paging
        /// </summary>
        [XmlAttribute]
        public int Skip { get; set; }
    }
}
