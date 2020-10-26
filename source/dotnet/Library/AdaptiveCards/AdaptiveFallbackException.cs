// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    /// <summary>
    /// An exception thrown while processing fallback.
    /// </summary>
    /// <remarks>
    /// This exception is intended to be caught and handled by an element that has a fallback action.
    /// </remarks>
    public class AdaptiveFallbackException: AdaptiveException
    {
        /// <inheritdoc />
        public AdaptiveFallbackException()
        {
        }

        /// <inheritdoc />
        public AdaptiveFallbackException(string message) : base(message)
        {
        }

        /// <inheritdoc />
        public AdaptiveFallbackException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
