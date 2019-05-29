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

        TEST_METHOD(ElementFallbackSerializationTest)
        {
            std::string cardStr = R"card({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type" : "AdaptiveCard",
                "version" : "1.2",
                "body" : [
                    {
                        "type": "TextBlock",
                        "text" : "TextBlock with fallback drop",
                        "fallback" : "drop"
                    },
                    {
                        "type": "TextBlock",
                        "text" : "TextBlock with fallback content",
                        "fallback" :
                        {
                            "type": "TextBlock",
                            "text" : "fallback content goes here"
                        }
                    }
                ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();
            auto textBlock1 = std::static_pointer_cast<TextBlock>(body.at(0));
            Assert::IsTrue(FallbackType::Drop == textBlock1->GetFallbackType(), L"Drop type");
            auto textBlock2 = std::static_pointer_cast<TextBlock>(body.at(1));
            Assert::IsTrue(FallbackType::Content == textBlock2->GetFallbackType(), L"Content type");
            auto fallbackTextBlock = std::static_pointer_cast<TextBlock>(textBlock2->GetFallbackContent());
            Assert::AreEqual(fallbackTextBlock->GetText().c_str(), "fallback content goes here");
            auto serializedCard = card->Serialize();
            Assert::AreEqual(serializedCard.c_str(),
                "{\"actions\":[],\"body\":[{\"fallback\":\"drop\",\"text\":\"TextBlock with fallback drop\",\"type\":\"TextBlock\"},{\"fallback\":{\"text\":\"fallback content goes here\",\"type\":\"TextBlock\"},\"text\":\"TextBlock with fallback content\",\"type\":\"TextBlock\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.2\"}\n");
        }

        TEST_METHOD(ActionFallbackSerializationTest)
        {
            std::string cardStr = R"card({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type" : "AdaptiveCard",
                "version" : "1.2",
                "body" : [
                    {
                        "type": "TextBlock",
                        "text" : "test text"
                    }
                ],
                "actions": [
                    {
                        "type": "Action.Submit",
                        "title": "Drop Test",
                        "fallback": "drop"
                    },
                    {
                        "type": "Action.OpenUrl",
                        "title": "Content Test",
                        "url": "http://example.com/",
                        "fallback":
                        {
                            "type": "Action.OpenUrl",
                            "title": "Fallback content",
                            "url": "http://example.com/fallback/"
                        }
                    }
                ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto actions = card->GetActions();
            auto submitAction = std::static_pointer_cast<SubmitAction>(actions.at(0));
            Assert::IsTrue(FallbackType::Drop == submitAction->GetFallbackType(), L"Drop type");
            auto openUrlAction = std::static_pointer_cast<OpenUrlAction>(actions.at(1));
            Assert::IsTrue(FallbackType::Content == openUrlAction->GetFallbackType(), L"Content type");
            auto fallbackAction = std::static_pointer_cast<OpenUrlAction>(openUrlAction->GetFallbackContent());
            Assert::IsTrue(fallbackAction->GetElementType() == ActionType::OpenUrl, L"openurl type check");
            Assert::AreEqual(fallbackAction->GetTitle().c_str(), "Fallback content", L"title comparison");
            Assert::AreEqual(fallbackAction->GetUrl().c_str(), "http://example.com/fallback/", L"url comparison");
            auto serializedCard = card->Serialize();
            Assert::AreEqual(serializedCard.c_str(),
                "{\"actions\":[{\"fallback\":\"drop\",\"title\":\"Drop Test\",\"type\":\"Action.Submit\"},{\"fallback\":{\"title\":\"Fallback content\",\"type\":\"Action.OpenUrl\",\"url\":\"http://example.com/fallback/\"},\"title\":\"Content Test\",\"type\":\"Action.OpenUrl\",\"url\":\"http://example.com/\"}],\"body\":[{\"text\":\"test text\",\"type\":\"TextBlock\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.2\"}\n");
        }

        TEST_METHOD(FallbackSimpleDuplicateTest)
        {
            std::string cardStr = R"card({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type" : "AdaptiveCard",
                "version" : "1.2",
                "body" : [
                    {
                        "type": "TextBlock",
                        "text" : "1",
                        "id": "1"
                    },
                    {
                        "type": "Container",
                        "id": "2",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text" : "3",
                                "id": "3",
                                "fallback":
                                {
                                    "type": "TextBlock",
                                    "text" : "3 fallback (this is okay)",
                                    "id": "3"
                                }
                            },
                            {
                                "type": "TextBlock",
                                "text" : "4",
                                "id": "4",
                                "fallback":
                                {
                                    "type": "Container",
                                    "id": "4",
                                    "items": [
                                        {
                                            "type": "TextBlock",
                                            "text" : "4 fallback container item. id is 3. this is *not* okay",
                                            "id": "3"
                                        }
                                    ]
                                }
                            }
                        ]
                    }
                ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::IdCollision == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Collision detected for id '3'", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(ElementFallbackDeepIdCollision)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "Container",
                  "id": "A",
                  "items": [
                    {
                      "type": "Container",
                      "id": "B",
                      "fallback": {
                        "type": "Container",
                        "id": "B",
                        "items": [
                          {
                            "type": "TextBlock",
                            "text": "B Container fallback textblock"
                          },
                          {
                            "type": "Image",
                            "url": "http://adaptivecards.io/content/cats/1.png"
                          }
                        ]
                      },
                      "items": [
                        {
                          "type": "ColumnSet",
                          "id": "C",
                          "columns": [
                            {
                              "type": "Column",
                              "id": "D",
                              "items": [
                                {
                                  "type": "Graph",
                                  "id": "E",
                                  "someProperty": "blah",
                                  "fallback": {
                                    "type": "Container",
                                    "id": "E",
                                    "items": [
                                      {
                                        "type": "Image",
                                        "id": "I",
                                        "url": "http://adaptivecards.io/content/cats/2.png"
                                      },
                                      {
                                        "type": "TextBlock",
                                        "id": "J",
                                        "text": "C ColumnSet fallback textblock"
                                      }
                                    ]
                                  }
                                }
                              ]
                            }
                          ]
                        }
                      ]
                    }
                  ]
                },
                {
                  "type": "TextBlock",
                  "id": "F",
                  "text": "F TextBlock"
                },
                {
                  "type": "Input.Text",
                  "id": "G",
                  "placeholder": "G Input.Text"
                },
                {
                  "type": "Graph",
                  "id": "H",
                  "someProperty": "foo",
                  "fallback": {
                    "type": "Container",
                    "id": "E",
                    "items": [
                      {
                        "type": "TextBlock",
                        "id": "K",
                        "text": "H Graph fallback TextBlock"
                      }
                    ]
                  }
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::IdCollision == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Collision detected for id 'E'", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(ElementFallbackDeepIdOkay)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "Container",
                  "id": "A",
                  "items": [
                    {
                      "type": "Container",
                      "id": "B",
                      "fallback": {
                        "type": "Container",
                        "id": "B",
                        "items": [
                          {
                            "type": "TextBlock",
                            "id": "C",
                            "text": "B Container fallback textblock"
                          },
                          {
                            "type": "Image",
                            "id": "Z",
                            "url": "http://adaptivecards.io/content/cats/1.png"
                          }
                        ]
                      },
                      "items": [
                        {
                          "type": "ColumnSet",
                          "id": "C",
                          "columns": [
                            {
                              "type": "Column",
                              "id": "D",
                              "items": [
                                {
                                  "type": "Graph",
                                  "id": "E",
                                  "someProperty": "blah",
                                  "fallback": {
                                    "type": "Container",
                                    "id": "E",
                                    "items": [
                                      {
                                        "type": "Image",
                                        "id": "I",
                                        "url": "http://adaptivecards.io/content/cats/2.png"
                                      },
                                      {
                                        "type": "TextBlock",
                                        "id": "J",
                                        "text": "C ColumnSet fallback textblock"
                                      }
                                    ]
                                  }
                                }
                              ]
                            }
                          ]
                        }
                      ]
                    }
                  ]
                },
                {
                  "type": "TextBlock",
                  "id": "F",
                  "text": "F TextBlock"
                },
                {
                  "type": "Input.Text",
                  "id": "G",
                  "fallback": "drop",
                  "placeholder": "G Input.Text"
                },
                {
                  "type": "Graph",
                  "id": "H",
                  "someProperty": "foo",
                  "fallback": {
                    "type": "Container",
                    "id": "L",
                    "items": [
                      {
                        "type": "TextBlock",
                        "id": "K",
                        "text": "H Graph fallback TextBlock"
                      }
                    ]
                  }
                }
              ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();

            {
                auto containerA = std::static_pointer_cast<Container>(body.at(0));
                Assert::IsTrue(containerA->GetId() == "A");
                auto containerAB = std::static_pointer_cast<Container>(containerA->GetItems()[0]);
                Assert::IsTrue(containerAB->GetId() == "B");
                Assert::IsTrue(containerAB->GetFallbackType() == FallbackType::Content);
                auto containerABFallback = std::static_pointer_cast<Container>(containerAB->GetFallbackContent());
                Assert::IsTrue(containerABFallback->GetId() == "B");
                auto containerABC = std::static_pointer_cast<ColumnSet>(containerAB->GetItems()[0]);
                Assert::IsTrue(containerABC->GetFallbackType() == FallbackType::None);
                auto containerABCD = std::static_pointer_cast<Column>(containerABC->GetColumns()[0]);
                auto containerABCDE = std::static_pointer_cast<UnknownElement>(containerABCD->GetItems()[0]);
                Assert::AreEqual("Graph", containerABCDE->GetElementTypeString().c_str());
                Assert::IsTrue(containerABCDE->GetId() == "E");
                Assert::IsTrue(containerABCDE->GetFallbackType() == FallbackType::Content);
                auto containerABCDEFallback = std::static_pointer_cast<Container>(containerABCDE->GetFallbackContent());
                Assert::IsTrue(containerABCDEFallback->GetId() == "E");
            }

            {
                auto inputG = std::static_pointer_cast<TextInput>(body.at(2));
                Assert::IsTrue(inputG->GetId() == "G");
                Assert::IsTrue(inputG->GetFallbackType() == FallbackType::Drop);
            }

            {
                auto unknownH = std::static_pointer_cast<UnknownElement>(body.at(3));
                Assert::IsTrue(unknownH->GetId() == "H");
                Assert::IsTrue(unknownH->GetFallbackType() == FallbackType::Content);
                auto unknownHL = std::static_pointer_cast<Container>(unknownH->GetFallbackContent());
                Assert::IsTrue(unknownHL->GetId() == "L");
            }
        }

       TEST_METHOD(DuplicateFallbackIdSimple)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "Container",
                  "fallback": {
                    "type": "Container",
                    "items": [
                      {
                        "type": "TextBlock",
                        "id": "B",
                        "text": "First B fallback textblock"
                      },
                      {
                        "type": "TextBlock",
                        "id": "B",
                        "text": "Second B fallback textblock"
                      }
                    ]
                  },
                  "items": [
                    {
                      "type": "TextBlock",
                      "text": "Non-fallback textblock"
                    }
                  ]
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::IdCollision == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Collision detected for id 'B'", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(DuplicateFallbackId)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "First textblock",
                  "fallback": {
                    "type": "TextBlock",
                    "id": "duplicate",
                    "text": "First fallback textblock"
                  }
                },
                {
                  "type": "TextBlock",
                  "text": "Second textblock",
                  "fallback": {
                    "type": "TextBlock",
                    "id": "duplicate",
                    "text": "Second fallback textblock"
                  }
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::IdCollision == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Collision detected for id 'duplicate'", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(DuplicateFallbackIdNestedOk)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "First textblock",
                  "id": "duplicate",
                  "fallback": {
                    "type": "TextBlock",
                    "id": "duplicate",
                    "text": "First fallback textblock",
                    "fallback": {
                      "type": "TextBlock",
                      "id": "duplicate",
                      "text": "Second fallback textblock"
                    }
                  }
                }
              ]
            })card";
            AdaptiveCard::DeserializeFromString(cardStr, "1.2");
        }

        TEST_METHOD(RequiresAndFallbackSerialization)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "This element requires version 1.2",
                  "requires": {
                     "adaptiveCards": "1.2",
                     "foobar": "2"
                  },
                  "fallback": {
                    "type": "TextBlock",
                    "text": "This element has no version requirement"
                  }
                }
              ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto serializedCard = card->Serialize();
            Assert::AreEqual("{\"actions\":[],\"body\":[{\"fallback\":{\"text\":\"This element has no version requirement\",\"type\":\"TextBlock\"},\"requires\":{\"adaptiveCards\":\"1.2.0.0\",\"foobar\":\"2.0.0.0\"},\"text\":\"This element requires version 1.2\",\"type\":\"TextBlock\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.2\"}\n",
                serializedCard.c_str());
        }

        TEST_METHOD(RequiresValidation)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "This element requires version 1.2",
                  "requires": {
                     "adaptiveCards": "1.2",
                     "foobar": "2"
                  }
                },
                {
                  "type": "TextBlock",
                  "text": "This element has no explicit requirements"
                }
              ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();
            auto textBlock = std::static_pointer_cast<TextBlock>(body[0]);
            auto textBlockNoRequires = std::static_pointer_cast<TextBlock>(body[1]);

            FeatureRegistration featureRegistration;

            featureRegistration.AddFeature("foobar", "2");
            Assert::IsTrue(textBlock->MeetsRequirements(featureRegistration));
            Assert::IsTrue(textBlockNoRequires->MeetsRequirements(featureRegistration));

            featureRegistration.RemoveFeature("foobar");
            Assert::IsFalse(textBlock->MeetsRequirements(featureRegistration));
            Assert::IsTrue(textBlockNoRequires->MeetsRequirements(featureRegistration));

            featureRegistration.AddFeature("foobar", "1.9.9.9");
            Assert::IsFalse(textBlock->MeetsRequirements(featureRegistration));
            Assert::IsTrue(textBlockNoRequires->MeetsRequirements(featureRegistration));

            featureRegistration.RemoveFeature("foobar");
            featureRegistration.AddFeature("foobar", "99");
            Assert::IsTrue(textBlock->MeetsRequirements(featureRegistration));
            Assert::IsTrue(textBlockNoRequires->MeetsRequirements(featureRegistration));
        }

        TEST_METHOD(NestedFallbacksSerialization)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "GraphV2",
                  "fallback": {
                    "type": "Graph",
                    "fallback": {
                      "type": "TextBlock",
                      "text": "No `Graph` support?"
                    }
                  }
                }
              ]
            })card";
            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            auto card = parseResult->GetAdaptiveCard();
            auto serializedCard = card->Serialize();
            Assert::AreEqual("{\"actions\":[],\"body\":[{\"fallback\":{\"fallback\":{\"text\":\"No `Graph` support?\",\"type\":\"TextBlock\"},\"type\":\"Graph\"},\"type\":\"GraphV2\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.2\"}\n",
                serializedCard.c_str());
        }

        TEST_METHOD(InvalidFallbackStringBody)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "textblock",
                  "fallback": "steve"
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("The only valid string value for the fallback property is 'drop'.", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(InvalidFallbackStringAction)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "textblock"
                }
              ],
              "actions": [
                {
                  "type": "Blahblah",
                  "fallback": "steve"
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("The only valid string value for the fallback property is 'drop'.", e.GetReason().c_str(), L"GetReason incorrect");
            }
        }

        TEST_METHOD(InvalidFallbackArray)
        {
            std::string cardStr = R"card({
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.2",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "textblock",
                  "fallback": [ { "blah": "2" } ]
                }
              ]
            })card";
            try
            {
                AdaptiveCard::DeserializeFromString(cardStr, "1.2");
                Assert::IsTrue(false, L"Deserializing should throw an exception");
            }
            catch (const AdaptiveCardParseException& e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode(), L"ErrorStatusCode incorrect");
                Assert::AreEqual("Invalid value for fallback", e.GetReason().c_str(), L"GetReason incorrect");
            }
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
    };
}
