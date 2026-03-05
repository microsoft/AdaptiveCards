// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
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
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Size for the column (either ColumnSize string or number which is relative size of the column).
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get; set; }

        /// <summary>
        /// Width for the column (either ColumnWidth string or number which is relative size of the column).
        /// </summary>
        [JsonConverter(typeof(AdaptiveWidthConverter))]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public AdaptiveWidth Width { get; set; }

    }
}
