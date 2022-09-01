// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
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
        /// The width as a string
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Width { get; set; }

    }
}
