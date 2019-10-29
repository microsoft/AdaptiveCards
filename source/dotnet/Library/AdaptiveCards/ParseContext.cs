// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace AdaptiveCards
{
    static class ParseContext
    {
        public static void Initialize()
        {
            elementIds = new Dictionary<string, List<AdaptiveInternalID>>();
            idStack = new Stack<Tuple<string, AdaptiveInternalID, bool>>();
        }

        public enum ContextType { Element, Action };

        public static ContextType Type { get; set; }

        private static IDictionary<string, List<AdaptiveInternalID>> elementIds = new Dictionary<string, List<AdaptiveInternalID>>();

        private static Stack<Tuple<string, AdaptiveInternalID, bool>> idStack = new Stack<Tuple<string, AdaptiveInternalID, bool>>();

        // Push the provided state on to our ID stack
        public static void PushElement(string idJsonProperty, AdaptiveInternalID internalId)
        {
        }

        public static AdaptiveInternalID PeekElement()
        {
            return new AdaptiveInternalID();
        }

        // Pop the last id off our stack and perform validation 
        public static void PopElement()
        {
        }

        // Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to skip), then
        // return its internal ID. If none, return an invalid ID. (see comment above)
        public static AdaptiveInternalID GetNearestFallbackID(AdaptiveInternalID skipID)
        {
            return new AdaptiveInternalID();
        }
    }
}
