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
    };
}
