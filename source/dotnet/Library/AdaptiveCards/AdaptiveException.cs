// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    public class AdaptiveException : Exception
    {
        public AdaptiveException()
        {
        }

        public AdaptiveException(string message) : base(message)
        {
        }

        public AdaptiveException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
