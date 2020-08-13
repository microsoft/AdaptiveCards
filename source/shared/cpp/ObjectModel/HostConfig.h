// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class FontSizesConfig
    {
    public:
        FontSizesConfig() = default;
        FontSizesConfig(unsigned int s, unsigned int d, unsigned int m, unsigned int l, unsigned int xl) :
            _small(s), _default(d), _medium(m), _large(l), _extraLarge(xl)
        {
        }

        static FontSizesConfig Deserialize(const Json::Value& json, const FontSizesConfig& defaultValue);
        static unsigned int GetDefaultFontSize(TextSize size);
        unsigned int GetFontSize(TextSize size) const;
        void SetFontSize(TextSize size, unsigned int value);

    private:
        // UINT_MAX used to check if value was defined
        unsigned int _small = UINT_MAX;
        unsigned int _default = UINT_MAX;
        unsigned int _medium = UINT_MAX;
        unsigned int _large = UINT_MAX;
        unsigned int _extraLarge = UINT_MAX;
    };

    class FontWeightsConfig
    {
    public:
        FontWeightsConfig() = default;
        FontWeightsConfig(unsigned int lighterWeight, unsigned int defaultWeight, unsigned int bolderWeight) :
            _lighter(lighterWeight), _default(defaultWeight), _bolder(bolderWeight)
        {
        }
        static FontWeightsConfig Deserialize(const Json::Value& json, const FontWeightsConfig& defaultValue);
        static unsigned int GetDefaultFontWeight(TextWeight weight);
        unsigned int GetFontWeight(TextWeight weight) const;
        void SetFontWeight(TextWeight weight, unsigned int value);

    private:
        // UINT_MAX used to check if value was defined
        unsigned int _lighter = UINT_MAX;
        unsigned int _default = UINT_MAX;
        unsigned int _bolder = UINT_MAX;
    };

    struct FontTypeDefinition
    {
        std::string fontFamily;
        FontSizesConfig fontSizes;
        FontWeightsConfig fontWeights;

        static FontTypeDefinition Deserialize(const Json::Value& json, const FontTypeDefinition& defaultValue);
    };

    struct FontTypesDefinition
    {
        FontTypeDefinition defaultFontType;
        FontTypeDefinition monospaceFontType;

        static FontTypesDefinition Deserialize(const Json::Value& json, const FontTypesDefinition& defaultValue);
    };

    struct HighlightColorConfig
    {
        std::string defaultColor;
        std::string subtleColor;

        static HighlightColorConfig Deserialize(const Json::Value& json, const HighlightColorConfig& defaultValue);
    };

    struct ColorConfig
    {
        std::string defaultColor;
        std::string subtleColor;

        HighlightColorConfig highlightColors;

        static ColorConfig Deserialize(const Json::Value& json, const ColorConfig& defaultValue);
    };

    // TODO: microsoft/AdaptiveCards#3460 each ColorConfig below needs a HighlightColorConfig initializer
#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif
    struct ColorsConfig
    {
        ColorConfig defaultColor = {"#FF000000", "#B2000000"};
        ColorConfig accent = {"#FF0000FF", "#B20000FF"};
        ColorConfig dark = {"#FF101010", "#B2101010"};
        ColorConfig light = {"#FFFFFFFF", "#B2FFFFFF"};
        ColorConfig good = {"#FF008000", "#B2008000"};
        ColorConfig warning = {"#FFFFD700", "#B2FFD700"};
        ColorConfig attention = {"#FF8B0000", "#B28B0000"};

        static ColorsConfig Deserialize(const Json::Value& json, const ColorsConfig& defaultValue);
    };
#ifdef __clang__
    #pragma clang diagnostic pop
#endif

    struct TextConfig
    {
        TextWeight weight = TextWeight::Default;
        TextSize size = TextSize::Default;
        FontType fontType = FontType::Default;
        ForegroundColor color = ForegroundColor::Default;
        bool isSubtle = false;
        bool wrap = true;
        unsigned int maxWidth = ~0U;

        static TextConfig Deserialize(const Json::Value& json, const TextConfig& defaultValue);
    };

    struct SpacingConfig
    {
        unsigned int smallSpacing = 3;
        unsigned int defaultSpacing = 8;
        unsigned int mediumSpacing = 20;
        unsigned int largeSpacing = 30;
        unsigned int extraLargeSpacing = 40;
        unsigned int paddingSpacing = 20;

        static SpacingConfig Deserialize(const Json::Value& json, const SpacingConfig& defaultValue);
    };

    struct SeparatorConfig
    {
        unsigned int lineThickness = 1;
        std::string lineColor = "#B2000000";

        static SeparatorConfig Deserialize(const Json::Value& json, const SeparatorConfig& defaultValue);
    };

    struct ImageSizesConfig
    {
        unsigned int smallSize = 80;
        unsigned int mediumSize = 120;
        unsigned int largeSize = 180;

        static ImageSizesConfig Deserialize(const Json::Value& json, const ImageSizesConfig& defaultValue);
    };

    struct ImageSetConfig
    {
        ImageSize imageSize = ImageSize::Auto;
        unsigned int maxImageHeight = 100;

        static ImageSetConfig Deserialize(const Json::Value& json, const ImageSetConfig& defaultValue);
    };

    struct ImageConfig
    {
        ImageSize imageSize = ImageSize::Auto;

        static ImageConfig Deserialize(const Json::Value& json, const ImageConfig& defaultValue);
    };

    struct AdaptiveCardConfig
    {
        bool allowCustomStyle = true;

        static AdaptiveCardConfig Deserialize(const Json::Value& json, const AdaptiveCardConfig& defaultValue);
    };

    struct FactSetConfig
    {
        TextConfig title{TextWeight::Bolder, TextSize::Default, FontType::Default, ForegroundColor::Default, false, true, 150};
        TextConfig value{TextWeight::Default, TextSize::Default, FontType::Default, ForegroundColor::Default, false, true, ~0U};
        unsigned int spacing = 10;

        static FactSetConfig Deserialize(const Json::Value& json, const FactSetConfig& defaultValue);
    };

    struct ContainerStyleDefinition
    {
        std::string backgroundColor = "#FFFFFFFF";
        std::string borderColor = "#FF7F7F7F7F"; // CAUTION: Experimental feature for iOS. Not in v1 schema, subject to change.
        unsigned int borderThickness = 0; // CAUTION: Experimental feature for iOS. Not in v1 schema, subject to change.
        ColorsConfig foregroundColors;

        static ContainerStyleDefinition Deserialize(const Json::Value& json, const ContainerStyleDefinition& defaultValue);
    };

    struct ContainerStylesDefinition
    {
        ContainerStyleDefinition defaultPalette = {"#FFFFFFFF",
                                                   "#FF7F7F7F7F",
                                                   0,
                                                   {
                                                       // Foreground Colors
                                                       {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                                                       {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                                                       {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                                                       {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                                                       {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                                                       {"#FFFFD700", "#B2FFD700", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                                                       {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}} // attention
                                                   }};
        ContainerStyleDefinition emphasisPalette = {"#08000000",
                                                    "#08000000",
                                                    0,
                                                    {
                                                        // Foreground Colors
                                                        {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                                                        {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                                                        {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                                                        {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                                                        {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                                                        {"#FFFFD700", "#B2FFD700", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                                                        {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}} // attention
                                                    }};
        ContainerStyleDefinition goodPalette = {"#FFD5F0DD",
                                                "#FF7F7F7F7F",
                                                0,
                                                {
                                                    // Foreground Colors
                                                    {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                                                    {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                                                    {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                                                    {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                                                    {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                                                    {"#FFA60000", "#B2FFA600", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                                                    {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}}  // attention
                                                }};
        ContainerStyleDefinition attentionPalette = {
            "#F7E9E9",
            "#FF7F7F7F7F",
            0,
            {
                // Foreground Colors
                {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                {"#FFA60000", "#B2FFA600", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}}  // attention
            },
        };
        ContainerStyleDefinition warningPalette = {"#F7F7DF",
                                                   "#FF7F7F7F7F",
                                                   0,
                                                   {
                                                       // Foreground Colors
                                                       {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                                                       {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                                                       {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                                                       {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                                                       {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                                                       {"#FFA60000", "#B2FFA600", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                                                       {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}} // attention
                                                   }};
        ContainerStyleDefinition accentPalette = {"#DCE5F7",
                                                  "#FF7F7F7F7F",
                                                  0,
                                                  {
                                                      // Foreground Colors
                                                      {"#FF000000", "#B2000000", {"#FFFFFF00", "#FFFFFFE0"}}, // defaultColor
                                                      {"#FF0000FF", "#B20000FF", {"#FFFFFF00", "#FFFFFFE0"}}, // accent
                                                      {"#FF101010", "#B2101010", {"#FFFFFF00", "#FFFFFFE0"}}, // dark
                                                      {"#FFFFFFFF", "#B2FFFFFF", {"#FFFFFF00", "#FFFFFFE0"}}, // light
                                                      {"#FF008000", "#B2008000", {"#FFFFFF00", "#FFFFFFE0"}}, // good
                                                      {"#FFA60000", "#B2FFA600", {"#FFFFFF00", "#FFFFFFE0"}}, // warning
                                                      {"#FF8B0000", "#B28B0000", {"#FFFFFF00", "#FFFFFFE0"}} // attention
                                                  }};

        static ContainerStylesDefinition Deserialize(const Json::Value& json, const ContainerStylesDefinition& defaultValue);
    };

    struct ShowCardActionConfig
    {
        ActionMode actionMode = ActionMode::Inline;
        ContainerStyle style = ContainerStyle::Emphasis;
        unsigned int inlineTopMargin = 16;

        static ShowCardActionConfig Deserialize(const Json::Value& json, const ShowCardActionConfig& defaultValue);
    };

    struct ActionsConfig
    {
        ShowCardActionConfig showCard;
        ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
        ActionAlignment actionAlignment = ActionAlignment::Stretch;
        unsigned int buttonSpacing = 10;
        unsigned int maxActions = 5;
        Spacing spacing = Spacing::Default;
        IconPlacement iconPlacement = IconPlacement::AboveTitle;
        unsigned int iconSize = 30;

        static ActionsConfig Deserialize(const Json::Value& json, const ActionsConfig& defaultValue);
    };

    struct InputLabelConfig
    {
        ForegroundColor color = ForegroundColor::Default;
        bool isSubtle = false; 
        TextSize size = TextSize::Default;
        std::string suffix = std::string();
        TextWeight weight = TextWeight::Default;

        static InputLabelConfig Deserialize(const Json::Value& json, const InputLabelConfig& defaultValue);
    };

    struct LabelConfig
    {
        Spacing inputSpacing = Spacing::Default;
        InputLabelConfig requiredInputs;
        InputLabelConfig optionalInputs;

        static LabelConfig Deserialize(const Json::Value& json, const LabelConfig& defaultValue);
    };

    struct ErrorMessageConfig
    {
        TextSize size = TextSize::Default;
        Spacing spacing = Spacing::Default;
        TextWeight weight = TextWeight::Default;

        static ErrorMessageConfig Deserialize(const Json::Value& json, const ErrorMessageConfig& defaultValue);
    };

    struct InputsConfig
    {
        LabelConfig label;
        ErrorMessageConfig errorMessage;

        static InputsConfig Deserialize(const Json::Value& json, const InputsConfig& defaultValue);
    };

    struct MediaConfig
    {
        std::string defaultPoster;
        std::string playButton;
        bool allowInlinePlayback = true;

        static MediaConfig Deserialize(const Json::Value& json, const MediaConfig& defaultValue);
    };

    class HostConfig
    {
    public:
        HostConfig() = default;
        static HostConfig Deserialize(const Json::Value& json);
        static HostConfig DeserializeFromString(const std::string& jsonString);

        FontTypeDefinition GetFontType(FontType fontType) const;
        std::string GetFontFamily(FontType fontType) const;
        unsigned int GetFontSize(FontType fontType, TextSize size) const;
        unsigned int GetFontWeight(FontType fontType, TextWeight weight) const;

        std::string GetBackgroundColor(ContainerStyle style) const;
        std::string GetForegroundColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const;
        std::string GetHighlightColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const;
        std::string GetBorderColor(ContainerStyle style) const;
        unsigned int GetBorderThickness(ContainerStyle style) const;

        std::string GetFontFamily() const;
        void SetFontFamily(const std::string& value);

        FontSizesConfig GetFontSizes() const;
        void SetFontSizes(const FontSizesConfig value);

        FontWeightsConfig GetFontWeights() const;
        void SetFontWeights(const FontWeightsConfig value);

        FontTypesDefinition GetFontTypes() const;
        void SetFontTypes(const FontTypesDefinition value);

        bool GetSupportsInteractivity() const;
        void SetSupportsInteractivity(const bool value);

        std::string GetImageBaseUrl() const;
        void SetImageBaseUrl(const std::string& value);

        ImageSizesConfig GetImageSizes() const;
        void SetImageSizes(const ImageSizesConfig value);

        ImageConfig GetImage() const;
        void SetImage(const ImageConfig value);

        SeparatorConfig GetSeparator() const;
        void SetSeparator(const SeparatorConfig value);

        SpacingConfig GetSpacing() const;
        void SetSpacing(const SpacingConfig value);

        AdaptiveCardConfig GetAdaptiveCard() const;
        void SetAdaptiveCard(const AdaptiveCardConfig value);

        ImageSetConfig GetImageSet() const;
        void SetImageSet(const ImageSetConfig value);

        FactSetConfig GetFactSet() const;
        void SetFactSet(const FactSetConfig value);

        ActionsConfig GetActions() const;
        void SetActions(const ActionsConfig value);

        ContainerStylesDefinition GetContainerStyles() const;
        void SetContainerStyles(const ContainerStylesDefinition value);

        MediaConfig GetMedia() const;
        void SetMedia(const MediaConfig value);

        InputsConfig GetInputs() const;
        void SetInputs(const InputsConfig value);

    private:
        const ContainerStyleDefinition& GetContainerStyle(ContainerStyle style) const;
        const ColorConfig& GetContainerColorConfig(const ColorsConfig& colors, ForegroundColor color) const;

        std::string _fontFamily;
        FontSizesConfig _fontSizes;
        FontWeightsConfig _fontWeights;
        FontTypesDefinition _fontTypes;
        bool _supportsInteractivity = true;
        std::string _imageBaseUrl;
        ImageSizesConfig _imageSizes;
        ImageConfig _image;
        SeparatorConfig _separator;
        SpacingConfig _spacing;
        AdaptiveCardConfig _adaptiveCard;
        ImageSetConfig _imageSet;
        FactSetConfig _factSet;
        ActionsConfig _actions;
        ContainerStylesDefinition _containerStyles;
        MediaConfig _media;
        InputsConfig _inputs;
    };
}
