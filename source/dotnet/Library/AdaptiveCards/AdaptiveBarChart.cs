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
    ///     Adaptive card rendering chartdata as a bar chart.
    /// </summary>
    [JsonConverter(typeof(AdaptiveBarChart))]
#if !NETSTANDARD1_3
    [XmlRoot(ElementName = "BarChart")]
#endif
    public class AdaptiveBarChart : AdaptiveChart
    {
        public new const string TypeName = "BarChart";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Creates an AdaptiveCard using a specific schema version
        /// </summary>
        /// <param name="schemaVersion">The schema version to use</param>
        public AdaptiveBarChart()
        {
        }
    }
}
