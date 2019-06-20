// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

#define ENUM_TEST_START(ENUMNAME) \
    TEST_METHOD(ENUMNAME##Test)                     \

#define ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING) \
        Assert::AreEqual(ENUMNAME##ToString(VALIDVALUE), VALIDSTRING); \
        Assert::IsTrue(ENUMNAME##FromString(VALIDSTRING) == VALIDVALUE); \

#define ENUM_TEST_THROWING(ENUMNAME, VALIDVALUE, VALIDSTRING) \
    ENUM_TEST_START(ENUMNAME)                                           \
    {                                                                   \
        ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING);    \
        Assert::ExpectException<std::out_of_range>([]() { ENUMNAME##FromString("This is invalid."); }); \
    }                                                                   \

#define ENUM_TEST_WITH_DEFAULT(ENUMNAME, VALIDVALUE, VALIDSTRING, DEFAULTVALUE)  \
    ENUM_TEST_START(ENUMNAME)                                     \
    {                                                             \
        ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING);  \
        Assert::IsTrue(ENUMNAME##FromString("This is invalid.") == DEFAULTVALUE); \
    }                                                                   \

#define ENUM_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING) ENUM_TEST_WITH_DEFAULT(ENUMNAME, VALIDVALUE, VALIDSTRING, ENUMNAME::Default)

#define ENUM_TEST_WITH_REVERSE_MAP(ENUMNAME, VALIDVALUE, VALIDSTRING, ...) \
    ENUM_TEST_START(ENUMNAME)                                           \
    {                                                                   \
        ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING);    \
        Assert::IsTrue(ENUMNAME##FromString("This is invalid.") == ENUMNAME::Default); \
        std::unordered_map<std::string, ENUMNAME> reverseMap __VA_ARGS__; \
        for (const auto& key : reverseMap)                              \
        {                                                               \
            Assert::IsTrue(ENUMNAME##FromString(key.first) == key.second); \
        }                                                               \
    }                                                                   \


namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(EnumTests)
    {
    public:
        ENUM_TEST_THROWING(AdaptiveCardSchemaKey, AdaptiveCardSchemaKey::Accent, "accent"s);
        ENUM_TEST_WITH_DEFAULT(CardElementType, CardElementType::AdaptiveCard, "AdaptiveCard"s, CardElementType::Unknown);
        ENUM_TEST_WITH_DEFAULT(ActionType, ActionType::OpenUrl, "Action.OpenUrl"s, ActionType::Unsupported);
        ENUM_TEST_WITH_DEFAULT(HeightType, HeightType::Auto, "Auto"s, HeightType::Stretch);
        ENUM_TEST(Spacing, Spacing::None, "none"s);
        ENUM_TEST(SeparatorThickness, SeparatorThickness::Thick, "thick"s);
        ENUM_TEST_WITH_REVERSE_MAP(ImageStyle, ImageStyle::Person, "person"s, {{"normal", ImageStyle::Default}});
        ENUM_TEST_WITH_DEFAULT(ImageSize, ImageSize::Large, "Large"s, ImageSize::Auto);
        ENUM_TEST_WITH_DEFAULT(HorizontalAlignment, HorizontalAlignment::Center, "center"s, HorizontalAlignment::Left);
        ENUM_TEST(ForegroundColor, ForegroundColor::Accent, "Accent"s);
        ENUM_TEST_WITH_REVERSE_MAP(TextWeight, TextWeight::Bolder, "Bolder"s, {{"Normal", TextWeight::Default}});
        ENUM_TEST_WITH_REVERSE_MAP(TextSize, TextSize::Large, "Large"s, {{"Normal", TextSize::Default}});
        ENUM_TEST(FontType, FontType::Monospace, "Monospace"s);
        ENUM_TEST_WITH_DEFAULT(ActionsOrientation, ActionsOrientation::Vertical, "Vertical"s, ActionsOrientation::Horizontal);
        ENUM_TEST_WITH_DEFAULT(ActionMode, ActionMode::Popup, "Popup"s, ActionMode::Inline);
        ENUM_TEST_WITH_DEFAULT(ChoiceSetStyle, ChoiceSetStyle::Expanded, "Expanded"s, ChoiceSetStyle::Compact);
        ENUM_TEST_WITH_DEFAULT(TextInputStyle, TextInputStyle::Tel, "Tel"s, TextInputStyle::Text);
        ENUM_TEST(ContainerStyle, ContainerStyle::Emphasis, "Emphasis"s);
        ENUM_TEST_WITH_DEFAULT(ActionAlignment, ActionAlignment::Center, "Center"s, ActionAlignment::Left);
        ENUM_TEST_WITH_DEFAULT(IconPlacement, IconPlacement::LeftOfTitle, "LeftOfTitle"s, IconPlacement::AboveTitle);
        ENUM_TEST_WITH_DEFAULT(VerticalContentAlignment, VerticalContentAlignment::Center, "Center"s, VerticalContentAlignment::Top);
    };
}
