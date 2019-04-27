// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveRenderException : AdaptiveException
    {
        public AdaptiveRenderException()
        {

        }

        public AdaptiveRenderException(string message) : base(message)
        {
        }

        public AdaptiveRenderException(string message, Exception innerException) : base(message, innerException)
        {
        }

        /// <summary>
        /// The fallback text associated with this card, if provided by the card author
        /// </summary>
        public string CardFallbackText { get; set; }
    }
}
