// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "TextBlock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(TextParsingTests)
    {
    public:
        TEST_METHOD(HtmlEncodingPositiveTest)
        {
            const std::string textBlockText = _GetTextBlockText("\"Foo &amp; Bar\"&nbsp;&lt;admin@example.com&gt;");
            const std::string expectedText = "\"Foo & Bar\" <admin@example.com>";
            Assert::AreEqual(expectedText, textBlockText, L"Make sure supported HTML entities are decoded");
        }

        TEST_METHOD(HtmlEncodingAmpTest)
        {
            // we should be doing a single pass through HTML character encoding, so the resulting "&nbsp;" below
            // shouldn't be further decoded to " "
            const std::string textBlockText = _GetTextBlockText("&amp;nbsp;");
            Assert::AreEqual("&nbsp;"s, textBlockText);
        }

        // Test for strings that should roundtrip without modification
        TEST_METHOD(HtmlEncodingRoundtripTests)
        {
            const std::vector<std::string> testStrings =
                {
                    "some test text",
                    "&foo;",
                    "&am p;"
                };

            for (const auto& testString : testStrings)
            {
                const std::string textBlockText = _GetTextBlockText(testString);
                Assert::AreEqual(testString, textBlockText);
            }
        }

    private:
        std::string _GetTextBlockText(const std::string& testString)
        {
            TextBlock textBlock;
            textBlock.SetText(testString);
            return textBlock.GetText();
        }
    };
}
