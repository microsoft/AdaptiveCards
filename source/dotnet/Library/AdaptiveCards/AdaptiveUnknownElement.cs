// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an unknown element encountered while parsing.
    /// </summary>
    public class AdaptiveUnknownElement : AdaptiveElement
    {
        /// <inheritdoc />
        public override string Type { get; set; }
    }

    /// <summary>
    /// Represents an unknown action encountered while parsing.
    /// </summary>
    public class AdaptiveUnknownAction : AdaptiveAction
    {
        /// <inheritdoc />
        public override string Type { get; set; }
    }
}
