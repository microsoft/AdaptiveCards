#pragma once
#include "pch.h"

#ifdef _WIN32
#define strncasecmp _strnicmp
#else
#include <climits>
#include <strings.h>
#endif // _WIN32

namespace AdaptiveSharedNamespace {

struct EnumHash
{
    template <typename T>
    size_t operator()(T t) const
    {
        return static_cast<size_t>(t);
    }
};

struct CaseInsensitiveEqualTo {
    bool operator() (const std::string& lhs, const std::string& rhs) const {
        return strncasecmp(lhs.c_str(), rhs.c_str(), CHAR_MAX) == 0;
    }
};

struct CaseInsensitiveHash {
    size_t operator() (const std::string& keyval) const {
        return std::accumulate(keyval.begin(), keyval.end(), size_t{ 0 }, [](size_t acc, unsigned char c) { return acc + std::toupper(c); });
    }
};

enum class AdaptiveCardSchemaKey
{
    Accent = 0,
    ActionAlignment,
    ActionMode,
    ActionOrientation,
    Actions,
    ActionSetConfig,
    ActionsOrientation,
    AdaptiveCard,
    AllowCustomStyle,
    AllowInlinePlayback,
    AltText,
    Attention,
    BackgroundColor,
    BackgroundImage,
    BackgroundImageUrl,
    BaseCardElement,
    Body,
    Bolder,
    BorderColor,
    BorderThickness,
    Bottom,
    ButtonSpacing,
    Card,
    Center,
    Choices,
    ChoiceSet,
    Color,
    ColorConfig,
    ForegroundColors,
    Column,
    Columns,
    ColumnSet,
    Container,
    ContainerStyles,
    Dark,
    Data,
    DateInput,
    Default,
    DefaultPoster,
    Emphasis,
    ExtraLarge,
    Facts,
    FactSet,
    FallbackText,
    FontFamily,
    FontSizes,
    FontWeights,
    Good,
    Height,
    HorizontalAlignment,
    IconPlacement,
    IconSize,
    IconUrl,
    Id,
    Image,
    ImageBaseUrl,
    Images,
    ImageSet,
    ImageSize,
    ImageSizes,
    InlineTopMargin,
    IsMultiline,
    IsMultiSelect,
    IsRequired,
    IsSelected,
    IsSubtle,
    Items,
    Language,
    Large,
    Left,
    Light,
    Lighter,
    LineColor,
    LineThickness,
    Max,
    MaxActions,
    MaxImageHeight,
    MaxLength,
    MaxLines,
    MaxWidth,
    Media, 
    Medium,
    Method,
    MimeType,
    Min,
    NumberInput,
    Padding,
    Placeholder,
    PlayButton,
    Poster,
    Right,
    SelectAction,
    Separator,
    ShowActionMode,
    ShowCard,
    ShowCardActionConfig,
    Size,
    Small,
    Sources,
    Spacing,
    SpacingDefinition,
    Speak,
    Stretch,
    Style,
    Subtle,
    SupportsInteractivity,
    Text,
    TextBlock,
    TextConfig,
    TextInput,
    TextWeight,
    Thick,
    Thickness,
    TimeInput,
    Title,
    ToggleInput,
    Top,
    Type,
    Url,
    Value,
    ValueOff,
    ValueOn,
    Version,
    VerticalContentAlignment,
    Warning,
    Weight,
    Width,
    Wrap,
};

enum class TextSize
{
    Small = 0,
    Default,
    Medium,
    Large,
    ExtraLarge
};

enum class TextWeight {
    Lighter = 0,
    Default,
    Bolder
};

enum class ForegroundColor {
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
    Default = 0,
    Person
};

enum class ImageSize {
    None = 0,
    Auto,
    Stretch,
    Small,
    Medium,
    Large,
};

enum class TextInputStyle {
    Text = 0,
    Tel,
    Url,
    Email,
};

enum class CardElementType
{
    Unsupported = 0,
    AdaptiveCard,
    TextBlock,
    Image,
    Container,
    Column,
    ColumnSet,
    FactSet,
    Fact,
    ImageSet,
    ChoiceInput,
    ChoiceSetInput,
    DateInput,
    NumberInput,
    TextInput,
    TimeInput,
    ToggleInput,
    Custom,
    Unknown,
    Media
};

enum class ActionType
{
    Unsupported = 0,
    ShowCard,
    Submit,
    OpenUrl,
    Custom
};

enum class ActionAlignment
{
    Left = 0,
    Center,
    Right,
    Stretch,
};

enum class ChoiceSetStyle
{
    Compact = 0,
    Expanded
};

enum class SeparatorThickness {
    Default = 0,
    Thick,
};

enum class Spacing {
    Default = 0,
    None,
    Small,
    Medium,
    Large,
    ExtraLarge,
    Padding
};

enum class ActionsOrientation {
    Vertical = 0,
    Horizontal
};

enum class ActionMode {
    Inline = 0,
    Popup
};

enum class ContainerStyle {
    None,
    Default,
    Emphasis
};

enum class ErrorStatusCode {
    InvalidJson = 0,
    RenderFailed,
    RequiredPropertyMissing,
    InvalidPropertyValue,
    UnsupportedParserOverride
};

enum class WarningStatusCode {
    UnknownElementType = 0,
    UnknownPropertyOnElement,
    UnknownEnumValue,
    NoRendererForType,
    InteractivityNotSupported,
    MaxActionsExceeded,
    AssetLoadFailed,
    UnsupportedSchemaVersion,
    UnsupportedMediaType,
    InvalidMediaMix,
    InvalidColorFormat,
};

enum class DateTimePreparsedTokenFormat {
    RegularString = 0,
    Time,
    DateCompact,
    DateShort,
    DateLong
};

enum class IconPlacement
{
    AboveTitle = 0,
    LeftOfTitle
};

enum class VerticalContentAlignment
{
    Top = 0,
    Center,
    Bottom
};

enum class HeightType
{
    Auto = 0,
    Stretch
};

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type);
AdaptiveCardSchemaKey AdaptiveCardSchemaKeyFromString(const std::string& type);

const std::string CardElementTypeToString(CardElementType elementType);
CardElementType CardElementTypeFromString(const std::string& elementType);

const std::string ActionTypeToString(ActionType actionType);
ActionType ActionTypeFromString(const std::string& actionType);

const std::string HeightTypeToString(HeightType heightType);
HeightType HeightTypeFromString(const std::string& heightType);

const std::string HorizontalAlignmentToString(HorizontalAlignment alignment);
HorizontalAlignment HorizontalAlignmentFromString(const std::string& alignment);

const std::string ForegroundColorToString(ForegroundColor type);
ForegroundColor ForegroundColorFromString(const std::string& type);

const std::string TextWeightToString(TextWeight type);
TextWeight TextWeightFromString(const std::string& type);

const std::string TextSizeToString(TextSize size);
TextSize TextSizeFromString(const std::string& size);

const std::string ImageSizeToString(ImageSize size);
ImageSize ImageSizeFromString(const std::string& size);

const std::string SpacingToString(Spacing spacing);
Spacing SpacingFromString(const std::string& spacing);

const std::string SeparatorThicknessToString(SeparatorThickness separatorThickness);
SeparatorThickness SeparatorThicknessFromString(const std::string& separatorThickness);

const std::string ImageStyleToString(ImageStyle style);
ImageStyle ImageStyleFromString(const std::string& style);

const std::string ActionsOrientationToString(ActionsOrientation orientation);
ActionsOrientation ActionsOrientationFromString(const std::string& orientation);

const std::string ActionModeToString(ActionMode mode);
ActionMode ActionModeFromString(const std::string& mode);

const std::string ChoiceSetStyleToString(ChoiceSetStyle style);
ChoiceSetStyle ChoiceSetStyleFromString(const std::string& style);

const std::string TextInputStyleToString(TextInputStyle style);
TextInputStyle TextInputStyleFromString(const std::string& style);

const std::string ContainerStyleToString(ContainerStyle style);
ContainerStyle ContainerStyleFromString(const std::string& style);

const std::string ActionAlignmentToString(ActionAlignment alignment);
ActionAlignment ActionAlignmentFromString(const std::string& alignment);

const std::string IconPlacementToString(IconPlacement placement);
IconPlacement IconPlacementFromString(const std::string& placement);

const std::string VerticalContentAlignmentToString(VerticalContentAlignment verticalContentAlignment);
VerticalContentAlignment VerticalContentAlignmentFromString(const std::string& verticalContentAlignment);

template <typename T>
const std::unordered_map<std::string, T, CaseInsensitiveHash, CaseInsensitiveEqualTo>
GenerateStringToEnumMap(const std::unordered_map<T, std::string, EnumHash>& keyToStringMap)
{
    std::unordered_map<std::string, T, CaseInsensitiveHash, CaseInsensitiveEqualTo> result;
    for (auto& kv : keyToStringMap)
    {
        result[kv.second] = kv.first;
    }
    return result;
}
}
