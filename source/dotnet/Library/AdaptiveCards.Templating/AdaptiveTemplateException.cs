// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards.Templating
{
    /// <summary>
    /// AdaptiveCardTemplate Library's Exception class
    /// </summary>
    public class AdaptiveTemplateException : Exception
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public AdaptiveTemplateException()
        {
        }

        /// <summary>
        /// Constructor that takes single argument that is exception message
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception</param>
        public AdaptiveTemplateException(string message) : base(message)
        {
        }

        /// <summary>
        /// Constructor that takes message and inner exception to pass
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception</param>
        /// <param name="innerException">The exception that is the cause of the current exception</param>
        public AdaptiveTemplateException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
