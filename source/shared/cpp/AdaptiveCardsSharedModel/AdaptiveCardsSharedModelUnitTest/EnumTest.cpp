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

#define ENUM_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING) \
    ENUM_TEST_START(ENUMNAME)                                           \
    {                                                                   \
        ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING);    \
        Assert::ExpectException<std::out_of_range>([]() { ENUMNAME##FromString("This is invalid."); }); \
    }                                                                   \

#define ENUM_TEST_WITH_REVERSE_MAP(ENUMNAME, VALIDVALUE, VALIDSTRING, ...) \
    ENUM_TEST_START(ENUMNAME)                                           \
    {                                                                   \
        ENUM_TO_FROM_STRING_TEST(ENUMNAME, VALIDVALUE, VALIDSTRING);    \
        Assert::ExpectException<std::out_of_range>([]() { ENUMNAME##FromString("This is invalid."); }); \
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
        ENUM_TEST(ActionAlignment, ActionAlignment::Center, "Center"s);  
        ENUM_TEST(ActionMode, ActionMode::Popup, "Popup"s);
        ENUM_TEST(ActionsOrientation, ActionsOrientation::Vertical, "Vertical"s);
        ENUM_TEST(ActionType, ActionType::OpenUrl, "Action.OpenUrl"s);
        ENUM_TEST(AdaptiveCardSchemaKey, AdaptiveCardSchemaKey::Accent, "accent"s);
        ENUM_TEST(CardElementType, CardElementType::AdaptiveCard, "AdaptiveCard"s);
        ENUM_TEST(ChoiceSetStyle, ChoiceSetStyle::Filtered, "Filtered"s);
        ENUM_TEST(ContainerStyle, ContainerStyle::Emphasis, "Emphasis"s);
        ENUM_TEST(FontType, FontType::Monospace, "Monospace"s);
        ENUM_TEST(ForegroundColor, ForegroundColor::Accent, "Accent"s);
        ENUM_TEST(HeightType, HeightType::Auto, "Auto"s);
        ENUM_TEST(HorizontalAlignment, HorizontalAlignment::Center, "center"s);
        ENUM_TEST(IconPlacement, IconPlacement::LeftOfTitle, "LeftOfTitle"s);
        ENUM_TEST(ImageSize, ImageSize::Large, "Large"s);
        ENUM_TEST_WITH_REVERSE_MAP(ImageStyle, ImageStyle::Person, "person"s, );
        ENUM_TEST(SeparatorThickness, SeparatorThickness::Thick, "thick"s);
        ENUM_TEST(Spacing, Spacing::None, "none"s);
        ENUM_TEST(TextInputStyle, TextInputStyle::Password, "Password"s);
        ENUM_TEST_WITH_REVERSE_MAP(TextSize, TextSize::Large, "Large"s, {{"Normal", TextSize::Default}});
        ENUM_TEST_WITH_REVERSE_MAP(TextWeight, TextWeight::Bolder, "Bolder"s, {{"Normal", TextWeight::Default}});
        ENUM_TEST(VerticalContentAlignment, VerticalContentAlignment::Center, "Center"s);
    };
}
