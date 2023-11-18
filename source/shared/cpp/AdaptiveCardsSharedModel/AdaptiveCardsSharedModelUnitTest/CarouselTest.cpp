
// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "stdafx.h"
#include "ActionSet.h"
#include "Carousel.h"
#include "CarouselPage.h"
#include "Enums.h"
#include "Image.h"
#include "ParseContext.h"
#include "ParseUtil.h"
#include "TextBlock.h"

using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(CarouselTest)
    {
    public:
        TEST_METHOD(Parse)
        {
            const std::string simpleCarouselJSON {R"({
                "type": "AdaptiveCard",
                "version": "1.6",
                "body": [
                    {
                        "type": "Carousel",
                        "pages": [
                            {
                                "type": "CarouselPage",
                                "id": "firstCarouselPage",
                                "items": [
                                    {
                                        "type": "Image",
                                        "url": "https://adaptivecards.io/content/cats/1.png",
                                        "altText": "Cat",
                                        "size": "medium"
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "actions": [
                    {
                        "type": "Action.OpenUrl",
                        "title": "See more",
                        "url": "https://adaptivecards.io"
                    }
                ]
            })"};

            auto parseResult = AdaptiveCard::DeserializeFromString(simpleCarouselJSON, "1.6");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(static_cast<size_t>(1),body.size());

            auto actions = card->GetActions();
            Assert::AreEqual(static_cast<size_t>(1), actions.size());

            auto carousel = std::dynamic_pointer_cast<Carousel>(body[0]);
            Assert::AreEqual<std::string>(carousel->GetElementTypeString(), CardElementTypeToString(CardElementType::Carousel));

            auto carouselPage = std::dynamic_pointer_cast<CarouselPage>(carousel->GetPages()[0]);
            Assert::AreEqual<std::string>(carouselPage->GetElementTypeString(), CardElementTypeToString(CardElementType::CarouselPage));

            auto image = std::dynamic_pointer_cast<Image>(carouselPage->GetItems()[0]);
            Assert::AreEqual<std::string>(image->GetElementTypeString(), CardElementTypeToString(CardElementType::Image));
        }

        TEST_METHOD(ParseWithProhibitedElements)
        {
            const std::string simpleCarouselJSON {R"(
                {
                    "type": "AdaptiveCard",
                    "version": "1.6",
                    "body": [
                        {
                            "type": "Carousel",
                            "pages": [
                                {
                                    "type": "CarouselPage",
                                    "id": "firstCarouselPage",
                                    "items": [
                                        {
                                            "type": "Carousel",
                                            "pages": [
                                                {
                                                    "type": "CarouselPage",
                                                    "id": "123",
                                                    "items": [
                                                        {
                                                            "type": "Image",
                                                            "url": "https://adaptivecards.io/content/cats/1.png",
                                                            "altText": "Cat",
                                                            "size": "medium"
                                                        }
                                                    ]
                                                }
                                            ]
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                }
            )"};

            auto parseResult = AdaptiveCard::DeserializeFromString(simpleCarouselJSON, "1.6");
            Assert::AreEqual(static_cast<size_t>(1), parseResult->GetWarnings().size());
            Assert::AreEqual<std::string>("type: Carousel is prohibited", parseResult->GetWarnings()[0]->GetReason());

            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(static_cast<size_t>(1),body.size());

            auto carousel = std::dynamic_pointer_cast<Carousel>(body[0]);
            Assert::AreEqual<std::string>(carousel->GetElementTypeString(), CardElementTypeToString(CardElementType::Carousel));

            auto carouselPage = std::dynamic_pointer_cast<CarouselPage>(carousel->GetPages()[0]);
            Assert::AreEqual<std::string>(carouselPage->GetElementTypeString(), CardElementTypeToString(CardElementType::CarouselPage));

            Assert::AreEqual(static_cast<size_t>(0), carouselPage->GetItems().size());
        }

        TEST_METHOD(ParseWithShowCardSelectAction)
        {
            const std::string simpleCarouselJSON {R"(
                {
                    "type": "AdaptiveCard",
                    "version": "1.6",
                    "body": [
                        {
                            "type": "Carousel",
                            "initialPage": 1,
                            "loop": false,
                            "heightInPixels": "100px",
                            "timer": 5000,
                            "pages": [
                                {
                                    "type": "CarouselPage",
                                    "id": "firstCarouselPage",
                                    "rtl": true,
                                    "items": [
                                        {
                                            "type": "Container",
                                            "items": [
                                                {
                                                    "type": "TextBlock",
                                                    "wrap": true,
                                                    "text": "This is a container with ShowCard action"
                                                }
                                            ],
                                            "selectAction": {
                                                "type": "Action.ShowCard",
                                                "title": "Action.ShowCard",
                                                "card": {
                                                    "type": "AdaptiveCard",
                                                    "body": [
                                                        {
                                                            "type": "TextBlock",
                                                            "text": "What do you think?"
                                                        }
                                                    ]
                                                }
                                            }
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                }
            )"};

            auto parseResult = AdaptiveCard::DeserializeFromString(simpleCarouselJSON, "1.6");
            auto card = parseResult->GetAdaptiveCard();
            Assert::AreEqual(static_cast<size_t>(1), parseResult->GetWarnings().size());
            Assert::AreEqual<std::string>("type: Action.ShowCard is prohibited", parseResult->GetWarnings()[0]->GetReason());

            auto body = card->GetBody();
            Assert::AreEqual(static_cast<size_t>(1),body.size());

            auto carousel = std::dynamic_pointer_cast<Carousel>(body[0]);
            Assert::AreEqual<std::string>(carousel->GetElementTypeString(), CardElementTypeToString(CardElementType::Carousel));
            Assert::AreEqual<bool>(carousel->GetAutoLoop().value(), false);
            Assert::AreEqual<int>(carousel->GetInitialPage().value(), static_cast<size_t>(1));
            Assert::AreEqual<std::string>(carousel->GetHeightInPixels(), "100px");
            Assert::AreEqual<int>(carousel->GetTimer().value(), 5000);

            auto carouselPage = std::dynamic_pointer_cast<CarouselPage>(carousel->GetPages()[0]);
            Assert::AreEqual<bool>(true, carouselPage->GetRtl().value());
            Assert::AreEqual<std::string>(carouselPage->GetElementTypeString(), CardElementTypeToString(CardElementType::CarouselPage));

            Assert::AreEqual(static_cast<size_t>(0), carouselPage->GetItems().size());
        }

        TEST_METHOD(ParseWithShowCardInActionSet)
        {
            const std::string simpleCarouselJSON {R"(
                {
                    "type": "AdaptiveCard",
                    "version": "1.6",
                    "body": [
                        {
                            "type": "Carousel",
                            "pages": [
                                {
                                    "type": "CarouselPage",
                                    "id": "firstCarouselPage",
                                    "items": [
                                        {
                                            "type": "ActionSet",
                                            "items": [
                                                {
                                                    "type": "Action.ShowCard",
                                                    "title": "Action.ShowCard",
                                                    "card": {
                                                        "type": "AdaptiveCard",
                                                        "body": [
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "What do you think?"
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
                }
            )"};

            auto parseResult = AdaptiveCard::DeserializeFromString(simpleCarouselJSON, "1.6");
            auto card = parseResult->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(static_cast<size_t>(1),body.size());

            auto carousel = std::dynamic_pointer_cast<Carousel>(body[0]);
            Assert::AreEqual<std::string>(carousel->GetElementTypeString(), CardElementTypeToString(CardElementType::Carousel));

            auto carouselPage = std::dynamic_pointer_cast<CarouselPage>(carousel->GetPages()[0]);
            Assert::AreEqual<std::string>(carouselPage->GetElementTypeString(), CardElementTypeToString(CardElementType::CarouselPage));

            Assert::AreEqual(static_cast<size_t>(1), carouselPage->GetItems().size());

            auto actionSet = std::dynamic_pointer_cast<ActionSet>(carouselPage->GetItems()[0]);
            Assert::AreEqual(static_cast<size_t>(0), actionSet->GetActions().size());
        }

        TEST_METHOD(Serialize)
        {
            const std::string simpleCarouselJSON {R"(
                {
                    "type": "AdaptiveCard",
                    "version": "1.6",
                    "body": [
                        {
                            "type": "Carousel",
                            "initialPage": 1,
                            "loop": false,
                            "heightInPixels": "100px",
                            "timer": 5000,
                            "pages": [
                                {
                                    "type": "CarouselPage",
                                    "id": "firstCarouselPage",
                                    "items": [
                                        {
                                            "type": "TextBlock",
                                            "wrap": true,
                                            "text": "Hello World!"
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                })"};

            auto parseResult = AdaptiveCard::DeserializeFromString(simpleCarouselJSON, "1.6");
            auto testCard = parseResult->GetAdaptiveCard();
            auto serializedCard = testCard->Serialize();

            auto roundTrippedCard = AdaptiveCard::DeserializeFromString(serializedCard, "1.6");
            auto card = roundTrippedCard->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(static_cast<size_t>(1),body.size());

            auto carousel = std::dynamic_pointer_cast<Carousel>(body[0]);
            Assert::AreEqual<std::string>(carousel->GetElementTypeString(), CardElementTypeToString(CardElementType::Carousel));
            Assert::AreEqual<bool>(carousel->GetAutoLoop().value(), false);
            Assert::AreEqual<int>(carousel->GetInitialPage().value(), static_cast<size_t>(1));
            Assert::AreEqual<std::string>(carousel->GetHeightInPixels(), "100px");
            Assert::AreEqual<int>(carousel->GetTimer().value(), 5000);

            auto carouselPage = std::dynamic_pointer_cast<CarouselPage>(carousel->GetPages()[0]);
            Assert::AreEqual<std::string>(carouselPage->GetElementTypeString(), CardElementTypeToString(CardElementType::CarouselPage));
            Assert::AreEqual(static_cast<size_t>(1), carouselPage->GetItems().size());

            auto textBlock = std::dynamic_pointer_cast<TextBlock>(carouselPage->GetItems()[0]);
            Assert::AreEqual(true, textBlock->GetWrap());
            Assert::AreEqual<std::string>("Hello World!", textBlock->GetText());
        }
    };
}
