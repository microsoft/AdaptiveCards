// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;
using System.Text.Json.Serialization;
using System.ComponentModel;
using System.Collections.Generic;
using System.Collections;

namespace AdaptiveCards
{
    /// <summary>
    /// AdaptiveCard element with content alignment properties
    /// </summary>
    public abstract class AdaptiveCollectionWithContentAlignment : AdaptiveCollectionElement
    {

       
        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonPropertyName("verticalCellContentAlignment")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalCellContentAlignment { get; set; }

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonPropertyName("horizontalCellContentAlignment")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveHorizontalContentAlignment), "left")]
        public AdaptiveHorizontalContentAlignment HorizontalCellContentAlignment { get; set; }
    }
}
