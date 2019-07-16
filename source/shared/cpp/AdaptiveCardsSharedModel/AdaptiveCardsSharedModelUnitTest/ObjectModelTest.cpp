// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"

#include "ChoiceSetInput.h"
#include "Column.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FeatureRegistration.h"
#include "Media.h"
#include "OpenUrlAction.h"
#include "ParseContext.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "ToggleInput.h"
#include "UnknownElement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ObjectModelTest)
    {
    public:
        // An empty JSON does not produce any selectAction
        TEST_METHOD(SelectActionEmptyJsonTest)
        {
            ParseContext context;

            Json::Value json;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                context,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON without selectAction key does not produce any selectAction
        TEST_METHOD(SelectActionNonExistentTest)
        {

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

            ParseContext context;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                context,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON with selectAction of incorrect type does not produce any selectAction
        TEST_METHOD(SelectActionInvalidTypeTest)
        {
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

            ParseContext context;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                context,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction->GetElementType() == ActionType::UnknownAction);
        }

        // A card JSON with an OpenUrl selectAction
        TEST_METHOD(SelectActionOpenUrlTest)
        {
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

            ParseContext context;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                context,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.OpenUrl"s);
        }

        // An arbitrary JSON with a Submit selectAction (for other elements such as Container, ColumnSet, etc.)
        TEST_METHOD(SelectActionAnyJsonTest)
        {
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

            ParseContext context;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                context,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.Submit"s);
        }

        TEST_METHOD(DuplicateIdSimpleTest)
        {
            std::string cardWithDuplicateIds = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\" : \"This card's has duplicate ids. Oh no!\"\
                    },\
                    { \
                      \"type\": \"Input.Text\", \
                      \"style\": \"text\", \
                      \"id\": \"duplicate\" \
                    }, \
                    { \
                      \"type\": \"Input.Text\", \
                      \"style\": \"url\", \
                      \"id\": \"duplicate\" \
                    } \
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult;
            Assert::ExpectException<AdaptiveCardParseException>([&]() { parseResult = AdaptiveCard::DeserializeFromString(cardWithDuplicateIds, "1.0"); });
        }

        TEST_METHOD(DuplicateIdNestedTest)
        {
            std::string cardWithDuplicateIds = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.Text\",\
                        \"placeholder\": \"Name\",\
                        \"style\": \"text\",\
                        \"maxLength\": 0,\
                        \"id\": \"duplicate\"\
                    }\
                ],\
                \"actions\": [\
                    {\
                        \"type\": \"Action.Submit\",\
                        \"title\": \"Submit\",\
                        \"data\": {\
                            \"id\": \"1234567890\"\
                        }\
                    },\
                    {\
                        \"type\": \"Action.ShowCard\",\
                        \"title\": \"Show Card\",\
                        \"card\": {\
                            \"type\": \"AdaptiveCard\",\
                            \"body\": [\
                                {\
                                    \"type\": \"Input.Text\",\
                                    \"placeholder\": \"enter comment\",\
                                    \"style\": \"text\",\
                                    \"maxLength\": 0,\
                                    \"id\": \"duplicate\"\
                                }\
                            ],\
                            \"actions\": [\
                                {\
                                    \"type\": \"Action.Submit\",\
                                    \"title\": \"OK\"\
                                }\
                            ]\
                        }\
                    }\
                ]\
               }";
            std::shared_ptr<ParseResult> parseResult;
            Assert::ExpectException<AdaptiveCardParseException>([&]() { parseResult = AdaptiveCard::DeserializeFromString(cardWithDuplicateIds, "1.0"); });
        }

        TEST_METHOD(MediaElementTest)
        {
            std::string cardWithMediaElement = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Media\",\
                        \"poster\" : \"http://adaptivecards.io/content/cats/1.png\",\
                        \"altText\" : \"This is a video\",\
                        \"sources\": [ \
                            {\
                                \"mimeType\": \"video/mp4\",\
                                \"url\" : \"http://source1.mp4\" \
                            },\
                            { \
                                \"mimeType\": \"video/avi\", \
                                \"url\" : \"http://source2.avi\" \
                            }\
                        ]\
                    }\
                ]\
            }";

            auto card = AdaptiveCard::DeserializeFromString(cardWithMediaElement, "1.0")->GetAdaptiveCard();
            std::shared_ptr<Media> mediaElement = std::static_pointer_cast<Media> (card->GetBody()[0]);

            Assert::IsTrue(mediaElement->GetElementType() == CardElementType::Media);
            Assert::AreEqual(mediaElement->GetElementTypeString(), "Media"s);
            Assert::AreEqual(mediaElement->GetPoster(), "http://adaptivecards.io/content/cats/1.png"s);
            Assert::AreEqual(mediaElement->GetAltText(), "This is a video"s);

            auto sources = mediaElement->GetSources();
            Assert::IsTrue(sources.size() == 2);
            Assert::AreEqual(sources[0]->GetMimeType(), "video/mp4"s);
            Assert::AreEqual(sources[0]->GetUrl(), "http://source1.mp4"s);
            Assert::AreEqual(sources[1]->GetMimeType(), "video/avi"s);
            Assert::AreEqual(sources[1]->GetUrl(), "http://source2.avi"s);
        }

        TEST_METHOD(ShowCardSerialization)
        {
            std::string cardWithShowCard = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"2.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\" : \"This card's action will show another card\"\
                    }\
                ],\
                \"actions\": [\
                    {\
                        \"type\": \"Action.ShowCard\",\
                        \"title\" : \"Action.ShowCard\",\
                        \"card\" : {\
                        \"type\": \"AdaptiveCard\",\
                        \"body\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"What do you think?\"\
                            }\
                        ],\
                        \"actions\": [\
                            {\
                                \"type\": \"Action.Submit\",\
                                \"title\" : \"Neat!\"\
                            }\
                        ]\
                        }\
                    }\
                ]\
            }";

            auto mainCard = AdaptiveCard::DeserializeFromString(cardWithShowCard, "2.0")->GetAdaptiveCard();
            auto showCard = (std::static_pointer_cast<ShowCardAction>(mainCard->GetActions()[0]))->GetCard();

            Assert::AreEqual(showCard->GetVersion(), "2.0"s);
            Assert::AreEqual(showCard->GetBody().size(), (size_t)1);
            Assert::IsTrue(showCard->GetBody()[0]->GetElementType() == CardElementType::TextBlock);
            Assert::AreEqual(std::static_pointer_cast<TextBlock>(showCard->GetBody()[0])->GetText(), "What do you think?"s);

            Assert::AreEqual(showCard->GetActions().size(), (size_t)1);
            Assert::IsTrue(showCard->GetActions()[0]->GetElementType() == ActionType::Submit);
            Assert::AreEqual(showCard->GetActions()[0]->GetTitle(), "Neat!"s);

            auto serializedShowCard = showCard->Serialize();
            auto roundTrippedShowCard = AdaptiveCard::DeserializeFromString(serializedShowCard, "2.0")->GetAdaptiveCard();

            Assert::AreEqual(showCard->GetVersion(), "2.0"s);
            Assert::AreEqual(roundTrippedShowCard->GetBody().size(), (size_t)1);
            Assert::IsTrue(roundTrippedShowCard->GetBody()[0]->GetElementType() == CardElementType::TextBlock);
            Assert::AreEqual(std::static_pointer_cast<TextBlock>(roundTrippedShowCard->GetBody()[0])->GetText(), "What do you think?"s);

            Assert::AreEqual(roundTrippedShowCard->GetActions().size(), (size_t)1);
            Assert::IsTrue(roundTrippedShowCard->GetActions()[0]->GetElementType() == ActionType::Submit);
            Assert::AreEqual(roundTrippedShowCard->GetActions()[0]->GetTitle(), "Neat!"s);
        }

        template<typename T>
            void runWrapTest(const std::vector<std::shared_ptr<BaseCardElement>> &body, int index, bool expectation)
        {
            auto testingElem = std::dynamic_pointer_cast<T>(body.at(index));
            if(testingElem)
            {
                Assert::AreEqual(testingElem->GetWrap(), expectation);
            }
            else
            {
                Assert::Fail(L"improper json payload");
            }
        }

        TEST_METHOD(ChoiceSetWrapParsingTest)
        {
            std::string testjson{ R"(
                {
                    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                    "type": "AdaptiveCard",
                    "version": "1.2",
                    "body": [
                        {
                            "type": "Input.ChoiceSet",
                            "id": "myColor",
                            "style": "compact",
                            "isMultiSelect": true,
                            "wrap": true,
                            "value": "1",
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
                        },
                        {
                            "type": "Input.ChoiceSet",
                            "id": "myColor2",
                            "style": "expanded",
                            "isMultiSelect": false,
                            "value": "1",
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
                        }
                    ]
                }
            )"};

            auto parseResult = AdaptiveCard::DeserializeFromString(testjson, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();

            runWrapTest<ChoiceSetInput>(body, 0, true);
            // default value test
            runWrapTest<ChoiceSetInput>(body, 1, false);
        }

        TEST_METHOD(ToggleInputWrapParsingTest)
        {
            std::string testjson{ R"(
                {
                    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                    "type": "AdaptiveCard",
                    "version": "1.2",
                    "body": [
                        {
                            "type": "Input.Toggle",
                            "id": "acceptTerms",
                            "wrap": true,
                            "title": "I accept the terms and agreements",
                            "value": "true",
                            "valueOn": "true",
                            "valueOff": "false"
                        },
                        {
                            "type": "Input.Toggle",
                            "id": "acceptTerms2",
                            "title": "I accept the terms and agreements",
                            "value": "true",
                            "valueOn": "true",
                            "valueOff": "false"
                        }
                    ]
                }
            )"};

            auto parseResult = AdaptiveCard::DeserializeFromString(testjson, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();

            runWrapTest<ToggleInput>(body, 0, true);
            // default value test
            runWrapTest<ToggleInput>(body, 1, false);
        }

        TEST_METHOD(ImplicitColumnTypeTest)
        {
            // Columns set to type "Column" or with type unset should parse correctly
            std::string columnTypeSetOrEmpty =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"items\": [\
                                ]\
                            },\
                            {\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";

            // Columns set to a bogus type should not parse correctly
            std::string columnTypeInvalid =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Elephant\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(columnTypeSetOrEmpty, "1.0");

            try
            {
                parseResult = AdaptiveCard::DeserializeFromString(columnTypeInvalid, "1.0");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Unable to parse element of type Elephant", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(ImplicitImageTypeInImageSetTest)
        {
            // Images set to type "Image" or with type unset should parse correctly within an image set
            std::string imageTypeSetOrEmpty =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ImageSet\",\
                        \"images\": [\
                            {\
                                \"type\": \"Image\",\
                                \"url\": \"http://adaptivecards.io/content/cats/1.png\"\
                            },\
                            {\
                                \"url\": \"http://adaptivecards.io/content/cats/1.png\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            // Images set to a bogus type should not parse correctly
            std::string imageTypeInvalid =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ImageSet\",\
                        \"images\": [\
                            {\
                                \"type\": \"Elephant\",\
                                \"url\": \"http://adaptivecards.io/content/cats/1.png\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(imageTypeSetOrEmpty, "1.0");

            try
            {
                parseResult = AdaptiveCard::DeserializeFromString(imageTypeInvalid, "1.0");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Unable to parse element of type Elephant", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }
    };
}
