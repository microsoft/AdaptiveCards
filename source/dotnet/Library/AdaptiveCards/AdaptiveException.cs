// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an exception thrown by Adaptive Cards itself.
    /// </summary>
    public class AdaptiveException : Exception
    {
        /// <inheritdoc />
        public AdaptiveException()
        {
        }

        /// <inheritdoc />
        public AdaptiveException(string message) : base(message)
        {
        }

        /// <inheritdoc />
        public AdaptiveException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
