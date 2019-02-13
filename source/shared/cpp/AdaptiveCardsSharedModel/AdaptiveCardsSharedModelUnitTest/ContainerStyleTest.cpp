#include "stdafx.h"
#include "Container.h"
#include "Column.h"
#include "ColumnSet.h"

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

        TEST_METHOD(ColunmContainerStyleTest)
        {
            std::string testJsonString {R"(
            {
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
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
                                        "type": "TextBlock",
                                        "text": "No Style"
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "style": "default",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Default Style"
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "style": "emphasis",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Emphasis Style"
                                    },
                                    {
                                        "type": "Container",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Container no style"
                                            }
                                        ]
                                    },
                                    {
                                        "type": "Container",
                                        "style": "default",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Container default style"
                                            }
                                        ]
                                    },
                                    {
                                        "type": "Container",
                                        "style": "emphasis",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Container emphasis style"
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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnset= std::static_pointer_cast<ColumnSet>(elem);
            auto columns = columnset->GetColumns();
            std::shared_ptr<Column> column1 = std::static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(column1->GetStyle() == ContainerStyle::None);

            std::shared_ptr<Column> column2 = std::static_pointer_cast<Column>(columns.at(2));
            Assert::IsTrue(column2->GetStyle() == ContainerStyle::Emphasis);

            auto items = column2->GetItems(); 
            std::shared_ptr<Container> container1 = std::static_pointer_cast<Container>(items.at(1));
            Assert::IsTrue(container1->GetStyle() == ContainerStyle::None);
            Assert::IsFalse(container1->GetPadding());

            std::shared_ptr<Container> container2 = std::static_pointer_cast<Container>(items.at(2));
            Assert::IsTrue(container2->GetStyle() == ContainerStyle::Default);
            Assert::IsTrue(container2->GetPadding());

            std::shared_ptr<Container> container3 = std::static_pointer_cast<Container>(items.at(3));
            Assert::IsTrue(container3->GetStyle() == ContainerStyle::Emphasis);
            Assert::IsFalse(container3->GetPadding());
        }
    };
}
