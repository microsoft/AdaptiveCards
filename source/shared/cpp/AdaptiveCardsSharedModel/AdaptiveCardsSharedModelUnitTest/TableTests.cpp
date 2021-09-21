// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "stdafx.h"
#include "Table.h"
#include "TableCell.h"
#include "TableRow.h"
#include "TableColumnDefinition.h"
#include "ParseContext.h"
#include "ParseUtil.h"

using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(TableTests)
    {
    public:
        TEST_METHOD(TableCellParse)
        {
            const std::string tableCellFragment {R"(
            {
                "type": "TableCell",
                "items": [
                    {
                        "type": "TextBlock",
                        "text": "flim"
                    },
                    {
                        "type": "TextBlock",
                        "text": "iz-us"
                    }
                ],
                "rtl": true
            })"};

            // ensure parse
            ParseContext context{};
            auto tableCell = TableCell::DeserializeTableCellFromString(context, tableCellFragment);

            // ensure no additional properties
            const auto& additionalProperties = tableCell->GetAdditionalProperties();
            Assert::IsTrue(additionalProperties.isNull(), L"This TableCell shouldn't have any additionalProperties");

            // ensure RTL works (since TableCell is a Container)
            auto rtl = tableCell->GetRtl();
            Assert::IsTrue(rtl.has_value());
            Assert::IsTrue(rtl.value());

            // ensure we get expected items
            auto items = tableCell->GetItems();
            Assert::AreEqual(2ui64, items.size(), L"This TableCell should have 2 items");
            for (const auto& item : items)
            {
                Assert::AreEqual("TextBlock"s, item->GetElementTypeString(), L"Each item in this cell should be a TextBlock");
            }

            // ensure correct serialization
            auto serializedResult = tableCell->Serialize();
            Assert::AreEqual("{\"items\":[{\"text\":\"flim\",\"type\":\"TextBlock\"},{\"text\":\"iz-us\",\"type\":\"TextBlock\"}],\"rtl\":true,\"type\":\"TableCell\"}\n"s, serializedResult, L"TableCell should roundtrip correctly");
        }

        TEST_METHOD(TableEmptyParseTests)
        {
            const std::vector<std::string> jsonFragments {
                "{\"type\":\"TableRow\"}\n",
                "{\"type\":\"Table\"}\n",
                "{\"items\":[],\"type\":\"TableCell\"}\n" // since this is Container, it auto-emits items
            };

            ParseContext context{};
            for (const auto& fragment : jsonFragments)
            {
                std::shared_ptr<BaseElement> element;
                const auto parsedFragment = ParseUtil::GetJsonValueFromString(fragment);
                BaseCardElement::ParseJsonObject(context, parsedFragment, element);
                auto serializedObject = element->Serialize();
                Assert::AreEqual(fragment, serializedObject);
            }
        }

        TEST_METHOD(TableRowParse)
        {
            const std::string tableRowFragment { R"(
            {
                "type": "TableRow",
                "horizontalCellContentAlignment": "center",
                "verticalCellContentAlignment": "bottom",
                "style": "accent",
                "cells": [
                    {
                        "type": "TableCell",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "the first"
                            },
                            {
                                "type": "TextBlock",
                                "text": "the first part deux"
                            }
                        ],
                        "rtl": true
                    },
                    {
                        "type": "TableCell",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "the second"
                            }
                        ],
                        "rtl": true
                    }
                ]
            })"};

            // ensure parse
            ParseContext context{};
            auto tableRow = TableRow::DeserializeTableRowFromString(context, tableRowFragment);

            // ensure no additional properties
            const auto& additionalProperties = tableRow->GetAdditionalProperties();
            Assert::IsTrue(additionalProperties.isNull(), L"This TableRow shouldn't have any additionalProperties");

            // ensure we get expected items
            Assert::AreEqual(2ui64, tableRow->GetCells().size(), L"This TableRow should have 2 cells");
            Assert::IsTrue(ContainerStyle::Accent == tableRow->GetStyle());
            Assert::IsTrue(HorizontalAlignment::Center == tableRow->GetHorizontalCellContentAlignment());
            Assert::IsTrue(VerticalContentAlignment::Bottom == tableRow->GetVerticalCellContentAlignment());

            // ensure correct serialization
            auto serializedResult = tableRow->Serialize();
            Assert::AreEqual("{\"cells\":[{\"items\":[{\"text\":\"the first\",\"type\":\"TextBlock\"},{\"text\":\"the first part deux\",\"type\":\"TextBlock\"}],\"rtl\":true,\"type\":\"TableCell\"},{\"items\":[{\"text\":\"the second\",\"type\":\"TextBlock\"}],\"rtl\":true,\"type\":\"TableCell\"}],\"horizontalCellContentAlignment\":\"center\",\"style\":\"Accent\",\"type\":\"TableRow\",\"verticalCellContentAlignment\":\"Bottom\"}\n"s, serializedResult);
        }

        TEST_METHOD(TableElementsParserRegistration)
        {
            ParseContext context{};
            Assert::IsNotNull(context.elementParserRegistration->GetParser("Table").get(), L"Should be a registered parser for Table");
            Assert::IsNull(context.elementParserRegistration->GetParser("TableRow").get(), L"Should not be a registered parser for TableRow");
            Assert::IsNull(context.elementParserRegistration->GetParser("TableCell").get(), L"Should not be a registered parser for TableCell");
        }

        TEST_METHOD(TableColumnDefinitionSimpleParse)
        {
            const std::string columnDefinitionFragment = R"(
                {
                    "horizontalCellContentAlignment": "center",
                    "verticalCellContentAlignment": "bottom",
                    "width": 1
                })";

            // ensure parse
            ParseContext context{};
            auto columnDefinition = TableColumnDefinition::DeserializeFromString(context, columnDefinitionFragment);

            // ensure we get expected values
            auto width = columnDefinition->GetWidth();
            Assert::IsTrue(width.has_value());
            Assert::IsTrue(1 == width.value());

            Assert::IsFalse(columnDefinition->GetPixelWidth().has_value(), L"if we have a width, we shouldn't have a pixel width");
            Assert::IsTrue(HorizontalAlignment::Center == columnDefinition->GetHorizontalCellContentAlignment());
            Assert::IsTrue(VerticalContentAlignment::Bottom == columnDefinition->GetVerticalCellContentAlignment());

            // ensure correct serialization
            auto serializedResult = columnDefinition->Serialize();
            Assert::AreEqual("{\"horizontalCellContentAlignment\":\"center\",\"verticalCellContentAlignment\":\"Bottom\",\"width\":1}\n"s, serializedResult);
        }

        TEST_METHOD(TableColumnDefinitionPixelParse)
        {
            const std::string columnDefinitionFragment = R"(
                {
                    "horizontalCellContentAlignment": "right",
                    "verticalCellContentAlignment": "center",
                    "width": "100px"
                })";

            ParseContext context{};
            auto columnDefinition = TableColumnDefinition::DeserializeFromString(context, columnDefinitionFragment);

            auto width = columnDefinition->GetWidth();
            Assert::IsFalse(width.has_value(), L"if we have a pixel width, we shouldn't have a width");

            auto pixelWidth = columnDefinition->GetPixelWidth();
            Assert::IsTrue(pixelWidth.has_value());
            Assert::IsTrue(100 == pixelWidth.value());
            Assert::IsTrue(HorizontalAlignment::Right == columnDefinition->GetHorizontalCellContentAlignment());
            Assert::IsTrue(VerticalContentAlignment::Center == columnDefinition->GetVerticalCellContentAlignment());

            auto serializedResult = columnDefinition->Serialize();
            Assert::AreEqual("{\"horizontalCellContentAlignment\":\"right\",\"verticalCellContentAlignment\":\"Center\",\"width\":\"100px\"}\n"s, serializedResult);
        }

        TEST_METHOD(TableColumnDefinitionMissingUnitParse)
        {
            // ensure we emit a parse warning for missing units
            const std::string columnDefinitionFragment = R"(
                {
                    "width": "10"
                })";

            ParseContext context{};
            auto columnDefinition = TableColumnDefinition::DeserializeFromString(context, columnDefinitionFragment);
            Assert::IsFalse(columnDefinition->GetWidth().has_value(), L"A string width with no units should not result in width getting set");
            Assert::IsFalse(columnDefinition->GetPixelWidth().has_value(), L"A string width with no units should not result in pixel width getting set");
            Assert::IsFalse(context.warnings.empty(), L"Parsing a string with no units should yield warnings");
        }

        TEST_METHOD(TableColumnDefinitionInvalidParse)
        {
            // ensure we emit parse warnings for invalid units
            const std::string columnDefinitionInvalidUnitFragment = R"(
                {
                    "width": "10pixels"
                })";

            ParseContext context{};
            auto columnDefinition = TableColumnDefinition::DeserializeFromString(context, columnDefinitionInvalidUnitFragment);
            Assert::IsFalse(columnDefinition->GetWidth().has_value());
            Assert::IsFalse(context.warnings.empty(), L"Parsing a string with no units should yield warnings");
        }

        TEST_METHOD(TableFragmentParseValid)
        {
            const std::string tableFragment = R"(
            {
                "type": "Table",
                "gridStyle": "accent",
                "firstRowAsHeaders": true,
                "columns": [
                    {
                        "width": 1
                    },
                    {
                        "width": 1
                    },
                    {
                        "width": 3
                    }
                ],
                "rows": [
                    {
                        "type": "TableRow",
                        "cells": [
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Name",
                                        "wrap": true,
                                        "weight": "Bolder"
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Type",
                                        "wrap": true,
                                        "weight": "Bolder"
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Description",
                                        "wrap": true,
                                        "weight": "Bolder"
                                    }
                                ]
                            }
                        ],
                        "style": "accent"
                    },
                    {
                        "type": "TableRow",
                        "cells": [
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "columns",
                                        "wrap": true
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "ColumnDefinition[]",
                                        "wrap": true
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Defines the table's columns (number of columns, and column sizes).",
                                        "wrap": true
                                    }
                                ]
                            }
                        ]
                    },
                    {
                        "type": "TableRow",
                        "cells": [
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "rows",
                                        "wrap": true
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "TableRow[]",
                                        "wrap": true
                                    }
                                ]
                            },
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Defines the rows of the Table, each being a collection of cells. Rows are not required, which allows empty Tables to be generated via templating without breaking the rendering of the whole card.",
                                        "wrap": true
                                    }
                                ]
                            }
                        ]
                    }
                ]
            })";

            // ensure parse
            ParseContext context{};
            auto parser = std::make_shared<AdaptiveCards::TableParser>();
            auto table = std::static_pointer_cast<Table>(parser->DeserializeFromString(context, tableFragment));

            // ensure no additional properties
            const auto& additionalProperties = table->GetAdditionalProperties();
            Assert::IsTrue(additionalProperties.isNull());

            // ensure we get expected items
            const auto& columns = table->GetColumns();
            Assert::AreEqual(3ui64, columns.size());
            Assert::IsTrue(columns[0]->GetWidth().has_value() && !columns[0]->GetPixelWidth().has_value());
            Assert::IsTrue(columns[0]->GetWidth().value() == 1);
            Assert::IsFalse(columns[0]->GetPixelWidth().has_value());
            Assert::IsTrue(columns[1]->GetWidth().has_value() && !columns[1]->GetPixelWidth().has_value());
            Assert::IsTrue(columns[1]->GetWidth().value() == 1);
            Assert::IsFalse(columns[1]->GetPixelWidth().has_value());
            Assert::IsTrue(columns[2]->GetWidth().has_value() && !columns[2]->GetPixelWidth().has_value());
            Assert::IsTrue(columns[2]->GetWidth().value() == 3);
            Assert::IsFalse(columns[2]->GetPixelWidth().has_value());

            const auto& rows = table->GetRows();
            Assert::AreEqual(3ui64, rows.size());
            for (const auto& row : rows)
            {
                const auto& cells = row->GetCells();
                Assert::AreEqual(columns.size(), cells.size());
            }

            // ensure correct serialization
            auto serializedResult = table->Serialize();
            Assert::AreEqual(R"({"columns":[{"width":1},{"width":1},{"width":3}],"gridStyle":"Accent","rows":[{"cells":[{"items":[{"text":"Name","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"},{"items":[{"text":"Type","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"},{"items":[{"text":"Description","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"}],"style":"Accent","type":"TableRow"},{"cells":[{"items":[{"text":"columns","type":"TextBlock","wrap":true}],"type":"TableCell"},{"items":[{"text":"ColumnDefinition[]","type":"TextBlock","wrap":true}],"type":"TableCell"},{"items":[{"text":"Defines the table's columns (number of columns, and column sizes).","type":"TextBlock","wrap":true}],"type":"TableCell"}],"type":"TableRow"},{"cells":[{"items":[{"text":"rows","type":"TextBlock","wrap":true}],"type":"TableCell"},{"items":[{"text":"TableRow[]","type":"TextBlock","wrap":true}],"type":"TableCell"},{"items":[{"text":"Defines the rows of the Table, each being a collection of cells. Rows are not required, which allows empty Tables to be generated via templating without breaking the rendering of the whole card.","type":"TextBlock","wrap":true}],"type":"TableCell"}],"type":"TableRow"}],"type":"Table"}
)"s,
                serializedResult);
        }

        TEST_METHOD(TableCardParseValid)
        {
            const std::string tableCard = R"(
            {
                "type": "AdaptiveCard",
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.5",
                "body": [
                    {
                        "type": "Table",
                        "gridStyle": "accent",
                        "firstRowAsHeaders": true,
                        "columns": [
                            {
                                "width": 1
                            },
                            {
                                "width": 1
                            },
                            {
                                "width": 3
                            }
                        ],
                        "rows": [
                            {
                                "type": "TableRow",
                                "cells": [
                                    {
                                        "type": "TableCell",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Name",
                                                "wrap": true,
                                                "weight": "Bolder"
                                            }
                                        ]
                                    },
                                    {
                                        "type": "TableCell",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Type",
                                                "wrap": true,
                                                "weight": "Bolder"
                                            }
                                        ]
                                    },
                                    {
                                        "type": "TableCell",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Description",
                                                "wrap": true,
                                                "weight": "Bolder"
                                            }
                                        ]
                                    }
                                ],
                                "style": "accent"
                            },
                            {
                                "type": "TableRow",
                                "cells": [
                                    {
                                        "type": "TableCell",
                                        "style": "good",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "columns",
                                                "wrap": true
                                            }
                                        ]
                                    },
                                    {
                                        "type": "TableCell",
                                        "style": "warning",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "some text",
                                                "wrap": true
                                            }
                                        ]
                                    },
                                    {
                                        "type": "TableCell",
                                        "style": "accent",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "some text #2",
                                                "wrap": true
                                            }
                                        ]
                                    }
                                ]
                            }
                        ]
                    }
                ]
            })";

            auto result = AdaptiveCard::DeserializeFromString(tableCard, "1.5");
            auto card = result->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(1ui64, body.size());
            auto bodyElem = body.at(0);
            Assert::AreEqual("Table"s, bodyElem->GetElementTypeString());

            auto serializedCard = card->Serialize();
            Assert::AreEqual(R"({"actions":[],"body":[{"columns":[{"width":1},{"width":1},{"width":3}],"gridStyle":"Accent","rows":[{"cells":[{"items":[{"text":"Name","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"},{"items":[{"text":"Type","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"},{"items":[{"text":"Description","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"}],"style":"Accent","type":"TableRow"},{"cells":[{"items":[{"text":"columns","type":"TextBlock","wrap":true}],"style":"Good","type":"TableCell"},{"items":[{"text":"some text","type":"TextBlock","wrap":true}],"style":"Warning","type":"TableCell"},{"items":[{"text":"some text #2","type":"TextBlock","wrap":true}],"style":"Accent","type":"TableCell"}],"type":"TableRow"}],"type":"Table"}],"type":"AdaptiveCard","version":"1.5"}
)"s, serializedCard);
        }

        TEST_METHOD(TableCardParseOrphanedTableRow)
        {
            const std::string tableCard = R"(
            {
                "type": "AdaptiveCard",
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.5",
                "body": [
                    {
                        "type": "TableRow",
                        "cells": [
                            {
                                "type": "TableCell",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "text": "..."
                                    }
                                ]
                            }
                        ]
                    }
                ]
            })";

            auto result = AdaptiveCard::DeserializeFromString(tableCard, "1.5");
            auto card = result->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(1ui64, body.size());
            auto bodyElem = body.at(0);
            Assert::AreEqual("TableRow"s, bodyElem->GetElementTypeString(),
                L"An orphaned TableRow should deserialize with its type string intact");
            Assert::AreEqual(CardElementTypeToString(CardElementType::Unknown),
                CardElementTypeToString(bodyElem->GetElementType()),
                L"An orphaned TableRow should implemented with UnknownElement");

            auto serializedCard = card->Serialize();
            Assert::AreEqual(R"({"actions":[],"body":[{"cells":[{"items":[{"text":"...","type":"TextBlock"}],"type":"TableCell"}],"type":"TableRow"}],"type":"AdaptiveCard","version":"1.5"}
)"s, serializedCard);
        }

        TEST_METHOD(TableCardParseOrphanedTableCell)
        {
            const std::string tableCard = R"(
            {
                "type": "AdaptiveCard",
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.5",
                "body": [
                    {
                        "type": "TableCell",
                        "items": [
                            {
                                "type": "TextBlock",
                                "text": "Name",
                                "wrap": true,
                                "weight": "Bolder"
                            }
                        ]
                    }
                ]
            })";

            auto result = AdaptiveCard::DeserializeFromString(tableCard, "1.5");
            auto card = result->GetAdaptiveCard();
            auto body = card->GetBody();
            Assert::AreEqual(1ui64, body.size());
            auto bodyElem = body.at(0);
            Assert::AreEqual("TableCell"s, bodyElem->GetElementTypeString(),
                L"An orphaned TableCell should deserialize with its type string intact");
            Assert::AreEqual(CardElementTypeToString(CardElementType::Unknown),
                CardElementTypeToString(bodyElem->GetElementType()),
                L"An orphaned TableCell should implemented with UnknownElement");
            auto serializedCard = card->Serialize();
            Assert::AreEqual(R"({"actions":[],"body":[{"items":[{"text":"Name","type":"TextBlock","weight":"Bolder","wrap":true}],"type":"TableCell"}],"type":"AdaptiveCard","version":"1.5"}
)"s, serializedCard);
        }

        TEST_METHOD(TableCardParseWithImpliedTypes)
        {
            const std::string tableCard = R"(
            {
                "type": "AdaptiveCard",
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.5",
                "body": [
                    {
                        "type": "Table",
                        "columns": [
                            {
                                "width": 1
                            }
                        ],
                        "rows": [
                            {
                                "cells": [
                                    {
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "text": "Text goes here."
                                            }
                                        ]
                                    }
                                ]
                            }
                        ]
                    }
                ]
            })";

            auto result = AdaptiveCard::DeserializeFromString(tableCard, "1.5");
            auto card = result->GetAdaptiveCard();

            auto body = card->GetBody();
            Assert::AreEqual(1ui64, body.size());

            auto bodyElem = body.at(0);
            Assert::AreEqual(CardElementTypeToString(CardElementType::Table),
                CardElementTypeToString(bodyElem->GetElementType()),
                L"only item in the body should be a Table");

            auto table = std::static_pointer_cast<Table>(bodyElem);

            auto columns = table->GetColumns();
            Assert::AreEqual(1ui64, columns.size(), L"should be only one column");

            auto rows = table->GetRows();
            Assert::AreEqual(1ui64, rows.size(), L"should be only one row");

            auto row = rows.at(0);
            Assert::AreEqual(CardElementTypeToString(CardElementType::TableRow),
                CardElementTypeToString(row->GetElementType()),
                L"should be a real TableRow");

            auto cells = row->GetCells();
            Assert::AreEqual(1ui64, cells.size(), L"should be only one cell");

            auto cell = cells.at(0);
            Assert::AreEqual(CardElementTypeToString(CardElementType::TableCell),
                CardElementTypeToString(cell->GetElementType()),
                L"should be a real TableCell");
        }
    };
}
