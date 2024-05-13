// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Column element.
    /// </summary>
    [XmlType(TypeName = AdaptiveColumn.TypeName)]
    public class AdaptiveColumn : AdaptiveContainer
    {
        /// <inheritdoc />
        public new const string TypeName = "Column";

        /// <inheritdoc />
        [XmlIgnore]
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Size for the column (either ColumnSize string or number which is relative size of the column).
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get; set; }

        /// <summary>
        /// Width for the column (either ColumnWidth string or number which is relative size of the column).
        /// </summary>
        [JsonConverter(typeof(AdaptiveWidthConverter))]
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public AdaptiveWidth Width { get; set; }

    }
}
