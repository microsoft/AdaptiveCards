#include "stdafx.h"
#include "Container.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ContainerStyleTest)
    {
    public:
        TEST_METHOD(CanCheckParentalContainerStyleTest)
        {
            std::string testJsonString {R"(
            {
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "style": "emphasis",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "Test"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.2"
            })"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
            auto containerStyle = container->GetStyle();
            Assert::AreEqual<std::string>(ContainerStyleToString(containerStyle), ContainerStyleToString(ContainerStyle::Emphasis));
        }

        TEST_METHOD(HaveValidPaddingFlagSetTest)
        {
            std::string testJsonString {R"(
            {
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "style": "emphasis",
                        "items": [
                            {
                                "type": "Container",
                                "style": "default"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.2"
            })"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
            auto items = container->GetItems();
            std::shared_ptr<Container> container2 = std::static_pointer_cast<Container>(items.back());
            // When container style is differrent from parent and child, child should get padding
            Assert::IsTrue(container2->GetPadding());
            //Assert::IsFalse(container->GetPadding());
        }
    };
}
