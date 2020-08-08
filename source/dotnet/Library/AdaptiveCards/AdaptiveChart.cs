// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace AdaptiveCards
{

    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    [JsonConverter(typeof(AdaptiveChart))]
#if !NETSTANDARD1_3
    [XmlRoot(ElementName = "Chart")]
#endif
    public class AdaptiveChart : AdaptiveTypedElement
    {
        public new const string TypeName = "Chart";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Creates an AdaptiveCard using a specific schema version
        /// </summary>
        /// <param name="schemaVersion">The schema version to use</param>
        public AdaptiveChart()
        {
        }


        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Data")]
#endif
        [JsonProperty("Data")]
        public ChartData Data { get; set; }

        /// <summary>
        /// Options for the chart
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Options")]
#endif
        [JsonProperty("options")]
        public ChartOptions Options { get; set; }
    }
}
