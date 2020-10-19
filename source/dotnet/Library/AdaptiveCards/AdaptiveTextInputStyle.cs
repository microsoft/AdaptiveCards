// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    /// Style of text input.
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveTextInputStyle
    {
        /// <summary>
        /// Unstructured plain text.
        /// </summary>
        Text,

        /// <summary>
        /// Input is a telephone number. The client may use this information to provide optimized keyboard input for the
        /// user.
        /// </summary>
        Tel,

        /// <summary>
        /// Input is a url. The client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Url,

        /// <summary>
        /// Input is an email address. The client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Email
    }
}
