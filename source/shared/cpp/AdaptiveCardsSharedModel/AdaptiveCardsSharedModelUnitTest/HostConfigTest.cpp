// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "HostConfig.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(HostConfigTest)
    {
    public:
        TEST_METHOD(DeserializeTableTest)
        {
            const std::string tableConfigJson = R"({
               "table": {
                   "cellSpacing": 11
               }
            })";

            const auto hostConfig = HostConfig::DeserializeFromString(tableConfigJson);
            const auto tableConfig = hostConfig.GetTable();
            Assert::AreEqual(11ui32, tableConfig.cellSpacing);
        }

        TEST_METHOD(DeserializeDefaultTableTest)
        {
            const auto hostConfig = HostConfig::DeserializeFromString("{}");
            Assert::AreEqual(8ui32, hostConfig.GetTable().cellSpacing);
        }

        TEST_METHOD(DeserializeColumnHeaderTest)
        {
            const std::string columnHeaderJson = R"({
                "textStyles": {
                    "columnHeader": {
                        "size": "small",
                        "weight": "normal",
                        "color": "accent",
                        "isSubtle": true,
                        "fontType": "monospace"
                    }
                }
            })";

            const auto hostConfig = HostConfig::DeserializeFromString(columnHeaderJson);
            const auto columnConfig = hostConfig.GetTextStyles().columnHeader;

            Assert::IsTrue(columnConfig.weight == TextWeight::Default);
            Assert::IsTrue(columnConfig.size == TextSize::Small);
            Assert::IsTrue(columnConfig.isSubtle);
            Assert::IsTrue(columnConfig.color == ForegroundColor::Accent);
            Assert::IsTrue(columnConfig.fontType == FontType::Monospace);
        }

        TEST_METHOD(DeserializeDefaultColumnHeaderTest)
        {
            const auto hostConfig = HostConfig::DeserializeFromString("{}");
            const auto actualConfig = hostConfig.GetTextStyles().columnHeader;
            const TextStyleConfig expectedConfig{TextWeight::Bolder, TextSize::Default, false, ForegroundColor::Default, FontType::Default};

            Assert::IsTrue(expectedConfig.weight == actualConfig.weight);
            Assert::IsTrue(expectedConfig.size == actualConfig.size);
            Assert::IsTrue(expectedConfig.isSubtle == actualConfig.isSubtle);
            Assert::IsTrue(expectedConfig.color == actualConfig.color);
            Assert::IsTrue(expectedConfig.fontType == actualConfig.fontType);
        }

    };
}
