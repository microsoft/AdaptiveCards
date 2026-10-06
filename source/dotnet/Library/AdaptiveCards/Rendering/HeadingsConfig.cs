// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Headings Config
    /// </summary>
    public class HeadingsConfig
    {
        /// <summary>
        /// Level of heading text, used only if underlying platform requires it.
        /// </summary>
        public int Level { get; set; } = 2;
    }
}
