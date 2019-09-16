// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveTextInputStyle
    {
        /// <summary>
        ///     plain text
        /// </summary>
        Text,

        /// <summary>
        ///     Input is a telephone number and the client may use this information to provide optimized keyboard input for the
        ///     user.
        /// </summary>
        Tel,

        /// <summary>
        ///     Input is a url and the client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Url,

        /// <summary>
        ///     Input is a email and the client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Email
    }
}
