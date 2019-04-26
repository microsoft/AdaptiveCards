using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    public class AdaptiveInternalID
    {
        public static uint Invalid = 0;
        private static uint CurrentInternalID = 1;
        private uint ID { get; }

        public AdaptiveInternalID()
        {
            ID = Invalid;
        }

        private AdaptiveInternalID(uint id)
        {
            ID = id;
        }

        public static AdaptiveInternalID Current()
        {
            return new AdaptiveInternalID(CurrentInternalID);
        }

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

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }

            return ((AdaptiveInternalID)obj).ID == this.ID;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override string ToString()
        {
            return ID.ToString();
        }
    }

    public class AdaptiveFallbackElement
    {
        public static readonly string drop = "drop";

        public enum AdaptiveFallbackType
        {
            None,
            Drop,
            Content
        }

        public AdaptiveFallbackElement(AdaptiveFallbackType type)
        {
            Type = type;
            Content = null;
        }

        public AdaptiveFallbackElement(AdaptiveTypedElement elem)
        {
            Type = AdaptiveFallbackType.Content;
            Content = elem;
        }

        public AdaptiveFallbackElement()
        {
            Type = AdaptiveFallbackType.None;
        }

        [JsonIgnore]
        public AdaptiveFallbackType Type { get; set; }

        [JsonIgnore]
        public AdaptiveTypedElement Content { get; set; }
    }
}
