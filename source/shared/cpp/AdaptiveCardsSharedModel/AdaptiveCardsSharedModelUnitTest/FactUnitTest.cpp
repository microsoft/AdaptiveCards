// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "Fact.h"
#include "ParseContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(FactTest)
    {
    public:
        TEST_METHOD(DefineFromEmptyConstructor)
        {
            Fact emptyFact;
            Assert::IsTrue(emptyFact.GetTitle().empty());

            // Define & test title
            std::string testTitle = "1 Example Title!";
            emptyFact.SetTitle(testTitle);
            Assert::AreEqual(testTitle, emptyFact.GetTitle());

            // Define & test value
            std::string testValue = "1 Example Value!";
            emptyFact.SetValue(testValue);
            Assert::AreEqual(testValue, emptyFact.GetValue());

            std::string json_data = emptyFact.Serialize();
            Assert::IsTrue(json_data == "{\"title\":\"1 Example Title!\",\"value\":\"1 Example Value!\"}\n");

            ParseContext context{};

            auto parsedFact = Fact::DeserializeFromString(context, json_data);

            Assert::AreEqual(emptyFact.GetTitle(), parsedFact->GetTitle());
            Assert::AreEqual(emptyFact.GetValue(), parsedFact->GetValue());
        }
    };
}
