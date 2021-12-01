// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "Column.h"
#include "ChoiceSetInput.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ElementTest)
    {
    public:
        TEST_METHOD(ColumnPixelWidthTest)
        {
            auto columnTest = std::make_shared<AdaptiveCards::Column>();
            Assert::AreEqual(0, columnTest->GetPixelWidth());
            Assert::AreEqual("Auto"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"Auto\"}\n"s, columnTest->Serialize());

            columnTest->SetWidth("20px"s);
            Assert::AreEqual(20, columnTest->GetPixelWidth());
            Assert::AreEqual("20px"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"20px\"}\n"s, columnTest->Serialize());

            columnTest->SetPixelWidth(40);
            Assert::AreEqual(40, columnTest->GetPixelWidth());
            Assert::AreEqual("40px"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"40px\"}\n"s, columnTest->Serialize());

            columnTest->SetWidth("Stretch");
            Assert::AreEqual(0, columnTest->GetPixelWidth());
            Assert::AreEqual("stretch"s, columnTest->GetWidth());
            Assert::AreEqual("{\"items\":[],\"type\":\"Column\",\"width\":\"stretch\"}\n"s, columnTest->Serialize());
        }

        TEST_METHOD(ChoiceSetMultiSelectFiltered)
        {
            std::string choiceSetFragment {R"(
            {
                "type": "Input.ChoiceSet",
                "id": "theChoiceSet",
                "isMultiSelect": true,
                "style": "filtered",
                "choices": [
                    {
                        "title": "Red",
                        "value": "1"
                    },
                    {
                        "title": "Green",
                        "value": "2"
                    },
                    {
                        "title": "Blue",
                        "value": "3"
                    }
                ]
            })"};

            ParseContext context{};
            auto parser = std::make_shared<AdaptiveCards::ChoiceSetInputParser>();
            auto choiceSet = std::static_pointer_cast<ChoiceSetInput>(parser->DeserializeFromString(context, choiceSetFragment));

            Assert::IsTrue(choiceSet->GetIsMultiSelect());
            Assert::IsTrue(ChoiceSetStyle::Filtered == choiceSet->GetChoiceSetStyle());
            Assert::AreEqual(context.warnings.size(), 1ui64);
            Assert::IsTrue(context.warnings[0]->GetStatusCode() == WarningStatusCode::InvalidValue);
            Assert::AreEqual(context.warnings[0]->GetReason(), "Input.ChoiceSet does not support filtering with multiselect"s);
        }
    };
}
