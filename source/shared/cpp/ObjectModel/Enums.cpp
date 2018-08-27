#include "pch.h"
#include "Enums.h"

#ifdef USE_CPPCORECHECK
#pragma warning(push)

// Unfortunately, the checker for WARNING_NO_GLOBAL_INIT_CALLS (26426) has an issue: it considers initialization of the
// below std::unordered_map statics to be global, and thus flags them all as having overly-complex initialization. We
// want to keep this check on, in general, but turn it off for this file (all warning instances were reviewed prior to
// disablement).
#pragma warning(disable: 26426)
#endif

namespace AdaptiveSharedNamespace {

void GetAdaptiveCardSchemaKeyEnumMappings(
    std::unordered_map<AdaptiveCardSchemaKey, std::string, EnumHash> * adaptiveCardSchemaKeyEnumToNameOut,
    std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> * adaptiveCardSchemaKeyNameToEnumOut)
{
    static std::unordered_map<AdaptiveCardSchemaKey, std::string, EnumHash> adaptiveCardSchemaKeyEnumToName =
    {
        { AdaptiveCardSchemaKey::Accent, "accent" },
        { AdaptiveCardSchemaKey::ActionAlignment, "actionAlignment" },
        { AdaptiveCardSchemaKey::ActionMode, "actionMode" },
        { AdaptiveCardSchemaKey::Actions, "actions" },
        { AdaptiveCardSchemaKey::ActionSetConfig, "actionSetConfig" },
        { AdaptiveCardSchemaKey::ActionsOrientation, "actionsOrientation" },
        { AdaptiveCardSchemaKey::AdaptiveCard, "adaptiveCard" },
        { AdaptiveCardSchemaKey::AllowCustomStyle, "allowCustomStyle" },
        { AdaptiveCardSchemaKey::AllowInlinePlayback, "allowInlinePlayback" },
        { AdaptiveCardSchemaKey::AltText, "altText" },
        { AdaptiveCardSchemaKey::Attention, "attention" },
        { AdaptiveCardSchemaKey::BackgroundColor, "backgroundColor" },
        { AdaptiveCardSchemaKey::BackgroundImage, "backgroundImage" },
        { AdaptiveCardSchemaKey::BackgroundImageUrl, "backgroundImageUrl" },
        { AdaptiveCardSchemaKey::BaseCardElement, "baseCardElement" },
        { AdaptiveCardSchemaKey::Body, "body" },
        { AdaptiveCardSchemaKey::Bolder, "bolder" },
        { AdaptiveCardSchemaKey::BorderColor, "borderColor" },
        { AdaptiveCardSchemaKey::BorderThickness, "borderThickness" },
        { AdaptiveCardSchemaKey::Bottom, "bottom" },
        { AdaptiveCardSchemaKey::ButtonSpacing, "buttonSpacing" },
        { AdaptiveCardSchemaKey::Card, "card" },
        { AdaptiveCardSchemaKey::Center, "center" },
        { AdaptiveCardSchemaKey::Choices, "choices" },
        { AdaptiveCardSchemaKey::ChoiceSet, "choiceSet" },
        { AdaptiveCardSchemaKey::Color, "color" },
        { AdaptiveCardSchemaKey::ColorConfig, "colorConfig" },
        { AdaptiveCardSchemaKey::ForegroundColors, "foregroundColors" },
        { AdaptiveCardSchemaKey::Column, "column" },
        { AdaptiveCardSchemaKey::Columns, "columns" },
        { AdaptiveCardSchemaKey::ColumnSet, "columnSet" },
        { AdaptiveCardSchemaKey::Container, "container" },
        { AdaptiveCardSchemaKey::ContainerStyles, "containerStyles" },
        { AdaptiveCardSchemaKey::Dark, "dark" },
        { AdaptiveCardSchemaKey::Data, "data" },
        { AdaptiveCardSchemaKey::DateInput, "dateInput" },
        { AdaptiveCardSchemaKey::Default, "default" },
        { AdaptiveCardSchemaKey::DefaultPoster, "defaultPoster" },
        { AdaptiveCardSchemaKey::Emphasis, "emphasis" },
        { AdaptiveCardSchemaKey::ExtraLarge, "extraLarge" },
        { AdaptiveCardSchemaKey::Facts, "facts" },
        { AdaptiveCardSchemaKey::FactSet, "factSet" },
        { AdaptiveCardSchemaKey::FallbackText, "fallbackText" },
        { AdaptiveCardSchemaKey::FontFamily, "fontFamily" },
        { AdaptiveCardSchemaKey::FontSizes, "fontSizes" },
        { AdaptiveCardSchemaKey::FontWeights, "fontWeights" },
        { AdaptiveCardSchemaKey::Good, "good" },
        { AdaptiveCardSchemaKey::Height, "height" },
        { AdaptiveCardSchemaKey::HorizontalAlignment, "horizontalAlignment" },
        { AdaptiveCardSchemaKey::IconPlacement, "iconPlacement" },
        { AdaptiveCardSchemaKey::IconSize, "iconSize" },
        { AdaptiveCardSchemaKey::IconUrl, "iconUrl" },
        { AdaptiveCardSchemaKey::Id, "id" },
        { AdaptiveCardSchemaKey::Image, "image" },
        { AdaptiveCardSchemaKey::ImageBaseUrl, "imageBaseUrl" },
        { AdaptiveCardSchemaKey::Images, "images" },
        { AdaptiveCardSchemaKey::ImageSet, "imageSet" },
        { AdaptiveCardSchemaKey::ImageSize, "imageSize" },
        { AdaptiveCardSchemaKey::ImageSizes, "imageSizes" },
        { AdaptiveCardSchemaKey::InlineTopMargin, "inlineTopMargin" },
        { AdaptiveCardSchemaKey::IsMultiline, "isMultiline" },
        { AdaptiveCardSchemaKey::IsMultiSelect, "isMultiSelect" },
        { AdaptiveCardSchemaKey::IsRequired, "isRequired" },
        { AdaptiveCardSchemaKey::IsSelected, "isSelected" },
        { AdaptiveCardSchemaKey::IsSubtle, "isSubtle" },
        { AdaptiveCardSchemaKey::Items, "items" },
        { AdaptiveCardSchemaKey::Language, "lang" },
        { AdaptiveCardSchemaKey::Large, "large" },
        { AdaptiveCardSchemaKey::Left, "left" },
        { AdaptiveCardSchemaKey::Light, "light" },
        { AdaptiveCardSchemaKey::Lighter, "lighter" },
        { AdaptiveCardSchemaKey::LineColor, "lineColor" },
        { AdaptiveCardSchemaKey::LineThickness, "lineThickness" },
        { AdaptiveCardSchemaKey::Max, "max" },
        { AdaptiveCardSchemaKey::MaxActions, "maxActions" },
        { AdaptiveCardSchemaKey::MaxImageHeight, "maxImageHeight" },
        { AdaptiveCardSchemaKey::MaxLength, "maxLength" },
        { AdaptiveCardSchemaKey::MaxLines, "maxLines" },
        { AdaptiveCardSchemaKey::MaxWidth, "maxWidth" },
        { AdaptiveCardSchemaKey::Media, "media" },
        { AdaptiveCardSchemaKey::Medium, "medium" },
        { AdaptiveCardSchemaKey::Method, "method" },
        { AdaptiveCardSchemaKey::MimeType, "mimeType" },
        { AdaptiveCardSchemaKey::Min, "min" },
        { AdaptiveCardSchemaKey::NumberInput, "numberInput" },
        { AdaptiveCardSchemaKey::Padding, "padding" },
        { AdaptiveCardSchemaKey::Placeholder, "placeholder" },
        { AdaptiveCardSchemaKey::PlayButton, "playButton" },
        { AdaptiveCardSchemaKey::Poster, "poster" },
        { AdaptiveCardSchemaKey::Right, "right" },
        { AdaptiveCardSchemaKey::SelectAction, "selectAction" },
        { AdaptiveCardSchemaKey::Separator, "separator" },
        { AdaptiveCardSchemaKey::Thickness, "thickness" },
        { AdaptiveCardSchemaKey::ShowActionMode, "showActionMode" },
        { AdaptiveCardSchemaKey::ShowCard, "showCard" },
        { AdaptiveCardSchemaKey::ShowCardActionConfig, "showCardActionConfig" },
        { AdaptiveCardSchemaKey::Size, "size" },
        { AdaptiveCardSchemaKey::Small, "small" },
        { AdaptiveCardSchemaKey::Sources, "sources" },
        { AdaptiveCardSchemaKey::Spacing, "spacing" },
        { AdaptiveCardSchemaKey::SpacingDefinition, "spacingDefinition" },
        { AdaptiveCardSchemaKey::Speak, "speak" },
        { AdaptiveCardSchemaKey::Stretch, "stretch" },
        { AdaptiveCardSchemaKey::Style, "style" },
        { AdaptiveCardSchemaKey::Subtle, "subtle" },
        { AdaptiveCardSchemaKey::SupportsInteractivity, "supportsInteractivity" },
        { AdaptiveCardSchemaKey::Text, "text" },
        { AdaptiveCardSchemaKey::TextBlock, "textBlock" },
        { AdaptiveCardSchemaKey::TextConfig, "textConfig" },
        { AdaptiveCardSchemaKey::TextInput, "textInput" },
        { AdaptiveCardSchemaKey::TextWeight, "weight" },
        { AdaptiveCardSchemaKey::Thick, "thick" },
        { AdaptiveCardSchemaKey::Thickness, "thickness" },
        { AdaptiveCardSchemaKey::TimeInput, "timeInput" },
        { AdaptiveCardSchemaKey::Title, "title" },
        { AdaptiveCardSchemaKey::ToggleInput, "toggleInput" },
        { AdaptiveCardSchemaKey::Top, "top" },
        { AdaptiveCardSchemaKey::Type, "type" },
        { AdaptiveCardSchemaKey::Url, "url" },
        { AdaptiveCardSchemaKey::Value, "value" },
        { AdaptiveCardSchemaKey::ValueOff, "valueOff" },
        { AdaptiveCardSchemaKey::ValueOn, "valueOn" },
        { AdaptiveCardSchemaKey::Version, "version" },
        { AdaptiveCardSchemaKey::VerticalContentAlignment, "verticalContentAlignment" },
        { AdaptiveCardSchemaKey::Warning, "warning" },
        { AdaptiveCardSchemaKey::Weight, "weight" },
        { AdaptiveCardSchemaKey::Width, "width" },
        { AdaptiveCardSchemaKey::Wrap, "wrap" }
    };
    static std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> adaptiveCardSchemaKeyNameToEnum = GenerateStringToEnumMap<AdaptiveCardSchemaKey>(adaptiveCardSchemaKeyEnumToName);

    if (adaptiveCardSchemaKeyEnumToNameOut != nullptr)
    {
        *adaptiveCardSchemaKeyEnumToNameOut = adaptiveCardSchemaKeyEnumToName;
    }

    if (adaptiveCardSchemaKeyNameToEnumOut != nullptr)
    {
        *adaptiveCardSchemaKeyNameToEnumOut = adaptiveCardSchemaKeyNameToEnum;
    }
}

void GetCardElementTypeEnumMappings(
    std::unordered_map<CardElementType, std::string, EnumHash> * cardElementTypeEnumToNameOut,
    std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> * cardElementTypeNameToEnumOut)
{
    static std::unordered_map<CardElementType, std::string, EnumHash> cardElementTypeEnumToName =
    {
        { CardElementType::AdaptiveCard, "AdaptiveCard" },
        { CardElementType::Column, "Column" },
        { CardElementType::ColumnSet, "ColumnSet" },
        { CardElementType::Container, "Container" },
        { CardElementType::Fact, "Fact" },
        { CardElementType::FactSet, "FactSet" },
        { CardElementType::Image, "Image" },
        { CardElementType::ImageSet, "ImageSet" },
        { CardElementType::ChoiceSetInput, "Input.ChoiceSet" },
        { CardElementType::DateInput, "Input.Date" },
        { CardElementType::NumberInput, "Input.Number" },
        { CardElementType::TextInput, "Input.Text" },
        { CardElementType::TimeInput, "Input.Time" },
        { CardElementType::ToggleInput, "Input.Toggle" },
        { CardElementType::TextBlock, "TextBlock" },
        { CardElementType::Custom, "Custom" },
        { CardElementType::Unknown, "Unknown" },
        { CardElementType::Media, "Media" },
    };
    static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> cardElementTypeNameToEnum = GenerateStringToEnumMap<CardElementType>(cardElementTypeEnumToName);

    if (cardElementTypeEnumToNameOut != nullptr)
    {
        *cardElementTypeEnumToNameOut = cardElementTypeEnumToName;
    }

    if (cardElementTypeNameToEnumOut != nullptr)
    {
        *cardElementTypeNameToEnumOut = cardElementTypeNameToEnum;
    }
}

void GetActionTypeEnumMappings(
    std::unordered_map<ActionType, std::string, EnumHash> * actionTypeEnumToNameOut,
    std::unordered_map<std::string, ActionType, CaseInsensitiveHash, CaseInsensitiveEqualTo> * actionTypeNameToEnumOut)
{
    static std::unordered_map<ActionType, std::string, EnumHash> actionTypeEnumToName =
    {
        { ActionType::OpenUrl, "Action.OpenUrl" },
        { ActionType::ShowCard, "Action.ShowCard" },
        { ActionType::Submit, "Action.Submit" },
        { ActionType::Custom, "Custom" }
    };
    static std::unordered_map<std::string, ActionType, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionTypeNameToEnum = GenerateStringToEnumMap<ActionType>(actionTypeEnumToName);

    if (actionTypeEnumToNameOut != nullptr)
    {
        *actionTypeEnumToNameOut = actionTypeEnumToName;
    }

    if (actionTypeNameToEnumOut != nullptr)
    {
        *actionTypeNameToEnumOut = actionTypeNameToEnum;
    }
}

void GetHeightTypeEnumMappings(
    std::unordered_map<HeightType, std::string, EnumHash> * heightTypeEnumToNameOut,
    std::unordered_map<std::string, HeightType, CaseInsensitiveHash, CaseInsensitiveEqualTo> * heightTypeNameToEnumOut)
{
    static std::unordered_map<HeightType, std::string, EnumHash> heightTypeEnumToName =
    {
        { HeightType::Auto, "Auto" },
        { HeightType::Stretch, "Stretch" }
    };

    static std::unordered_map<std::string, HeightType, CaseInsensitiveHash, CaseInsensitiveEqualTo>
        heightTypeNameToEnum = GenerateStringToEnumMap<HeightType>(heightTypeEnumToName);

    if (heightTypeEnumToNameOut != nullptr)
    {
        *heightTypeEnumToNameOut = heightTypeEnumToName;
    }

    if (heightTypeNameToEnumOut != nullptr)
    {
        *heightTypeNameToEnumOut = heightTypeNameToEnum;
    }
}

void GetSpacingMappings(
    std::unordered_map<Spacing, std::string, EnumHash> * spacingEnumToNameOut,
    std::unordered_map<std::string, Spacing, CaseInsensitiveHash, CaseInsensitiveEqualTo> * spacingNameToEnumOut)
{
    static std::unordered_map<Spacing, std::string, EnumHash> spacingEnumToName =
        {
            { Spacing::Default, "default" },
            { Spacing::None, "none" },
            { Spacing::Small, "small" },
            { Spacing::Medium, "medium" },
            { Spacing::Large, "large" },
            { Spacing::ExtraLarge, "extraLarge" },
            { Spacing::Padding, "padding" },
        };
    static std::unordered_map<std::string, Spacing, CaseInsensitiveHash, CaseInsensitiveEqualTo> spacingNameToEnum = GenerateStringToEnumMap<Spacing>(spacingEnumToName);

    if (spacingEnumToNameOut != nullptr)
    {
        *spacingEnumToNameOut = spacingEnumToName;
    }

    if (spacingNameToEnumOut != nullptr)
    {
        *spacingNameToEnumOut = spacingNameToEnum;
    }
}

void GetSeparatorThicknessEnumMappings(
    std::unordered_map<SeparatorThickness, std::string, EnumHash> *separatorThicknessEnumToNameOut,
    std::unordered_map<std::string, SeparatorThickness, CaseInsensitiveHash, CaseInsensitiveEqualTo> * separatorThicknessNameToEnumOut)
{
    static std::unordered_map<SeparatorThickness, std::string, EnumHash> separatorThicknessEnumToName =
    {
        { SeparatorThickness::Default, "default" },
        { SeparatorThickness::Thick, "thick" },
    };
    static std::unordered_map<std::string, SeparatorThickness, CaseInsensitiveHash, CaseInsensitiveEqualTo> separatorThicknessNameToEnum = GenerateStringToEnumMap<SeparatorThickness>(separatorThicknessEnumToName);

    if (separatorThicknessEnumToNameOut != nullptr)
    {
        *separatorThicknessEnumToNameOut = separatorThicknessEnumToName;
    }

    if (separatorThicknessNameToEnumOut != nullptr)
    {
        *separatorThicknessNameToEnumOut = separatorThicknessNameToEnum;
    }
}

void GetImageStyleEnumMappings(
    std::unordered_map<ImageStyle, std::string, EnumHash> * imageStyleEnumToNameOut,
    std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> * imageStyleNameToEnumOut)
{
    static std::unordered_map<ImageStyle, std::string, EnumHash> imageStyleEnumToName =
    {
        { ImageStyle::Default, "default" },
        { ImageStyle::Person, "person" }
    };

    static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> imageStyleNameToEnum =
    {
        { "default", ImageStyle::Default },
        { "person", ImageStyle::Person },
        { "normal", ImageStyle::Default } // Back compat to support "Normal" for "Default" for pre V1.0 payloads
    };

    if (imageStyleEnumToNameOut != nullptr)
    {
        *imageStyleEnumToNameOut = imageStyleEnumToName;
    }

    if (imageStyleNameToEnumOut != nullptr)
    {
        *imageStyleNameToEnumOut = imageStyleNameToEnum;
    }
}

void GetImageSizeEnumMappings(
    std::unordered_map<ImageSize, std::string, EnumHash> * imageSizeEnumToNameOut,
    std::unordered_map<std::string, ImageSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> * imageSizeNameToEnumOut)
{
    static std::unordered_map<ImageSize, std::string, EnumHash> imageSizeEnumToName =
    {
        { ImageSize::Auto, "Auto" },
        { ImageSize::Large, "Large" },
        { ImageSize::Medium, "Medium" },
        { ImageSize::Small, "Small" },
        { ImageSize::Stretch, "Stretch" },
    };
    static std::unordered_map<std::string, ImageSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> imageSizeNameToEnum = GenerateStringToEnumMap<ImageSize>(imageSizeEnumToName);

    if (imageSizeEnumToNameOut != nullptr)
    {
        *imageSizeEnumToNameOut = imageSizeEnumToName;
    }

    if (imageSizeNameToEnumOut != nullptr)
    {
        *imageSizeNameToEnumOut = imageSizeNameToEnum;
    }
};

void GetHorizontalAlignmentEnumMappings(
    std::unordered_map<HorizontalAlignment, std::string, EnumHash> * horizontalAlignmentEnumToNameOut,
    std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> * horizontalAlignmentNameToEnumOut)
{
    static std::unordered_map<HorizontalAlignment, std::string, EnumHash> horizontalAlignmentEnumToName =
    {
        {HorizontalAlignment::Center, "Center"},
        {HorizontalAlignment::Left, "Left"},
        {HorizontalAlignment::Right, "Right"}
    };
    static std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> horizontalAlignmentNameToEnum = GenerateStringToEnumMap<HorizontalAlignment>(horizontalAlignmentEnumToName);

    if (horizontalAlignmentEnumToNameOut != nullptr)
    {
        *horizontalAlignmentEnumToNameOut = horizontalAlignmentEnumToName;
    }

    if (horizontalAlignmentNameToEnumOut != nullptr)
    {
        *horizontalAlignmentNameToEnumOut = horizontalAlignmentNameToEnum;
    }
};

void GetColorEnumMappings(
    std::unordered_map<ForegroundColor, std::string, EnumHash> * colorEnumToNameOut,
    std::unordered_map<std::string, ForegroundColor, CaseInsensitiveHash, CaseInsensitiveEqualTo> * colorNameToEnumOut)
{
    static std::unordered_map<ForegroundColor, std::string, EnumHash> colorEnumToName =
    {
        {ForegroundColor::Accent, "Accent"},
        {ForegroundColor::Attention, "Attention"},
        {ForegroundColor::Dark, "Dark" },
        {ForegroundColor::Default, "Default"},
        {ForegroundColor::Good, "Good"},
        {ForegroundColor::Light, "Light" },
        {ForegroundColor::Warning, "Warning"},
    };
    static std::unordered_map<std::string, ForegroundColor, CaseInsensitiveHash, CaseInsensitiveEqualTo> colorNameToEnum = GenerateStringToEnumMap<ForegroundColor>(colorEnumToName);

    if (colorEnumToNameOut != nullptr)
    {
        *colorEnumToNameOut = colorEnumToName;
    }

    if (colorNameToEnumOut != nullptr)
    {
        *colorNameToEnumOut = colorNameToEnum;
    }
}

void GetTextWeightEnumMappings(
    std::unordered_map<TextWeight, std::string, EnumHash> * textWeightEnumToNameOut,
    std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> * textWeightNameToEnumOut)
{
    static std::unordered_map<TextWeight, std::string, EnumHash> textWeightEnumToName =
    {
        {TextWeight::Bolder, "Bolder"},
        {TextWeight::Lighter, "Lighter"},
        {TextWeight::Default, "Default"},
    };

    static std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> textWeightNameToEnum =
    {
        { "Bolder", TextWeight::Bolder },
        { "Lighter", TextWeight::Lighter },
        { "Default", TextWeight::Default },
        { "Normal", TextWeight::Default }, // Back compat to support "Normal" for "Default" for pre V1.0 payloads
    };

    if (textWeightEnumToNameOut != nullptr)
    {
        *textWeightEnumToNameOut = textWeightEnumToName;
    }

    if (textWeightNameToEnumOut != nullptr)
    {
        *textWeightNameToEnumOut = textWeightNameToEnum;
    }
}

void GetTextSizeEnumMappings(
    std::unordered_map<TextSize, std::string, EnumHash> * textSizeEnumToNameOut,
    std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> * textSizeNameToEnumOut)
{
    static std::unordered_map<TextSize, std::string, EnumHash> textSizeEnumToName =
    {
        {TextSize::ExtraLarge, "ExtraLarge"},
        {TextSize::Large, "Large"},
        {TextSize::Medium, "Medium"},
        {TextSize::Default, "Default"},
        {TextSize::Small, "Small"},
    };

    static std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> textSizeNameToEnum =
    {
        { "ExtraLarge", TextSize::ExtraLarge },
        { "Large", TextSize::Large },
        { "Medium", TextSize::Medium },
        { "Default", TextSize::Default },
        { "Small", TextSize::Small },
        { "Normal", TextSize::Default }, // Back compat to support "Normal" for "Default" for pre V1.0 payloads
    };

    if (textSizeEnumToNameOut != nullptr)
    {
        *textSizeEnumToNameOut = textSizeEnumToName;
    }

    if (textSizeNameToEnumOut != nullptr)
    {
        *textSizeNameToEnumOut = textSizeNameToEnum;
    }
}

void GetActionsOrientationEnumMappings(
    std::unordered_map<ActionsOrientation, std::string, EnumHash> * actionsOrientationEnumToNameOut,
    std::unordered_map<std::string, ActionsOrientation, CaseInsensitiveHash, CaseInsensitiveEqualTo> * actionsOrientationNameToEnumOut)
{
    static std::unordered_map<ActionsOrientation, std::string, EnumHash> actionsOrientationEnumToName =
    {
        { ActionsOrientation::Horizontal, "Horizontal" },
        { ActionsOrientation::Vertical, "Vertical" },
    };
    static std::unordered_map<std::string, ActionsOrientation, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionsOrientationNameToEnum = GenerateStringToEnumMap<ActionsOrientation>(actionsOrientationEnumToName);

    if (actionsOrientationEnumToNameOut != nullptr)
    {
        *actionsOrientationEnumToNameOut = actionsOrientationEnumToName;
    }

    if (actionsOrientationNameToEnumOut != nullptr)
    {
        *actionsOrientationNameToEnumOut = actionsOrientationNameToEnum;
    }
}

void GetActionModeEnumMappings(
    std::unordered_map<ActionMode, std::string, EnumHash> * actionModeEnumToNameOut,
    std::unordered_map<std::string, ActionMode, CaseInsensitiveHash, CaseInsensitiveEqualTo> * actionModeNameToEnumOut)
{
    static std::unordered_map<ActionMode, std::string, EnumHash> actionModeEnumToName =
    {
        { ActionMode::Inline, "Inline" },
        { ActionMode::Popup, "Popup" }
    };
    static std::unordered_map<std::string, ActionMode, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionModeNameToEnum = GenerateStringToEnumMap<ActionMode>(actionModeEnumToName);

    if (actionModeEnumToNameOut != nullptr)
    {
        *actionModeEnumToNameOut = actionModeEnumToName;
    }

    if (actionModeNameToEnumOut != nullptr)
    {
        *actionModeNameToEnumOut = actionModeNameToEnum;
    }
}

void GetChoiceSetStyleEnumMappings(
    std::unordered_map<ChoiceSetStyle, std::string, EnumHash> * choiceSetStyleEnumToNameOut,
    std::unordered_map<std::string, ChoiceSetStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> * choiceSetStyleNameToEnumOut)
{
    static std::unordered_map<ChoiceSetStyle, std::string, EnumHash> choiceSetStyleEnumToName =
    {
        { ChoiceSetStyle::Compact, "Compact" },
        { ChoiceSetStyle::Expanded, "Expanded" }
    };
    static std::unordered_map<std::string, ChoiceSetStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> choiceSetStyleNameToEnum = GenerateStringToEnumMap<ChoiceSetStyle>(choiceSetStyleEnumToName);

    if (choiceSetStyleEnumToNameOut != nullptr)
    {
        *choiceSetStyleEnumToNameOut = choiceSetStyleEnumToName;
    }

    if (choiceSetStyleNameToEnumOut != nullptr)
    {
        *choiceSetStyleNameToEnumOut = choiceSetStyleNameToEnum;
    }
};

void GetTextInputStyleEnumMappings(
    std::unordered_map<TextInputStyle, std::string, EnumHash> * textInputStyleEnumToNameOut,
    std::unordered_map<std::string, TextInputStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> * textInputStyleNameToEnumOut)
{
    static std::unordered_map<TextInputStyle, std::string, EnumHash> textInputStyleEnumToName =
    {
        { TextInputStyle::Email, "Email" },
        { TextInputStyle::Tel, "Tel" },
        { TextInputStyle::Text, "Text" },
        { TextInputStyle::Url, "Url" },
    };
    static std::unordered_map<std::string, TextInputStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> textInputStyleNameToEnum = GenerateStringToEnumMap<TextInputStyle>(textInputStyleEnumToName);

    if (textInputStyleEnumToNameOut != nullptr)
    {
        *textInputStyleEnumToNameOut = textInputStyleEnumToName;
    }

    if (textInputStyleNameToEnumOut != nullptr)
    {
        *textInputStyleNameToEnumOut = textInputStyleNameToEnum;
    }
}

void GetContainerStyleEnumMappings(
    std::unordered_map<ContainerStyle, std::string, EnumHash> * containerStyleEnumToNameOut,
    std::unordered_map<std::string, ContainerStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> * containerStyleNameToEnumOut)
{
    static std::unordered_map<ContainerStyle, std::string, EnumHash> containerStyleEnumToName =
    {
        { ContainerStyle::Default, "Default" },
        { ContainerStyle::Emphasis, "Emphasis" },
    };
    static std::unordered_map<std::string, ContainerStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> containerStyleNameToEnum = GenerateStringToEnumMap<ContainerStyle>(containerStyleEnumToName);

    if (containerStyleEnumToNameOut != nullptr)
    {
        *containerStyleEnumToNameOut = containerStyleEnumToName;
    }

    if (containerStyleNameToEnumOut != nullptr)
    {
        *containerStyleNameToEnumOut = containerStyleNameToEnum;
    }
}

void GetActionAlignmentEnumMappings(
    std::unordered_map<ActionAlignment, std::string, EnumHash> * actionAlignmentEnumToNameOut,
    std::unordered_map<std::string, ActionAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> * actionAlignmentNameToEnumOut)
{
    static std::unordered_map<ActionAlignment, std::string, EnumHash> actionAlignmentEnumToName =
    {
        { ActionAlignment::Left, "Left" },
        { ActionAlignment::Center, "Center" },
        { ActionAlignment::Right, "Right" },
        { ActionAlignment::Stretch, "Stretch" },
    };
    static std::unordered_map<std::string, ActionAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionAlignmentNameToEnum = GenerateStringToEnumMap<ActionAlignment>(actionAlignmentEnumToName);

    if (actionAlignmentEnumToNameOut != nullptr)
    {
        *actionAlignmentEnumToNameOut = actionAlignmentEnumToName;
    }

    if (actionAlignmentNameToEnumOut != nullptr)
    {
        *actionAlignmentNameToEnumOut = actionAlignmentNameToEnum;
    }
}

void GetIconPlacementEnumMappings(
    std::unordered_map<IconPlacement, std::string, EnumHash> * iconPlacementEnumToNameOut,
    std::unordered_map<std::string, IconPlacement, CaseInsensitiveHash, CaseInsensitiveEqualTo> * iconPlacementNameToEnumOut)
{
    static std::unordered_map<IconPlacement, std::string, EnumHash> iconPlacementEnumToName =
    {
        {IconPlacement::AboveTitle , "AboveTitle"},
        {IconPlacement::LeftOfTitle, "LeftOfTitle"}
    };
    static std::unordered_map<std::string, IconPlacement, CaseInsensitiveHash, CaseInsensitiveEqualTo> iconPlacementNameToEnum = GenerateStringToEnumMap<IconPlacement>(iconPlacementEnumToName);

    if (iconPlacementEnumToNameOut != nullptr)
    {
        *iconPlacementEnumToNameOut = iconPlacementEnumToName;
    }

    if (iconPlacementNameToEnumOut != nullptr)
    {
        *iconPlacementNameToEnumOut = iconPlacementNameToEnum;
    }
}

void GetVerticalContentAlignmentEnumMappings(
    std::unordered_map<VerticalContentAlignment, std::string, EnumHash> * verticalContentAlignmentEnumToNameOut,
    std::unordered_map<std::string, VerticalContentAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> * verticalContentAlignmentNameToEnumOut)
{
    static std::unordered_map<VerticalContentAlignment, std::string, EnumHash> verticalContentAlignmentEnumToName =
    {
        { VerticalContentAlignment::Top, "Top" },
        { VerticalContentAlignment::Center, "Center" },
        { VerticalContentAlignment::Bottom, "Bottom" }
    };
    static std::unordered_map<std::string, VerticalContentAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> verticalContentAlignmentNameToEnum =
        GenerateStringToEnumMap<VerticalContentAlignment>(verticalContentAlignmentEnumToName);

    if (verticalContentAlignmentEnumToNameOut != nullptr)
    {
        *verticalContentAlignmentEnumToNameOut = verticalContentAlignmentEnumToName;
    }

    if (verticalContentAlignmentNameToEnumOut != nullptr)
    {
        *verticalContentAlignmentNameToEnumOut = verticalContentAlignmentNameToEnum;
    }
}

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type)
{
    std::unordered_map<AdaptiveCardSchemaKey, std::string, EnumHash> adaptiveCardSchemaKeyEnumToName;
    GetAdaptiveCardSchemaKeyEnumMappings(&adaptiveCardSchemaKeyEnumToName, nullptr);

    if (adaptiveCardSchemaKeyEnumToName.find(type) == adaptiveCardSchemaKeyEnumToName.end())
    {
        throw std::out_of_range("Invalid AdaptiveCardSchemaKey");
    }

    return adaptiveCardSchemaKeyEnumToName[type];
}

AdaptiveCardSchemaKey AdaptiveCardSchemaKeyFromString(const std::string& type)
{
    std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> adaptiveCardSchemaKeyNameToEnum;
    GetAdaptiveCardSchemaKeyEnumMappings(nullptr, &adaptiveCardSchemaKeyNameToEnum);

    if (adaptiveCardSchemaKeyNameToEnum.find(type) == adaptiveCardSchemaKeyNameToEnum.end())
    {
        throw std::out_of_range("Invalid AdaptiveCardSchemaKey: " + type);
    }

    return adaptiveCardSchemaKeyNameToEnum[type];
}

const std::string CardElementTypeToString(CardElementType elementType)
{
    std::unordered_map<CardElementType, std::string, EnumHash> cardElementTypeEnumToName;
    GetCardElementTypeEnumMappings(&cardElementTypeEnumToName, nullptr);

    if (cardElementTypeEnumToName.find(elementType) == cardElementTypeEnumToName.end())
    {
        throw std::out_of_range("Invalid CardElementType");
    }

    return cardElementTypeEnumToName[elementType];
}

CardElementType CardElementTypeFromString(const std::string& elementType)
{
    std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> cardElementTypeNameToEnum;
    GetCardElementTypeEnumMappings(nullptr, &cardElementTypeNameToEnum);

    if (cardElementTypeNameToEnum.find(elementType) == cardElementTypeNameToEnum.end())
    {
        return CardElementType::Unsupported;
    }

    return cardElementTypeNameToEnum[elementType];
}

const std::string ActionTypeToString(ActionType actionType)
{
    std::unordered_map<ActionType, std::string, EnumHash> actionTypeEnumToName;
    GetActionTypeEnumMappings(&actionTypeEnumToName, nullptr);

    if (actionTypeEnumToName.find(actionType) == actionTypeEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionType");
    }

    return actionTypeEnumToName[actionType];
}

ActionType ActionTypeFromString(const std::string& actionType)
{
    std::unordered_map<std::string, ActionType, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionTypeNameToEnum;
    GetActionTypeEnumMappings(nullptr, &actionTypeNameToEnum);

    if (actionTypeNameToEnum.find(actionType) == actionTypeNameToEnum.end())
    {
        return ActionType::Unsupported;
    }

    return actionTypeNameToEnum[actionType];
}

const std::string HeightTypeToString(HeightType heightType)
{
    std::unordered_map<HeightType, std::string, EnumHash> heightTypeEnumToName;
    GetHeightTypeEnumMappings(&heightTypeEnumToName, nullptr);

    if (heightTypeEnumToName.find(heightType) == heightTypeEnumToName.end())
    {
        throw std::out_of_range("Invalid HeightType type");
    }

    return heightTypeEnumToName[heightType];
}

HeightType HeightTypeFromString(const std::string& heightType)
{
    std::unordered_map<std::string, HeightType, CaseInsensitiveHash, CaseInsensitiveEqualTo> heightTypeNameToEnum;
    GetHeightTypeEnumMappings(nullptr, &heightTypeNameToEnum);

    if (heightTypeNameToEnum.find(heightType) == heightTypeNameToEnum.end())
    {
        return HeightType::Auto;
    }

    return heightTypeNameToEnum[heightType];
}

const std::string HorizontalAlignmentToString(HorizontalAlignment alignment)
{
    std::unordered_map<HorizontalAlignment, std::string, EnumHash> horizontalAlignmentEnumToName;
    GetHorizontalAlignmentEnumMappings(&horizontalAlignmentEnumToName, nullptr);

    if (horizontalAlignmentEnumToName.find(alignment) == horizontalAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid HorizontalAlignment type");
    }
    return horizontalAlignmentEnumToName[alignment];
}

HorizontalAlignment HorizontalAlignmentFromString(const std::string& alignment)
{
    std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> horizontalAlignmentNameToEnum;
    GetHorizontalAlignmentEnumMappings(nullptr, &horizontalAlignmentNameToEnum);

    if (horizontalAlignmentNameToEnum.find(alignment) == horizontalAlignmentNameToEnum.end())
    {
        return HorizontalAlignment::Left;
    }

    return horizontalAlignmentNameToEnum[alignment];
}

const std::string ForegroundColorToString(ForegroundColor color)
{
    std::unordered_map<ForegroundColor, std::string, EnumHash> colorEnumToName;
    GetColorEnumMappings(&colorEnumToName, nullptr);

    if (colorEnumToName.find(color) == colorEnumToName.end())
    {
        throw std::out_of_range("Invalid ForegroundColor type");
    }
    return colorEnumToName[color];
}

ForegroundColor ForegroundColorFromString(const std::string& color)
{
    std::unordered_map<std::string, ForegroundColor, CaseInsensitiveHash, CaseInsensitiveEqualTo> colorNameToEnum;
    GetColorEnumMappings(nullptr, &colorNameToEnum);

    if (colorNameToEnum.find(color) == colorNameToEnum.end())
    {
        return ForegroundColor::Default;
    }

    return colorNameToEnum[color];
}

const std::string TextWeightToString(TextWeight weight)
{
    std::unordered_map<TextWeight, std::string, EnumHash> textWeightEnumToName;
    GetTextWeightEnumMappings(&textWeightEnumToName, nullptr);

    if (textWeightEnumToName.find(weight) == textWeightEnumToName.end())
    {
        throw std::out_of_range("Invalid TextWeight type");
    }
    return textWeightEnumToName[weight];
}

TextWeight TextWeightFromString(const std::string& weight)
{
    std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> textWeightNameToEnum;
    GetTextWeightEnumMappings(nullptr, &textWeightNameToEnum);

    if (textWeightNameToEnum.find(weight) == textWeightNameToEnum.end())
    {
        return TextWeight::Default;
    }

    return textWeightNameToEnum[weight];
}

const std::string TextSizeToString(TextSize size)
{
    std::unordered_map<TextSize, std::string, EnumHash> textSizeEnumToName;
    GetTextSizeEnumMappings(&textSizeEnumToName, nullptr);

    if (textSizeEnumToName.find(size) == textSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid TextSize type");
    }
    return textSizeEnumToName[size];
}

TextSize TextSizeFromString(const std::string& size)
{
    std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> textSizeNameToEnum;
    GetTextSizeEnumMappings(nullptr, &textSizeNameToEnum);

    if (textSizeNameToEnum.find(size) == textSizeNameToEnum.end())
    {
        return TextSize::Default;
    }

    return textSizeNameToEnum[size];
}

const std::string ImageSizeToString(ImageSize size)
{
    std::unordered_map<ImageSize, std::string, EnumHash> imageSizeEnumToName;
    GetImageSizeEnumMappings(&imageSizeEnumToName, nullptr);

    if (imageSizeEnumToName.find(size) == imageSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid ImageSize type");
    }
    return imageSizeEnumToName[size];
}

ImageSize ImageSizeFromString(const std::string& size)
{
    std::unordered_map<std::string, ImageSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> imageSizeNameToEnum;
    GetImageSizeEnumMappings(nullptr, &imageSizeNameToEnum);

    if (imageSizeNameToEnum.find(size) == imageSizeNameToEnum.end())
    {
        return ImageSize::Auto;
    }

    return imageSizeNameToEnum[size];
}

const std::string SpacingToString(Spacing spacing)
{
    std::unordered_map<Spacing, std::string, EnumHash> spacingEnumToName;
    GetSpacingMappings(&spacingEnumToName, nullptr);

    if (spacingEnumToName.find(spacing) == spacingEnumToName.end())
    {
        throw std::out_of_range("Invalid Spacing type");
    }
    return spacingEnumToName[spacing];
}

Spacing SpacingFromString(const std::string& spacing)
{
    std::unordered_map<std::string, Spacing, CaseInsensitiveHash, CaseInsensitiveEqualTo> spacingNameToEnum;
    GetSpacingMappings(nullptr, &spacingNameToEnum);

    if (spacingNameToEnum.find(spacing) == spacingNameToEnum.end())
    {
        return Spacing::Default;
    }

    return spacingNameToEnum[spacing];
}

const std::string SeparatorThicknessToString(SeparatorThickness thickness)
{
    std::unordered_map<SeparatorThickness, std::string, EnumHash> separatorThicknessEnumToName;
    GetSeparatorThicknessEnumMappings(&separatorThicknessEnumToName, nullptr);

    if (separatorThicknessEnumToName.find(thickness) == separatorThicknessEnumToName.end())
    {
        throw std::out_of_range("Invalid SeparatorThickness type");
    }
    return separatorThicknessEnumToName[thickness];
}

SeparatorThickness SeparatorThicknessFromString(const std::string& thickness)
{
    std::unordered_map<std::string, SeparatorThickness, CaseInsensitiveHash, CaseInsensitiveEqualTo> separatorThicknessNameToEnum;
    GetSeparatorThicknessEnumMappings(nullptr, &separatorThicknessNameToEnum);

    if (separatorThicknessNameToEnum.find(thickness) == separatorThicknessNameToEnum.end())
    {
        return SeparatorThickness::Default;
    }

    return separatorThicknessNameToEnum[thickness];
}

const std::string ImageStyleToString(ImageStyle style)
{
    std::unordered_map<ImageStyle, std::string, EnumHash> imageStyleEnumToName;
    GetImageStyleEnumMappings(&imageStyleEnumToName, nullptr);

    if (imageStyleEnumToName.find(style) == imageStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ImageStyle style");
    }
    return imageStyleEnumToName[style];
}

ImageStyle ImageStyleFromString(const std::string& style)
{
    std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> imageStyleNameToEnum;
    GetImageStyleEnumMappings(nullptr, &imageStyleNameToEnum);

    if (imageStyleNameToEnum.find(style) == imageStyleNameToEnum.end())
    {
        return ImageStyle::Default;
    }

    return imageStyleNameToEnum[style];
}

const std::string ActionsOrientationToString(ActionsOrientation orientation)
{
    std::unordered_map<ActionsOrientation, std::string, EnumHash> actionsOrientationEnumToName;
    GetActionsOrientationEnumMappings(&actionsOrientationEnumToName, nullptr);

    if (actionsOrientationEnumToName.find(orientation) == actionsOrientationEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionsOrientation type");
    }
    return actionsOrientationEnumToName[orientation];
}

ActionsOrientation ActionsOrientationFromString(const std::string& orientation)
{
    std::unordered_map<std::string, ActionsOrientation, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionsOrientationNameToEnum;
    GetActionsOrientationEnumMappings(nullptr, &actionsOrientationNameToEnum);

    if (actionsOrientationNameToEnum.find(orientation) == actionsOrientationNameToEnum.end())
    {
        return ActionsOrientation::Horizontal;
    }
    return actionsOrientationNameToEnum[orientation];
}

const std::string ActionModeToString(ActionMode mode)
{
    std::unordered_map<ActionMode, std::string, EnumHash> actionModeEnumToName;
    GetActionModeEnumMappings(&actionModeEnumToName, nullptr);

    if (actionModeEnumToName.find(mode) == actionModeEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionMode type");
    }
    return actionModeEnumToName[mode];
}

ActionMode ActionModeFromString(const std::string& mode)
{
    std::unordered_map<std::string, ActionMode, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionModeNameToEnum;
    GetActionModeEnumMappings(nullptr, &actionModeNameToEnum);

    if (actionModeNameToEnum.find(mode) == actionModeNameToEnum.end())
    {
        return ActionMode::Inline;
    }
    return actionModeNameToEnum[mode];
}

const std::string ChoiceSetStyleToString(ChoiceSetStyle style)
{
    std::unordered_map<ChoiceSetStyle, std::string, EnumHash> choiceSetStyleEnumToName;
    GetChoiceSetStyleEnumMappings(&choiceSetStyleEnumToName, nullptr);

    if (choiceSetStyleEnumToName.find(style) == choiceSetStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ChoiceSetStyle");
    }
    return choiceSetStyleEnumToName[style];
}
ChoiceSetStyle ChoiceSetStyleFromString(const std::string & style)
{
    std::unordered_map<std::string, ChoiceSetStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> choiceSetStyleNameToEnum;
    GetChoiceSetStyleEnumMappings(nullptr, &choiceSetStyleNameToEnum);

    if (choiceSetStyleNameToEnum.find(style) == choiceSetStyleNameToEnum.end())
    {
        return ChoiceSetStyle::Compact;
    }
    return choiceSetStyleNameToEnum[style];
}

const std::string TextInputStyleToString(TextInputStyle style)
{
    std::unordered_map<TextInputStyle, std::string, EnumHash> textInputStyleEnumToName;
    GetTextInputStyleEnumMappings(&textInputStyleEnumToName, nullptr);

    if (textInputStyleEnumToName.find(style) == textInputStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid TextInputStyle");
    }
    return textInputStyleEnumToName[style];
}

TextInputStyle TextInputStyleFromString(const std::string & style)
{
    std::unordered_map<std::string, TextInputStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> textInputStyleNameToEnum;
    GetTextInputStyleEnumMappings(nullptr, &textInputStyleNameToEnum);

    if (textInputStyleNameToEnum.find(style) == textInputStyleNameToEnum.end())
    {
        return TextInputStyle::Text;
    }
    return textInputStyleNameToEnum[style];
}

const std::string ContainerStyleToString(ContainerStyle style)
{
    std::unordered_map<ContainerStyle, std::string, EnumHash> containerStyleEnumToName;
    GetContainerStyleEnumMappings(&containerStyleEnumToName, nullptr);

    if (containerStyleEnumToName.find(style) == containerStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ContainerStyle");
    }
    return containerStyleEnumToName[style];
}

ContainerStyle ContainerStyleFromString(const std::string & style)
{
    std::unordered_map<std::string, ContainerStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> containerStyleNameToEnum;
    GetContainerStyleEnumMappings(nullptr, &containerStyleNameToEnum);

    if (containerStyleNameToEnum.find(style) == containerStyleNameToEnum.end())
    {
        return ContainerStyle::Default;
    }
    return containerStyleNameToEnum[style];
}

const std::string ActionAlignmentToString(ActionAlignment alignment)
{
    std::unordered_map<ActionAlignment, std::string, EnumHash> actionAlignmentEnumToName;
    GetActionAlignmentEnumMappings(&actionAlignmentEnumToName, nullptr);

    if (actionAlignmentEnumToName.find(alignment) == actionAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionAlignment");
    }
    return actionAlignmentEnumToName[alignment];
}

ActionAlignment ActionAlignmentFromString(const std::string & alignment)
{
    std::unordered_map<std::string, ActionAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> actionAlignmentNameToEnum;
    GetActionAlignmentEnumMappings(nullptr, &actionAlignmentNameToEnum);

    if (actionAlignmentNameToEnum.find(alignment) == actionAlignmentNameToEnum.end())
    {
        return ActionAlignment::Left;
    }
    return actionAlignmentNameToEnum[alignment];
}

const std::string IconPlacementToString(IconPlacement placement)
{
    std::unordered_map<IconPlacement, std::string, EnumHash> iconPlacementEnumToName;
    GetIconPlacementEnumMappings(&iconPlacementEnumToName, nullptr);

    if (iconPlacementEnumToName.find(placement) == iconPlacementEnumToName.end())
    {
        throw std::out_of_range("Invalid IconPlacement");
    }
    return iconPlacementEnumToName[placement];
}

IconPlacement IconPlacementFromString(const std::string& placement)
{
    std::unordered_map<std::string, IconPlacement, CaseInsensitiveHash, CaseInsensitiveEqualTo> iconPlacementNameToEnum;
    GetIconPlacementEnumMappings(nullptr, &iconPlacementNameToEnum);

    if (iconPlacementNameToEnum.find(placement) == iconPlacementNameToEnum.end())
    {
        return IconPlacement::AboveTitle;
    }
    return iconPlacementNameToEnum[placement];
}

const std::string VerticalContentAlignmentToString(VerticalContentAlignment verticalContentAlignment)
{
    std::unordered_map<VerticalContentAlignment, std::string, EnumHash> verticalContentAlignmentEnumToName;
    GetVerticalContentAlignmentEnumMappings(&verticalContentAlignmentEnumToName, nullptr);

    if (verticalContentAlignmentEnumToName.find(verticalContentAlignment) == verticalContentAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid VerticalContentAlignment");
    }
    return verticalContentAlignmentEnumToName[verticalContentAlignment];
}

VerticalContentAlignment VerticalContentAlignmentFromString(const std::string& verticalContentAlignment)
{
    std::unordered_map<std::string, VerticalContentAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> verticalContentAlignmentNameToEnum;
    GetVerticalContentAlignmentEnumMappings(nullptr, &verticalContentAlignmentNameToEnum);

    if (verticalContentAlignmentNameToEnum.find(verticalContentAlignment) == verticalContentAlignmentNameToEnum.end())
    {
        return VerticalContentAlignment::Top;
    }
    return verticalContentAlignmentNameToEnum[verticalContentAlignment];
}

}

#ifdef USE_CPPCORECHECK
#pragma warning(pop)
#endif
