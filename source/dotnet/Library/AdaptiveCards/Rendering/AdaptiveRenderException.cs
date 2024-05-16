// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Execption for adaptive renderer
    /// </summary>
    public class AdaptiveRenderException : AdaptiveException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public AdaptiveRenderException()
        {

        }

        /// <summary>
        /// Constructor with message
        /// </summary>
        /// <param name="message"></param>
        public AdaptiveRenderException(string message) : base(message)
        {
        }

        /// <summary>
        /// Constructor with message and inner exception
        /// </summary>
        /// <param name="message"></param>
        /// <param name="innerException"></param>
        public AdaptiveRenderException(string message, Exception innerException) : base(message, innerException)
        {
        }

        /// <summary>
        /// The fallback text associated with this card, if provided by the card author
        /// </summary>
        public string CardFallbackText { get; set; }
    }
}
