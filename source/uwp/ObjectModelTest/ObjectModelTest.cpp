// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
// ObjectModelTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParseUtil.h"
#include "AdaptiveCardParseException.h"
#include "AdaptiveCard.h"
#include "TextBlock.h"
#include <memory>
#include <iostream>
#include <string>

using namespace std;
using namespace AdaptiveCards;
typedef  std::tuple< std::string, std::string> ParserTest;

int main(int argc, const char* argv[])
{
    std::vector<ParserTest> tests =
    {
        //std::make_tuple("TestJsonFiles\\imagetest.json", ""),
        std::make_tuple("TestJsonFiles\\textblock_noUnicode.json", ""),
        //std::make_tuple("TestJsonFiles\\nounicode.json", ""),
        //std::make_tuple("TestJsonFiles\\test1.json", ""),
    };

    for (size_t i = 0; i < tests.size(); i++)
    {
        auto test = tests[i];
        std::string path = std::get<0>(test);
        const std::string expectedResult = std::get<1>(test);
        printf("Running test %zu, (%s, %s)\n", i, path.c_str(), expectedResult.c_str());
        try
        {
            auto result = AdaptiveCard::DeserializeFromFile(path);
            if (!expectedResult.empty() || result == nullptr)
            {
                printf("  Failed test %zu, (%s, %s)\n", i, path.c_str(), expectedResult.c_str());
            }
            else
            {
                printf("  Passed test %zu, (%s, %s)\n", i, path.c_str(), expectedResult.c_str());
            }
        }
        catch (const AdaptiveCards::AdaptiveCardParseException& e)
        {
            printf("  Failed test %zu, (%s, %s)\n  ", i, path.c_str(), expectedResult.c_str());
            printf(e.what());
        }
        catch (...)
        {
            printf("  Failed test %zu, (%s, %s)\n", i, path.c_str(), expectedResult.c_str());
        }
    }

    return 0;
}
