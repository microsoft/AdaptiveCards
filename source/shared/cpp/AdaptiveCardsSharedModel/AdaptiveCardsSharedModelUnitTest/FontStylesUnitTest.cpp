// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "TextBlock.h"
#include "ParseContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(FontType)
    {
    public:
        TEST_METHOD(DefineFromEmptyConstructor)
        {
            TextBlock emptyTB;
            Assert::IsTrue(emptyTB.GetFontType() == AdaptiveCards::FontType::Default);

            // Set FontType to Display
            emptyTB.SetFontType(AdaptiveCards::FontType::Default);
            Assert::IsTrue(emptyTB.GetFontType() == AdaptiveCards::FontType::Default);

            // Set FontType to Monospace
            emptyTB.SetFontType(AdaptiveCards::FontType::Monospace);
            Assert::IsTrue(emptyTB.GetFontType() == AdaptiveCards::FontType::Monospace);
        }

        TEST_METHOD(EmptyTextBlockSerialization)
        {
            TextBlock emptyTB;
            std::string json_data = emptyTB.Serialize();
            Assert::IsTrue(json_data == "{\"text\":\"\",\"type\":\"TextBlock\"}\n");

            ParseContext context {};

            TextBlockParser parser;
            auto parsedObject = parser.DeserializeFromString(context, json_data);

            Assert::IsTrue(emptyTB.GetFontType() == std::dynamic_pointer_cast<TextBlock>(parsedObject)->GetFontType());
        }
    };
}
