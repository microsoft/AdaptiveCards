// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a cell within a row of a Table element.
    /// </summary>

#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTableCell.TypeName)]
#endif
    public class AdaptiveTableCell : AdaptiveContainer
    {
        /// <inheritdoc />
        public new const string TypeName = "TableCell";
    }
}
