// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// Encapsulates state necessary to correctly parse an AdaptiveCard.
    /// </summary>
    public class ParseContext
    {
        /// <summary>
        /// Denotes what type of AdaptiveCard element this ParseContext represents.
        /// </summary>
        public enum ContextType
        {
            /// <summary>
            /// Represents an Element (i.e. something that belongs in the body of a card).
            /// </summary>
            Element,

            /// <summary>
            /// Represents an Action (i.e. something that belongs in an ActionSet or in the actions of a card).
            /// </summary>
            Action
        };

        /// <summary>
        /// Tracks the most recently encountered element type.
        /// </summary>
        public ContextType Type { get; set; }

        private IDictionary<string, List<AdaptiveInternalID>> elementIds = new Dictionary<string, List<AdaptiveInternalID>>();

        private Stack<Tuple<string, AdaptiveInternalID, bool>> idStack = new Stack<Tuple<string, AdaptiveInternalID, bool>>();

        /// <summary>
        /// Pushes the supplied element state on to the context stack.
        /// </summary>
        /// <remarks>Used by element converters to determine how to perform element fallback.</remarks>
        /// <param name="idJsonProperty">The value of the current element's "id" property.</param>
        /// <param name="internalId">The current element's <see cref="AdaptiveInternalID"/>.</param>
        public void PushElement(string idJsonProperty, AdaptiveInternalID internalId)
        {
            if (internalId.Equals(AdaptiveInternalID.Invalid))
            {
                throw new AdaptiveSerializationException($"Attemping to push an element on to the stack with an invalid ID");
            }
            idStack.Push(new Tuple<string, AdaptiveInternalID, bool>(idJsonProperty, internalId, AdaptiveFallbackConverter.IsInFallback));
        }

        /// <summary>
        /// Pops an element off of the context stack.
        /// </summary>
        public void PopElement()
        {
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
                        haveCollision = true;
                    }
                }

                if (haveCollision)
                {
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
        }

        /// <summary>
        /// Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to
        /// skip), then return its internal ID. If none, return an invalid ID.
        /// </summary>
        /// <param name="skipID"><see cref="AdaptiveInternalID"/> of the element to ignore.</param>
        /// <returns>
        /// The <see cref="AdaptiveInternalID"/> of the nearest element with fallback, or an invalid <see
        /// cref="AdaptiveInternalID"/> if there is no element with fallback.
        /// </returns>
        public AdaptiveInternalID GetNearestFallbackID(AdaptiveInternalID skipID)
        {
            foreach (var curElement in idStack)
            {
                // if element is fallback
                if (curElement.Item3)
                {
                    if (!curElement.Item2.Equals(skipID))
                    {
                        return curElement.Item2;
                    }
                }
            }

            var invalidID = new AdaptiveInternalID();
            return invalidID;
        }
    }
}
