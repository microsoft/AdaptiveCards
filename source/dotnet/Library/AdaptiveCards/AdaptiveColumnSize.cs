// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the horizontal size (width) of Column.
    /// </summary>
    [Obsolete("ColumnSize has been deprecated.  Use ColumnWidth", false)]
    public class AdaptiveColumnSize
    {
        /// <summary>
        ///     The width of the Column is optimally chosen depending on the space available in the element's container
        /// </summary>
        public const string Auto = "Auto";

        /// <summary>
        ///     The width of the Column adjusts to match that of its container
        /// </summary>
        public const string Stretch = "Stretch";
    }
}
