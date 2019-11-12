// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// JsonConverters that deserialize to Adpative Elements and require
    /// ParseContext must inherit this Class
    /// ParseContext provides id generation, id collision detections, and other useful
    /// services during deserialization
    /// </summary>
    public abstract class AdaptiveTypedBaseElementConverter : JsonConverter
    {
        public ParseContext ParseContext { get; set; } = new ParseContext();
    }
}
