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

        private static Mutex mut = new Mutex();
        public enum ContextType { Element, Action };

        public static ContextType Type { get; set; }

        private static IDictionary<string, List<AdaptiveInternalID>> elementIds = new Dictionary<string, List<AdaptiveInternalID>>();

        private static Stack<Tuple<string, AdaptiveInternalID, bool>> idStack = new Stack<Tuple<string, AdaptiveInternalID, bool>>();

        // Push the provided state on to our ID stack
        public static void PushElement(string idJsonProperty, AdaptiveInternalID internalId)
        {
            mut.WaitOne();
            if (internalId.Equals(AdaptiveInternalID.Invalid))
            {
                mut.ReleaseMutex();
                throw new AdaptiveSerializationException($"Attemping to push an element on to the stack with an invalid ID");
            }
            idStack.Push(new Tuple<string, AdaptiveInternalID, bool>(idJsonProperty, internalId, AdaptiveFallbackConverter.IsInFallback));
            mut.ReleaseMutex();
        }

        public static AdaptiveInternalID PeekElement()
        {
            mut.WaitOne();
            if (idStack.Count == 0)
            {
                // internal id in dot net needs to be revisited tracked via issue 3386
                mut.ReleaseMutex();
                return new AdaptiveInternalID();
            }
            var id = idStack.Peek().Item2;
            mut.ReleaseMutex();
            return id;
        }

        // Pop the last id off our stack and perform validation 
        public static void PopElement()
        {
            mut.WaitOne();
            // about to pop an element off the stack. perform collision list maintenance and detection.
            var idsToPop = idStack.Peek();
            string elementID = idsToPop.Item1;
            AdaptiveInternalID elementInternalID = idsToPop.Item2;
            bool isFallback = idsToPop.Item3;

            if (!string.IsNullOrEmpty(elementID))
            {
                bool haveCollision = false;
                var nearestFallbackID = GetNearestFallbackID(elementInternalID);

                // Walk through the list of elements we've seen with this ID
                if (elementIds.ContainsKey(elementID))
                {
                    foreach (var entryFallBackID in elementIds[elementID])
                    {
                        // If the element we're about to pop is the fallback parent for this entry, then there's no collision
                        // (fallback content is allowed to have the same ID as its parent)
                        if (entryFallBackID.Equals(elementInternalID))
                        {
                            haveCollision = false;
                            break;
                        }

                        // The inverse of the above -- if this element's fallback parent is the entry we're looking at, there's
                        // no collision.
                        try
                        {
                            // 0 is the last item on the stack (the one we're about to pop)
                            // 1 is the parent of the last item on the stack
                            var previousInStack = idStack.ElementAt(1);

                            if (previousInStack.Item2.Equals(entryFallBackID))
                            {
                                // we're looking at a fallback entry for our parent
                                break;
                            }
                        }
                        catch (ArgumentOutOfRangeException)
                        {
                            // we're looking at a toplevel element
                        }

                        // if the element we're inspecting is fallback content, continue on to the next entry
                        if (isFallback)
                        {
                            continue;
                        }

                        // at this point, we may or may not have a collision depending on additional entries.
                        // haveCollision = true;
                    }
                }

                if (haveCollision)
                {
                    mut.ReleaseMutex();
                    throw new AdaptiveSerializationException("Collision detected for id '" + elementID + "'");
                }

                // add an entry for this element if it's fallback (we'll add one when we parse it for non-fallback)
                if (!isFallback)
                {
                    try
                    {
                        elementIds[elementID].Add(nearestFallbackID);
                    }
                    catch (KeyNotFoundException)
                    {
                        elementIds[elementID] = new List<AdaptiveInternalID>() { nearestFallbackID };
                    }
                }
            }
            idStack.Pop();
            mut.ReleaseMutex();
        }

        // Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to skip), then
        // return its internal ID. If none, return an invalid ID. (see comment above)
        public static AdaptiveInternalID GetNearestFallbackID(AdaptiveInternalID skipID)
        {
            mut.WaitOne();
            foreach (var curElement in idStack)
            {
                // if element is fallback
                if (curElement.Item3)
                {
                    if (!curElement.Item2.Equals(skipID))
                    {
                        mut.ReleaseMutex();
                        return curElement.Item2;
                    }
                }
            }
            var invalidID = new AdaptiveInternalID();
            mut.ReleaseMutex();
            return invalidID;
        }
    }
}
