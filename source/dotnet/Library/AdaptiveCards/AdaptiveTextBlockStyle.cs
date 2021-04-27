// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    ///     Indicates TextBlock element's content type.
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveTextBlockStyle
    {
        /// <summary>
        ///     The content is a paragraph (default).
        /// </summary>
        Paragraph = 0,

        /// <summary>
        ///     The content is a heading.
        /// </summary>
        Heading = 1,
    }
}
