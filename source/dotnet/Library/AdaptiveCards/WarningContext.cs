// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards
{
    /// <summary>
    /// Provides an ambient context for sharing warnings during deserialization.
    /// Converters instantiated via [JsonConverter] attributes create their own
    /// warning lists. This context allows them to contribute warnings back to
    /// the shared parse result warnings list.
    /// </summary>
    internal static class WarningContext
    {
        [System.ThreadStatic]
        private static List<AdaptiveWarning> _current;

        /// <summary>
        /// Gets or sets the shared warnings list for the current deserialization operation.
        /// </summary>
        internal static List<AdaptiveWarning> Current
        {
            get => _current;
            set => _current = value;
        }

        /// <summary>
        /// Adds a warning to the shared context (if active) or to the provided fallback list.
        /// </summary>
        internal static void AddWarning(List<AdaptiveWarning> fallback, AdaptiveWarning warning)
        {
            var target = _current ?? fallback;
            target?.Add(warning);
        }
    }
}
