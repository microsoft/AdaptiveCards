#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ParseUtilTest)
    {
    public:
        // An empty JSON does not produce any selectAction
        TEST_METHOD(SelectActionEmptyJsonTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            Json::Value json;

            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetSelectAction(
                elementParserRegistration,
                actionParserRegistration,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON without selectAction key does not produce any selectAction
        TEST_METHOD(SelectActionNonExistentTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // Card without card-level selectAction
            std::string cardStr = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Container\",\
                        \"items\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub.\",\
                                \"wrap\" : true\
                            }\
                        ]\
                    }\
                ]\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(cardStr);

            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetSelectAction(
                elementParserRegistration,
                actionParserRegistration,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON with selectAction of incorrect type does not produce any selectAction
        TEST_METHOD(SelectActionInvalidTypeTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // An arbitrary JSON with OpenUrl selectAction
            std::string str = "{\
                \"type\" : \"ColumnSet\",\
                \"selectAction\": {\
                    \"type\": \"Action.Invalid\",\
                    \"title\" : \"Submit\",\
                    \"data\": {\
                        \"x\": 13\
                    }\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetSelectAction(
                elementParserRegistration,
                actionParserRegistration,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }
        
        // A card JSON with an OpenUrl selectAction
        TEST_METHOD(SelectActionOpenUrlTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // Card with card-level OpenUrl selectAction
            std::string str = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Container\",\
                        \"items\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub.\",\
                                \"wrap\" : true\
                            }\
                        ]\
                    }\
                ],\
                \"selectAction\": {\
                    \"type\": \"Action.OpenUrl\",\
                    \"title\" : \"View\",\
                    \"url\" : \"http://select-action.io\"\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetSelectAction(
                elementParserRegistration,
                actionParserRegistration,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.OpenUrl"s);
        }
        
        // An arbitrary JSON with a Submit selectAction (for other elements such as Container, ColumnSet, etc.)
        TEST_METHOD(SelectActionAnyJsonTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // An arbitrary JSON with OpenUrl selectAction
            std::string str = "{\
                \"type\" : \"ColumnSet\",\
                \"selectAction\": {\
                    \"type\": \"Action.Submit\",\
                    \"title\" : \"Submit\",\
                    \"data\": {\
                        \"x\": 13\
                    }\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetSelectAction(
                elementParserRegistration,
                actionParserRegistration,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.Submit"s);
        }
    };
}