#include "stdafx.h"
#include "CppUnitTest.h"
#include "Fact.h"
#include "ActionParserRegistration.h"

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

            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;

            auto parsedFact = Fact::DeserializeFromString(elementParserRegistration, actionParserRegistration, warnings, json_data);
            
            Assert::AreEqual(emptyFact.GetTitle(), parsedFact->GetTitle());
            Assert::AreEqual(emptyFact.GetValue(), parsedFact->GetValue());
        }
    };
}