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
    TEST_CLASS(FallbackTests)
    {
    public:
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

        TEST_METHOD(ColumnFallback)
        {
            std::string cardStr = R"card({
                "type": "AdaptiveCard",
                "version": "1.0",
                "body": [
                {
                    "type": "ColumnSet",
                    "columns": [
                    {
                        "type": "Column",
                        "items": [
                        {
                            "type": "Graph"
                        }],
                        "fallback": {
                            "type": "Column",
                            "items": [
                            {
                                "type": "TextBlock",
                                "text": "Fallback"
                            }]
                        }
                    }]
                }]
            })card";

            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            Assert::IsTrue(0 == parseResult->GetWarnings().size());

            auto column = (std::static_pointer_cast<ColumnSet>(parseResult->GetAdaptiveCard()->GetBody().at(0)))->GetColumns().at(0);
            Assert::IsTrue(FallbackType::Content == column->GetFallbackType());

            auto fallbackColumn = column->GetFallbackContent();
            Assert::AreEqual("Column"s, fallbackColumn->GetElementTypeString());
        }

        TEST_METHOD(ColumnBadFallback)
        {
            std::string cardStr = R"card({
                "type": "AdaptiveCard",
                "version": "1.0",
                "body": [
                {
                    "type": "ColumnSet",
                    "columns": [
                    {
                        "type": "Column",
                        "items": [
                        {
                            "type": "Graph"
                        }],
                        "fallback": {
                            "type": "TextBlock",
                            "text": "Fallback"
                        }
                    }]
                }]
            })card";

            auto parseResult = AdaptiveCard::DeserializeFromString(cardStr, "1.2");
            Assert::IsTrue(1 == parseResult->GetWarnings().size());
            Assert::IsTrue(WarningStatusCode::UnknownElementType == parseResult->GetWarnings().at(0)->GetStatusCode());
            Assert::AreEqual("Column Fallback must be a Column. Fallback content dropped."s, parseResult->GetWarnings().at(0)->GetReason());

            auto column = (std::static_pointer_cast<ColumnSet>(parseResult->GetAdaptiveCard()->GetBody().at(0)))->GetColumns().at(0);
            Assert::IsTrue(FallbackType::None == column->GetFallbackType());
        }
    };
}
