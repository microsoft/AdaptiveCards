// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the backgroundImage property
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTableColumnDefinition.TypeName)]
#endif
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
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty("horizontalCellContentAlignment", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalContentAlignment), "left")]
        public AdaptiveHorizontalContentAlignment HorizontalContentAlignment { get; set; }

        [JsonConverter(typeof(ColumnWidthConverter))]
        [JsonProperty("width", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        private TableColumnWidth TableColumnWidth { get; set; } = new TableColumnWidth();

        [JsonIgnore]
        public double PixelWidth {
            get { return TableColumnWidth.PixelWidth; }
            set { TableColumnWidth.PixelWidth = value;}
        }

        [JsonIgnore]
        public long Width
        {
            get { return TableColumnWidth.RelativeWidth; }
            set { TableColumnWidth.RelativeWidth = value;}
        }
    }
    public class TableColumnWidth
    {
        public TableColumnWidth()
        {
        }

        public TableColumnWidth(double pixelWidth)
        {
            PixelWidth = pixelWidth;
        }
        public TableColumnWidth(long relativeWidth)
        {
            RelativeWidth = relativeWidth;
        }

        public double PixelWidth { get; set; }
        public long RelativeWidth { get; set; }
    }
}
