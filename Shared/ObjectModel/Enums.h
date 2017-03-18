#pragma once

namespace AdaptiveCards
{
    enum class Size
    {
        Auto = 0,
        Stretch,
        Small,
        Medium,
        Large
    };

    enum class TextSize
    {
        Small = 0,
        Normal,
        Medium,
        Large,
        ExtraLarge
    };

    enum class TextWeight {
        Lighter = 0,
        Normal,
        Bolder
    };

    enum class TextColor {
        Default = 0,
        Dark,
        Light,
        Accent,
        Good,
        Warning,
        Attention
    };

    enum class HorizontalAlignment {
        Left = 0,
        Center,
        Right
    };

    enum class ImageStyle {
        Normal = 0,
        Person
    };
}

