// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCardVisualizer.Helpers
{
    public static class IListExtensions
    {
        public static bool MakeListLike<T>(this IList<T> list, IList<T> desired)
        {
            // If already equal, do nothing
            if (desired.SequenceEqual(list))
                return false;

            // Remove any of the items that aren't there anymore
            for (int i = 0; i < list.Count; i++)
            {
                if (!desired.Contains(list[i]))
                {
                    list.RemoveAt(i);
                    i--;
                }
            }

            for (int i = 0; i < desired.Count; i++)
            {
                if (i >= list.Count)
                    list.Add(desired[i]);

                // There's a wrong item in its place
                else if (!object.Equals(list[i], desired[i]))
                {
                    // If it's already in the list somewhere, we remove it
                    list.Remove(desired[i]);

                    // No matter what we insert it into its desired spot
                    list.Insert(i, desired[i]);
                }

                // Otherwise it's already in the right place!
            }

            return true;
        }
    }
}
