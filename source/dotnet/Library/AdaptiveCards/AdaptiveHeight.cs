// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the vertical size (height) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHeightType>), true)]

    public enum AdaptiveHeightType
    {
        /// <summary>
        ///     The height of the element is wraps the element content
        /// </summary>
        Auto,

        /// <summary>
        ///     The height of the element uses as much space as it is able to
        /// </summary>
        Stretch,

        /// <summary>
        ///     The height of the element was explicitly specified (only for Image elements)
        /// </summary>
        Pixel
    }


    public struct AdaptiveHeight
    {
        public static AdaptiveHeight Auto { get; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        public static AdaptiveHeight Stretch { get; } = new AdaptiveHeight(AdaptiveHeightType.Stretch);

        public AdaptiveHeightType _heightType;
        public AdaptiveHeightType HeightType { get { return _heightType; } set { } }

        public uint? _unit;
        public uint? Unit { get { return _unit; } set { } }

        public AdaptiveHeight(uint px)
        {
            _heightType = AdaptiveHeightType.Pixel;
            _unit = px;
        }

        public AdaptiveHeight(AdaptiveHeightType heightType)
        {
            _heightType = heightType;
            _unit = null;
        }

        public bool IsPixel()
        {
            return HeightType == AdaptiveHeightType.Pixel;
        }

        public bool ShouldSerializeAdaptiveHeight()
        {
            if (HeightType == AdaptiveHeightType.Auto)
            {
                return false;
            }
            if( HeightType == AdaptiveHeightType.Pixel )
            {
                if (!Unit.HasValue)
                {
                    return false;
                }
                else if (Unit.Value == 0)
                {
                    return false;
                }
            }
            return true;
        }

        public static bool operator ==(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            if (ah1 != null && ah2 != null)
            {
                return ah1.Equals(ah2);
            }

            if (ah1 == null && ah2 == null)
            {
                return true;
            }
            return false;
        }

        public static bool operator !=(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            return !(ah1 == ah2);
        }

        public override int GetHashCode()
        {
            if (!Unit.HasValue)
            {
                return -1;
            }
            return (int)(Unit.Value * 10 + (int)HeightType);
        }

        public override bool Equals(object obj)
        {
            if (obj is AdaptiveHeight)
            {
                AdaptiveHeight ah = (AdaptiveHeight)obj;
                if (HeightType == ah.HeightType)
                {
                    if (HeightType == AdaptiveHeightType.Pixel)
                    {
                        return Unit == ah.Unit;
                    }
                    return true;
                }
            }
            return false;
        }
    }
}
