// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// System.Text.Json converters that deserialize to AdaptiveCards elements and use ParseContext must inherit this class.
    /// ParseContext provides id generation, id collision detections, and other useful services during deserialization.
    /// </summary>
    public abstract class AdaptiveTypedBaseElementSystemTextJsonConverter<T> : JsonConverter<T>
    {
        /// <summary>
        /// The <see cref="ParseContext"/> to use while parsing in AdaptiveCards.
        /// </summary>
        public ParseContext ParseContext { get; set; } = new ParseContext();
    }
}