#include "stdafx.h"
#include "CppUnitTest.h"
#include "Enums.h"
#include "TextBlock.h"
#include "ActionParserRegistration.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(FontStyle)
    {
    public:
        TEST_METHOD(DefineFromEmptyConstructor)
        {
            TextBlock emptyTB;
            Assert::IsTrue(emptyTB.GetFontStyle() == AdaptiveCards::FontStyle::Default);

            // Set FontStyle to Display
            emptyTB.SetFontStyle(AdaptiveCards::FontStyle::Default);
            Assert::IsTrue(emptyTB.GetFontStyle() == AdaptiveCards::FontStyle::Default);

            // Set FontStyle to Display
            emptyTB.SetFontStyle(AdaptiveCards::FontStyle::Display);
            Assert::IsTrue(emptyTB.GetFontStyle() == AdaptiveCards::FontStyle::Display);

            // Set FontStyle to Monospace
            emptyTB.SetFontStyle(AdaptiveCards::FontStyle::Monospace);
            Assert::IsTrue(emptyTB.GetFontStyle() == AdaptiveCards::FontStyle::Monospace);
        }

        TEST_METHOD(EmptyTextBlockSerialization)
        {
            TextBlock emptyTB;
            std::string json_data = emptyTB.Serialize();
            Assert::IsTrue(json_data == "{\"text\":\"\",\"type\":\"TextBlock\"}\n");

            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;

            TextBlockParser parser;
            auto parsedObject = parser.DeserializeFromString(elementParserRegistration, actionParserRegistration, warnings, json_data);

            Assert::IsTrue(emptyTB.GetFontStyle() == std::dynamic_pointer_cast<TextBlock>(parsedObject)->GetFontStyle());
        }
    };
}