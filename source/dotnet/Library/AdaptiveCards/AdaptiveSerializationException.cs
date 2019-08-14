// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    public class AdaptiveSerializationException : AdaptiveException
    {
        public AdaptiveSerializationException()
        {
        }

        public AdaptiveSerializationException(string message) : base(message)
        {
        }

        public AdaptiveSerializationException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
