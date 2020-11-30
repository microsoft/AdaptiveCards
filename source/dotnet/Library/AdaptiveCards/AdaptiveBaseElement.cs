// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

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
        public static readonly uint Invalid = 0;

        private static uint CurrentInternalID = 1;
        private uint ID { get; }

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
        private AdaptiveInternalID(uint id)
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

    /// <summary>
    /// Represents the fallback property.
    /// </summary>
    public class AdaptiveFallbackElement
    {
        /// <summary>
        /// String that represents "drop" fallback type
        /// </summary>
        public static readonly string drop = "drop";

        /// <summary>
        /// Enumeration describing an object's fallback type.
        /// </summary>
        public enum AdaptiveFallbackType
        {
            /// <summary>
            /// This object does not have fallback specified.
            /// </summary>
            None,

            /// <summary>
            /// Drop this element during fallback.
            /// </summary>
            Drop,

            /// <summary>
            /// This element has content to show in the event of fallback being triggered.
            /// </summary>
            Content
        }

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with the given <paramref name="fallbackType"/>.
        /// </summary>
        /// <param name="fallbackType">The type of fallback this instance represents.</param>
        public AdaptiveFallbackElement(AdaptiveFallbackType fallbackType)
        {
            Type = fallbackType;
            Content = null;
        }

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with the given <paramref name="fallbackContent"/>.
        /// </summary>
        /// <param name="fallbackContent">The content to show in the event of fallback.</param>
        public AdaptiveFallbackElement(AdaptiveTypedElement fallbackContent)
        {
            Type = AdaptiveFallbackType.Content;
            Content = fallbackContent;
        }

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with no fallback type.
        /// </summary>
        public AdaptiveFallbackElement()
        {
            Type = AdaptiveFallbackType.None;
        }

        /// <summary>
        /// Represents the type of fallback to perform.
        /// </summary>
        [JsonIgnore]
        public AdaptiveFallbackType Type { get; set; }

        /// <summary>
        /// The content to show in the event of fallback.
        /// </summary>
        [JsonIgnore]
        public AdaptiveTypedElement Content { get; set; }
    }
}
