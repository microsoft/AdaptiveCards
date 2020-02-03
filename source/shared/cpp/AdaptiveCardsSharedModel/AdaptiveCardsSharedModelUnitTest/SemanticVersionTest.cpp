// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "SemanticVersion.h"
#include "AdaptiveCardParseException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(SemanticVersionTests)
    {
    public:
        TEST_METHOD(PositiveTest)
        {
            {
                SemanticVersion version("1");
                Assert::AreEqual(1U, version.GetMajor());
                Assert::AreEqual(0U, version.GetMinor());
                Assert::AreEqual(0U, version.GetBuild());
                Assert::AreEqual(0U, version.GetRevision());
            }

            {
                SemanticVersion version("10.2");
                Assert::AreEqual(10U, version.GetMajor());
                Assert::AreEqual(2U, version.GetMinor());
                Assert::AreEqual(0U, version.GetBuild());
                Assert::AreEqual(0U, version.GetRevision());
            }

            {
                SemanticVersion version("100.20.3");
                Assert::AreEqual(100U, version.GetMajor());
                Assert::AreEqual(20U, version.GetMinor());
                Assert::AreEqual(3U, version.GetBuild());
                Assert::AreEqual(0U, version.GetRevision());
            }

            {
                SemanticVersion version("1000.200.30.4");
                Assert::AreEqual(1000U, version.GetMajor());
                Assert::AreEqual(200U, version.GetMinor());
                Assert::AreEqual(30U, version.GetBuild());
                Assert::AreEqual(4U, version.GetRevision());
            }

            {
                SemanticVersion version("1000.200.30.40");
                Assert::AreEqual(1000U, version.GetMajor());
                Assert::AreEqual(200U, version.GetMinor());
                Assert::AreEqual(30U, version.GetBuild());
                Assert::AreEqual(40U, version.GetRevision());
            }

        }

        TEST_METHOD(NegativeTest)
        {
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version(""); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("text"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1234567890123456789012345678901234567890"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1."); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2."); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3."); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3.4."); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version(" 1.0"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.0 "); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("-1"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("0xF"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("F"); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.c"); });
        }

        TEST_METHOD(CompareTest)
        {
            {
                SemanticVersion lhs("1");
                SemanticVersion rhs("1.000000.0000000.0000000");
                Assert::IsTrue(lhs == rhs);
                Assert::IsFalse(lhs != rhs);
                Assert::IsFalse(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsTrue(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1");
                SemanticVersion rhs("1.001");
                Assert::IsTrue(lhs == rhs);
                Assert::IsFalse(lhs != rhs);
                Assert::IsFalse(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsTrue(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.0");
                SemanticVersion rhs("1.1");
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.0");
                SemanticVersion rhs("1.0.1");
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1.2");
                SemanticVersion rhs("1.1.3");
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1.3.100");
                SemanticVersion rhs("1.1.4.1");
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.3.1");
                SemanticVersion rhs("1.10.2");
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }
        }
    };
}
