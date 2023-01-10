// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType(TypeName = TypeName)]
#endif
    public class AdaptiveTableColumn
    {
        /// <inheritdoc />
        public const string TypeName = "TableColumn";

        /// <summary>
        /// Initializes an empty Fact.
        /// </summary>
        public AdaptiveTableColumn()
        { }

        /// <summary>
        /// Define the column properties.
        /// </summary>
        /// <param name="width">The width of the column either as proportion (number) or px (numberpx)</param>
        public AdaptiveTableColumn(string width)
        {
            Width = width;
        }

        /// <summary>
        /// Width for the column (either ColumnWidth string or number which is relative size of the column).
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public AdaptiveColumnWidth Width { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Xml Serialization for complex type of AdaptiveColumnWidth
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Width))]
        public string _Width { get => Width?.ToString(); set => this.Width = new AdaptiveColumnWidth(value); }

        /// <summary>
        /// Controls serialization 
        /// </summary>
        /// <returns></returns>
        public bool ShouldSerialize_Width() => Width != null;
#endif
    }
}
