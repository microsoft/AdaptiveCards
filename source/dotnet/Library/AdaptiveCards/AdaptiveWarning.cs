// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards
{
    // TODO: decide if standard error codes are useful or if this should just be string

    /// <summary>
    /// Represents a warning generated while parsing.
    /// </summary>
    public class AdaptiveWarning
    {
        // TODO #2749: temporary warning code for fallback card. Remove when common set of error codes created and integrated.

        /// <summary>
        /// Status code representing the type of warning encountered.
        /// </summary>
        public enum WarningStatusCode
        {
            /// <summary>
            /// The supplied schema version wasn't recognized.
            /// </summary>
            UnsupportedSchemaVersion = 7,

            /// <summary>
            /// The supplied language was not valid.
            /// </summary>
            InvalidLanguage = 12,

            /// <summary>
            /// The maximum number of <see cref="AdaptiveAction"/>s was exceeded.
            /// </summary>
            MaxActionsExceeded = 13,

            /// <summary>
            /// An input was marked as requiring input, but didn't have a label.
            /// </summary>
            EmptyLabelInRequiredInput = 14
        };

        /// <summary>
        /// Initializes an <see cref="AdaptiveWarning"/> instance with the given properties.
        /// </summary>
        /// <param name="code">The <see cref="WarningStatusCode"/> encountered.</param>
        /// <param name="message">The warning message.</param>
        public AdaptiveWarning(int code, string message)
        {
            Code = code;
            Message = message;
        }

        /// <summary>
        /// The <see cref="WarningStatusCode"/>.
        /// </summary>
        public int Code { get; set; }

        /// <summary>
        /// The warning message.
        /// </summary>
        public string Message { get; set; }
    }
}
