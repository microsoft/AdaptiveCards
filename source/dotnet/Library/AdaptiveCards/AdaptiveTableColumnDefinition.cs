// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;
using System;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the backgroundImage property
    /// </summary>
    [XmlType(TypeName = AdaptiveTableColumnDefinition.TypeName)]
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTableColumnDefinition
    {
        /// <summary>
        /// The JSON property name that this class implements.
        /// </summary>
        public const string TypeName = "TableColumnDefinition";

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty("verticalCellContentAlignment", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty("horizontalCellContentAlignment", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveHorizontalContentAlignment), "left")]
        public AdaptiveHorizontalContentAlignment HorizontalContentAlignment { get; set; }

        [JsonConverter(typeof(TableColumnWidthConverter))]
        [JsonProperty("width", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(0)]
        private TableColumnWidth TableColumnWidth { get; set; } = new TableColumnWidth();

        /// <summary>
        /// Ths width in pixels
        /// </summary>
        [JsonIgnore]
        public double PixelWidth
        {
            get { return TableColumnWidth.PixelWidth; }
            set { TableColumnWidth.PixelWidth = value; }
        }

        /// <summary>
        /// Ths relative width as a weight
        /// </summary>
        [JsonIgnore]
        public double Width
        {
            get { return TableColumnWidth.RelativeWidth; }
            set { TableColumnWidth.RelativeWidth = value; }
        }
    }

    internal class TableColumnWidth
    {
        private double _pixel;
        private double _relative;

        internal TableColumnWidth()
        {
        }



        internal double PixelWidth
        {
            get => _pixel;
            set
            {
                _pixel = value;
                _relative = 0;
            }
        }

        internal double RelativeWidth
        {
            get => _relative;
            set
            {
                _relative = value;
                _pixel = 0;
            }
        }
    }
}
