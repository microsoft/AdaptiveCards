// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a unique identifier.
    /// </summary>
    public class AdaptiveInternalID
    {
        /// <summary>
        /// Value representing an invalid (or unset) AdaptiveInternalID
        /// </summary>
        public static readonly int Invalid = 0;

        private static int CurrentInternalID = 1;
        private int ID { get; }

        /// <summary>
        /// Initializes an invalid AdaptiveInternalID
        /// </summary>
        public AdaptiveInternalID()
        {
            ID = Invalid;
        }

        /// <summary>
        /// Initializes an AdaptiveInternalID with the supplied <paramref name="id"/>.
        /// </summary>
        /// <param name="id">The id with which to initialize.</param>
        private AdaptiveInternalID(int id)
        {
            ID = id;
        }

        /// <summary>
        /// Retrieves the current AdaptiveInternalID
        /// </summary>
        public static AdaptiveInternalID Current()
        {
            return new AdaptiveInternalID(CurrentInternalID);
        }

        /// <summary>
        /// Advances to the next AdaptiveInternalID.
        /// </summary>
        /// <returns>The next AdaptiveInternalID.</returns>
        public static AdaptiveInternalID Next()
        {
            try
            {
                CurrentInternalID++;
            }
            catch (System.OverflowException)
            {
                CurrentInternalID = 1;
            }

            return Current();
        }

        ///<inheritdoc cref="Object.Equals(object)"/>
        public override bool Equals(object obj)
        {
            if (obj == null || !(obj is AdaptiveInternalID))
            {
                return false;
            }

            return ((AdaptiveInternalID)obj).ID == this.ID;
        }

        ///<inheritdoc cref="Object.GetHashCode"/>
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        ///<inheritdoc cref="Object.ToString"/>
        public override string ToString()
        {
            return ID.ToString();
        }
    }
}
