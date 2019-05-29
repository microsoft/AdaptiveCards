// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "Container.h"
#include "Column.h"
#include "ColumnSet.h"
#include "ParseUtil.h"

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
        }

        TEST_METHOD(ColumnContainerStyleTest)
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

        TEST_METHOD(CanParseBleedPropertyTest)
        {
            std::vector<std::string> testJsonStrings {
            {R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "style": "emphasis",
                        "bleed": true,
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
            })"},

            {R"({
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
            })"}
            };

            std::vector<std::shared_ptr<Container>> containers{};
            for(auto json : testJsonStrings) {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(json, "1.2");
                std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
                std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
                containers.push_back(container);
            }

            Assert::IsTrue(containers.at(0)->GetBleed());
            Assert::IsFalse(containers.at(1)->GetBleed());
        }

        TEST_METHOD(CanSerializeBleedPropertyTest)
        {
            std::vector<std::string> testJsonStrings {
            {R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "style": "Emphasis",
                        "bleed": true,
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "Test"
                            }
                        ]
                    }
                ],
                "actions": [
                    {
                        "type": "Alert",
                        "title": "Submit",
                        "data": {
                            "id": "1234567890"
                        }
                    }],
                "version": "1.2"
            }
            )"},

            {R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "style": "Emphasis",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "Test"
                            }
                        ]
                    }
                ],
                "actions": [
                    {
                        "type": "Alert",
                        "title": "Submit",
                        "data": {
                            "id": "1234567890"
                        }
                    }],
                "version": "1.2"
            }
            )"}
            };

            std::vector<std::shared_ptr<Container>> containers{};
            for(auto json : testJsonStrings) {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(json, "1.2");
                const auto expectedValue = ParseUtil::GetJsonValueFromString(json);
                auto expectedString = ParseUtil::JsonToString(expectedValue);
                const auto serializedCard = parseResult->GetAdaptiveCard()->SerializeToJsonValue();
                auto serializedCardAsString = ParseUtil::JsonToString(serializedCard);
                Assert::AreEqual(expectedString, serializedCardAsString);
                Assert::IsTrue(expectedValue == serializedCard);
            }
        }

        TEST_METHOD(BleedPropertyConveysCorrectInformationTest)
        {
            std::string testJsonString {R"(
            {
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type": "AdaptiveCard",
                "version": "1.0",
                "body": [
                    {
                        "type": "ColumnSet",
                        "id":"0",
                        "columns": [
                            {
                                "type": "Column",
                                "id":"1",
                                "style": "emphasis",
                                "items": [
                                    {
                                        "type": "Container",
                                        "id":"2",
                                        "style": "default",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "id":"3",
                                                "text": "Container default style"
                                            },
                                            {
                                            "type": "Container",
                                            "id":"4",
                                            "style": "default",
                                            "items": [
                                                {
                                                    "type": "Container",
                                                    "id":"5",
                                                    "style": "emphasis",
                                                    "bleed":true,
                                                    "items": [
                                                        {
                                                            "id":"6",
                                                            "type": "TextBlock",
                                                            "text": "Container Emphasis style"
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
                ]
            }
            )"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnset= std::static_pointer_cast<ColumnSet>(elem);
            auto columns = columnset->GetColumns();

            std::shared_ptr<Column> column1 = std::static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(column1->GetStyle() == ContainerStyle::Emphasis);

            auto items = column1->GetItems();
            std::shared_ptr<Container> container1 = std::static_pointer_cast<Container>(items.back());
            Assert::IsTrue(container1->GetStyle() == ContainerStyle::Default);
            Assert::IsFalse(container1->GetCanBleed());

            auto items1 = container1->GetItems();
            std::shared_ptr<Container> container2 = std::static_pointer_cast<Container>(items1.back());
            Assert::AreEqual<std::string>("4", container2->GetId());
            Assert::IsTrue(container2->GetStyle() == ContainerStyle::Default);
            Assert::IsFalse(container2->GetCanBleed());

            auto items2 = container2->GetItems();
            std::shared_ptr<Container> container3 = std::static_pointer_cast<Container>(items2.back());
            Assert::AreEqual<std::string>("5", container3->GetId());
            Assert::IsTrue(container3->GetStyle() == ContainerStyle::Emphasis);
            Assert::IsTrue(container3->GetCanBleed());
            // check that the container can return the correct parent's ID to which it can expand
            Assert::IsTrue(container1->GetInternalId() == container3->GetParentalId());
        }

        TEST_METHOD(BleedPropertyColumnSetTest)
        {
            std::string testJsonString {R"(
            {
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type": "AdaptiveCard",
                "version": "1.2",
                "body": [
                    {
                        "type": "ColumnSet",
                        "style": "emphasis",
                        "bleed": true,
                        "columns": [
                            {
                                "type": "Column",
                                "width": "stretch",
                                "style": "default",
                                "bleed": true,
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Dis is a textblock",
                                        "wrap": true
                                    },
                                    {
                                        "type": "Container",
                                        "style": "emphasis",
                                        "bleed": true,
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Dis is a textblock"
                                            }
                                        ]
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "width": "stretch",
                                "style": "default",
                                "bleed": true,
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Dis is a textblock",
                                        "wrap": true
                                    },
                                    {
                                        "type": "Container",
                                        "style": "emphasis",
                                        "bleed": true,
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Dis is a textblock"
                                            }
                                        ]
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "width": "stretch",
                                "style": "default",
                                "bleed": true,
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Dis is a textblock",
                                        "wrap": true
                                    },
                                    {
                                        "type": "Container",
                                        "style": "emphasis",
                                        "bleed": true,
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Dis is a textblock"
                                            }
                                        ]
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "actions": [ ]
            }
            )"};

            using std::shared_ptr;
            using std::static_pointer_cast;

            shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            Assert::IsTrue(!parseResult->GetAdaptiveCard()->GetBody().empty());

            shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            shared_ptr<ColumnSet> columnset = static_pointer_cast<ColumnSet>(elem);
            Assert::IsTrue(columnset->GetStyle() == ContainerStyle::Emphasis);

            auto columns = columnset->GetColumns();
            shared_ptr<Column> column1 = static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(column1->GetStyle() == ContainerStyle::Default);
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft |
                            ContainerBleedDirection::BleedUp) == column1->GetBleedDirection());

            auto items = column1->GetItems();
            shared_ptr<Container> container = static_pointer_cast<Container>(items.back());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft |
                            ContainerBleedDirection::BleedRight) == container->GetBleedDirection());
            Assert::IsTrue(column1->GetInternalId() == container->GetParentalId()); 

            shared_ptr<Column> column2 = static_pointer_cast<Column>(columns.at(1));
            Assert::IsTrue(column2->GetStyle() == ContainerStyle::Default);
            Assert::IsTrue(column2->GetPadding());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedUp) == column2->GetBleedDirection());

            auto items2 = column2->GetItems();
            shared_ptr<Container> container2 = static_pointer_cast<Container>(items2.back());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft |
                            ContainerBleedDirection::BleedRight) == container2->GetBleedDirection());

            shared_ptr<Column> column3 = static_pointer_cast<Column>(columns.at(2));
            Assert::IsTrue(column3->GetStyle() == ContainerStyle::Default);
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedRight |
                            ContainerBleedDirection::BleedUp) == column3->GetBleedDirection());

            auto items3 = column3->GetItems();
            shared_ptr<Container> container3 = static_pointer_cast<Container>(items3.back());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedRight|
                            ContainerBleedDirection::BleedLeft) == container3->GetBleedDirection());
            Assert::IsTrue(column3->GetInternalId() == container3->GetParentalId()); 
        }

        TEST_METHOD(BleedPropertyNestedColumnSetTest)
        {
            std::string testJsonString {R"(
              {
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "ColumnSet",
                        "style": "default",
                        "columns": [
                            {
                                "type": "Column",
                                "style": "emphasis",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Has Padding",
                                        "wrap": true
                                    },
                                    {
                                        "type": "ColumnSet",
                                        "columns": [
                                            {
                                                "type": "Column",
                                                "style": "default",
                                                "items": [
                                                    {
                                                        "type": "TextBlock",
                                                        "text": "Bleed\n"
                                                    }
                                                ],
                                                "bleed": true,
                                                "width": "stretch"
                                            },
                                            {
                                                "type": "Column",
                                                "style": "default",
                                                "items": [
                                                    {
                                                        "type": "TextBlock",
                                                        "text": "Not Bleed"
                                                    }
                                                ],
                                                "bleed": true,
                                                "width": "stretch"
                                            },
                                            {
                                                "type": "Column",
                                                "style": "default",
                                                "items": [
                                                    {
                                                        "type": "TextBlock",
                                                        "text": "Bleed"
                                                    }
                                                ],
                                                "bleed": true,
                                                "width": "stretch"
                                            }
                                        ]
                                    }
                                ],
                                "width": "stretch"
                            },
                            {
                                "type": "Column",
                                "style": "emphasis",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Has Padding",
                                        "wrap": true
                                    },
                                    {
                                        "type": "ColumnSet",
                                        "columns": [
                                            {
                                                "type": "Column",
                                                "items": [
                                                    {
                                                        "type": "Container",
                                                        "style": "default",
                                                        "items": [
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "New TextBlock"
                                                            }
                                                        ],
                                                        "bleed": true
                                                    }
                                                ],
                                                "width": "stretch"
                                            },
                                            {
                                                "type": "Column",
                                                "items": [
                                                    {
                                                        "type": "Container",
                                                        "style": "default",
                                                        "items": [
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "New TextBlock"
                                                            }
                                                        ],
                                                        "bleed": true
                                                    }
                                                ],
                                                "width": "stretch"
                                            },
                                            {
                                                "type": "Column",
                                                "items": [
                                                    {
                                                        "type": "Container",
                                                        "style": "default",
                                                        "items": [
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "New TextBlock"
                                                            }
                                                        ],
                                                        "bleed": true
                                                    }
                                                ],
                                                "width": "stretch"
                                            }
                                        ]
                                    }
                                ],
                                "width": "stretch"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.1"
            }
            )"};

            using std::shared_ptr;
            using std::static_pointer_cast;

            shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            Assert::IsTrue(!parseResult->GetAdaptiveCard()->GetBody().empty());

            shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            shared_ptr<ColumnSet> columnset= static_pointer_cast<ColumnSet>(elem);
            Assert::IsTrue(columnset->GetStyle() == ContainerStyle::Default);

            auto columns = columnset->GetColumns();
            shared_ptr<Column> column1 = static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(column1->GetStyle() == ContainerStyle::Emphasis);
            Assert::IsFalse(column1->GetBleed());
            Assert::IsFalse(column1->GetCanBleed());

            auto items = column1->GetItems();
            shared_ptr<ColumnSet> innerconlumnset = static_pointer_cast<ColumnSet>(items.back());
            auto innercolumns = innerconlumnset->GetColumns();
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft) == innercolumns.at(0)->GetBleedDirection());
            Assert::IsTrue(innercolumns.at(0)->GetParentalId() == column1->GetInternalId());

            Assert::IsTrue(ContainerBleedDirection::BleedDown == innercolumns.at(1)->GetBleedDirection());

            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedRight) == innercolumns.at(2)->GetBleedDirection());
            Assert::IsTrue(innercolumns.at(2)->GetParentalId() == column1->GetInternalId());

            shared_ptr<Column> column2 = static_pointer_cast<Column>(columns.at(1));
            Assert::IsTrue(column2->GetStyle() == ContainerStyle::Emphasis);
            Assert::IsFalse(column2->GetCanBleed());

            auto items2 = column2->GetItems();
            shared_ptr<ColumnSet> innerconlumnset2 = static_pointer_cast<ColumnSet>(items2.back());
            auto innercolumns2 = innerconlumnset2->GetColumns();
            shared_ptr<Column> innercolumn0 = static_pointer_cast<Column>(innercolumns2.at(0));
            shared_ptr<Container> innercontainer = static_pointer_cast<Container>(innercolumn0->GetItems().at(0));
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft) == innercontainer->GetBleedDirection());
            Assert::IsTrue(innercontainer->GetParentalId() == column2->GetInternalId());

            shared_ptr<Column> innercolumn1 = static_pointer_cast<Column>(innercolumns2.at(1));
            shared_ptr<Container> innercontainer1 = static_pointer_cast<Container>(innercolumn1->GetItems().at(0));
            Assert::IsTrue(ContainerBleedDirection::BleedDown == innercontainer1->GetBleedDirection());

            shared_ptr<Column> innercolumn2 = static_pointer_cast<Column>(innercolumns2.at(2));
            shared_ptr<Container> innercontainer2 = static_pointer_cast<Container>(innercolumn2->GetItems().at(0));
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedRight) == innercontainer2->GetBleedDirection());
            Assert::IsTrue(innercontainer2->GetParentalId() == column2->GetInternalId());
        }

        TEST_METHOD(BleedPropertyNestedLeftAndRightRestrictedColumnSetTest)
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
                                "type": "ColumnSet",
                                "style": "default",
                                "columns": [
                                    {
                                        "type": "Column",
                                        "items": [
                                            {
                                                "type": "ColumnSet",
                                                "columns": [
                                                    {
                                                        "type": "Column",
                                                        "width": "stretch"
                                                    },
                                                    {
                                                        "type": "Column",
                                                        "width": "stretch"
                                                    },
                                                    {
                                                        "type": "Column",
                                                        "width": "stretch"
                                                    }
                                                ]
                                            }
                                        ],
                                        "width": "stretch"
                                    },
                                    {
                                        "type": "Column",
                                        "items": [
                                            {
                                                "type": "ColumnSet",
                                                "columns": [
                                                    {
                                                        "type": "Column",
                                                        "items": [
                                                            {
                                                                "type": "Container",
                                                                "style": "emphasis",
                                                                "bleed":true
                                                            }
                                                        ],
                                                        "width": "stretch"
                                                    },
                                                    {
                                                        "type": "Column",
                                                        "width": "stretch"
                                                    },
                                                    {
                                                        "type": "Column",
                                                        "items": [
                                                            {
                                                                "type": "Container",
                                                                "style": "emphasis",
                                                                "bleed": true
                                                            }
                                                        ],
                                                        "width": "stretch"
                                                    }
                                                ]
                                            }
                                        ],
                                        "width": "stretch"
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.2"
            }
            )"};

            using std::shared_ptr;
            using std::static_pointer_cast;

            shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            Assert::IsTrue(!parseResult->GetAdaptiveCard()->GetBody().empty());

            shared_ptr<Container> rootcontainer = static_pointer_cast<Container>(parseResult->GetAdaptiveCard()->GetBody().front());
            shared_ptr<ColumnSet> columnset =  static_pointer_cast<ColumnSet>(rootcontainer->GetItems().at(0));

            Assert::IsTrue(columnset->GetStyle() == ContainerStyle::Default);

            auto columns = columnset->GetColumns();
            shared_ptr<Column> columnRight = static_pointer_cast<Column>(columns.at(1));
            Assert::IsTrue(columnRight->GetStyle() == ContainerStyle::None);
            Assert::IsFalse(columnRight->GetCanBleed());

            auto items = columnRight->GetItems();
            shared_ptr<ColumnSet> innercolumnset = static_pointer_cast<ColumnSet>(items.back());
            Assert::IsFalse(innercolumnset->GetCanBleed());

            auto innercolumns = innercolumnset->GetColumns();
            Assert::IsFalse(innercolumns.at(0)->GetCanBleed());

            shared_ptr<Container> innercontainer = static_pointer_cast<Container>(innercolumns.at(0)->GetItems().at(0));
            Assert::IsTrue(innercontainer->GetPadding());
            Assert::IsTrue(innercontainer->GetBleed());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedUp) == innercontainer->GetBleedDirection());

            Assert::IsFalse(innercolumns.at(2)->GetCanBleed());

            shared_ptr<Container> innercontainerRight = static_pointer_cast<Container>(innercolumns.at(2)->GetItems().at(0));
            Assert::IsTrue(innercontainerRight->GetPadding());
            Assert::IsTrue(innercontainerRight->GetBleed());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedRight|
                            ContainerBleedDirection::BleedUp) == innercontainerRight->GetBleedDirection());
            Assert::IsTrue(innercontainerRight->GetParentalId() == columnset->GetInternalId());

            Assert::IsFalse(innercolumns.at(1)->GetCanBleed());
            shared_ptr<Column> columnLeft = static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(columnLeft->GetStyle() == ContainerStyle::None);
            Assert::IsFalse(columnLeft->GetCanBleed());
        }

        TEST_METHOD(BleedSequentialColumnSets)
        {
            std::string testJsonString {R"(
            {
                "type": "AdaptiveCard",
                "version":"1.0",
                "body": [
                    {
                        "type": "ColumnSet",
                        "columns": [
                            {
                                "type": "Column",
                                "style": "good",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 1"
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "style": "attention",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 2"
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "style": "warning",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 3"
                                    }
                                ]
                            }
                        ]
                    },
                    {
                        "type": "ColumnSet",
                        "columns": [
                            {
                                "type": "Column",
                                "style": "good",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 1"
                                    }
                                ],
                                "bleed": true
                            },
                            {
                                "type": "Column",
                                "style": "attention",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 2"
                                    }
                                ]
                            },
                            {
                                "type": "Column",
                                "style": "warning",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Column 3"
                                    }
                                ]
                            }
                        ]
                    }
                ]
            }
            )"};

            auto adaptiveCard = AdaptiveCard::DeserializeFromString(testJsonString, "1.2")->GetAdaptiveCard();
            Assert::IsTrue(adaptiveCard != nullptr);

            // The first column in the second column set should bleed to the left
            auto secondColumnSet = std::static_pointer_cast<ColumnSet>(adaptiveCard->GetBody()[1]);
            Assert::IsTrue(secondColumnSet->GetColumns()[0]->GetCanBleed());
            Assert::IsTrue((ContainerBleedDirection::BleedDown |
                            ContainerBleedDirection::BleedLeft) == secondColumnSet->GetColumns()[0]->GetBleedDirection());
        }
    };
}
