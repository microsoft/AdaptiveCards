// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an exception that occurs during serialization.
    /// </summary>
    public class AdaptiveSerializationException : AdaptiveException
    {
        /// <inheritdoc />
        public AdaptiveSerializationException()
        {
        }

        /// <inheritdoc />
        public AdaptiveSerializationException(string message) : base(message)
        {
        }

        /// <inheritdoc />
        public AdaptiveSerializationException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
