#include "stdafx.h"
#include "CppUnitTest.h"
#include "SemanticVersion.h"
#include "AdaptiveCardParseException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(SemanticVersionTests)
    {
    public:
        TEST_METHOD(PositiveTest)
        {
            {
                SemanticVersion version("1", WildcardSupport::NotSupported);
                Assert::IsFalse(version.supportsWildcards());
                Assert::AreEqual(1U, version.get(SemanticVersionSegment::Major));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Minor));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Revision));
            }

            {
                SemanticVersion version("10.2", WildcardSupport::NotSupported);
                Assert::IsFalse(version.supportsWildcards());
                Assert::AreEqual(10U, version.get(SemanticVersionSegment::Major));
                Assert::AreEqual(2U, version.get(SemanticVersionSegment::Minor));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Revision));
            }

            {
                SemanticVersion version("100.20.3", WildcardSupport::NotSupported);
                Assert::IsFalse(version.supportsWildcards());
                Assert::AreEqual(100U, version.get(SemanticVersionSegment::Major));
                Assert::AreEqual(20U, version.get(SemanticVersionSegment::Minor));
                Assert::AreEqual(3U, version.get(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, version.get(SemanticVersionSegment::Revision));
            }

            {
                SemanticVersion version("1000.200.30.4", WildcardSupport::NotSupported);
                Assert::IsFalse(version.supportsWildcards());
                Assert::AreEqual(1000U, version.get(SemanticVersionSegment::Major));
                Assert::AreEqual(200U, version.get(SemanticVersionSegment::Minor));
                Assert::AreEqual(30U, version.get(SemanticVersionSegment::Build));
                Assert::AreEqual(4U, version.get(SemanticVersionSegment::Revision));
            }

            {
                SemanticVersion version("1000.200.30.40", WildcardSupport::NotSupported);
                Assert::IsFalse(version.supportsWildcards());
                Assert::AreEqual(1000U, version.get(SemanticVersionSegment::Major));
                Assert::AreEqual(200U, version.get(SemanticVersionSegment::Minor));
                Assert::AreEqual(30U, version.get(SemanticVersionSegment::Build));
                Assert::AreEqual(40U, version.get(SemanticVersionSegment::Revision));
            }
        }

        TEST_METHOD(WildcardPositiveTest)
        {
            SemanticVersion version("1.2.3.4", WildcardSupport::NotSupported);

            {
                SemanticVersion wildcard("*", WildcardSupport::Supported);
                Assert::IsTrue(wildcard.supportsWildcards());
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Major));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Major));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Minor));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Minor));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Build));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Revision));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Revision));
                Assert::IsTrue(version == wildcard);
                Assert::IsFalse(version < wildcard);
            }

            {
                SemanticVersion wildcard("1.*", WildcardSupport::Supported);
                Assert::IsTrue(wildcard.supportsWildcards());
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Major));
                Assert::AreEqual(1U, wildcard.get(SemanticVersionSegment::Major));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Minor));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Minor));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Build));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Revision));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Revision));
                Assert::IsTrue(version == wildcard);
                Assert::IsFalse(version < wildcard);
            }

            {
                SemanticVersion wildcard("1.2.*", WildcardSupport::Supported);
                Assert::IsTrue(wildcard.supportsWildcards());
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Major));
                Assert::AreEqual(1U, wildcard.get(SemanticVersionSegment::Major));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Minor));
                Assert::AreEqual(2U, wildcard.get(SemanticVersionSegment::Minor));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Build));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Build));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Revision));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Revision));
                Assert::IsTrue(version == wildcard);
                Assert::IsFalse(version < wildcard);
            }

            {
                SemanticVersion wildcard("1.2.3.*", WildcardSupport::Supported);
                Assert::IsTrue(wildcard.supportsWildcards());
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Major));
                Assert::AreEqual(1U, wildcard.get(SemanticVersionSegment::Major));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Minor));
                Assert::AreEqual(2U, wildcard.get(SemanticVersionSegment::Minor));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Build));
                Assert::AreEqual(3U, wildcard.get(SemanticVersionSegment::Build));
                Assert::IsTrue(wildcard.hasWildcard(SemanticVersionSegment::Revision));
                Assert::AreEqual(0U, wildcard.get(SemanticVersionSegment::Revision));
                Assert::IsTrue(version == wildcard);
                Assert::IsFalse(version < wildcard);
            }

            {
                SemanticVersion wildcard("1.2.3.4", WildcardSupport::Supported);
                Assert::IsTrue(wildcard.supportsWildcards());
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Major));
                Assert::AreEqual(1U, wildcard.get(SemanticVersionSegment::Major));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Minor));
                Assert::AreEqual(2U, wildcard.get(SemanticVersionSegment::Minor));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Build));
                Assert::AreEqual(3U, wildcard.get(SemanticVersionSegment::Build));
                Assert::IsFalse(wildcard.hasWildcard(SemanticVersionSegment::Revision));
                Assert::AreEqual(4U, wildcard.get(SemanticVersionSegment::Revision));
                Assert::IsTrue(version == wildcard);
                Assert::IsFalse(version < wildcard);
            }
        }

        TEST_METHOD(NegativeTest)
        {
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("text", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1234567890123456789012345678901234567890", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3.", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3.4.", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version(" 1.0", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.0 ", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("-1", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("0xF", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("F", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.c", WildcardSupport::NotSupported); });
        }

        TEST_METHOD(WildcardNegativeTest)
        {
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("invalid", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("**", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1*", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("*1", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.0*", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.*0", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("*.1", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.0*", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.*0", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3*", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.*3", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3.0*", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion version("1.2.3.*0", WildcardSupport::Supported); });
        }

        TEST_METHOD(CompareTest)
        {
            {
                SemanticVersion lhs("1", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.000000.0000000.0000000", WildcardSupport::NotSupported);
                Assert::IsTrue(lhs == rhs);
                Assert::IsFalse(lhs != rhs);
                Assert::IsFalse(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsTrue(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.001", WildcardSupport::NotSupported);
                Assert::IsTrue(lhs == rhs);
                Assert::IsFalse(lhs != rhs);
                Assert::IsFalse(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsTrue(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.0", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.1", WildcardSupport::NotSupported);
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.0", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.0.1", WildcardSupport::NotSupported);
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1.2", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.1.3", WildcardSupport::NotSupported);
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.1.3.100", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.1.4.1", WildcardSupport::NotSupported);
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }

            {
                SemanticVersion lhs("1.3.1", WildcardSupport::NotSupported);
                SemanticVersion rhs("1.10.2", WildcardSupport::NotSupported);
                Assert::IsFalse(lhs == rhs);
                Assert::IsTrue(lhs != rhs);
                Assert::IsTrue(lhs < rhs);
                Assert::IsFalse(lhs > rhs);
                Assert::IsFalse(lhs >= rhs);
                Assert::IsTrue(lhs <= rhs);
            }
        }

        TEST_METHOD(VersionWildcardTest)
        {
            SemanticVersion ver("2", WildcardSupport::NotSupported);
            SemanticVersion verOneOh("1", WildcardSupport::Supported);
            Assert::IsFalse(ver == verOneOh);
            Assert::IsFalse(verOneOh == ver);
            Assert::IsTrue(ver >= verOneOh);
            Assert::IsTrue(verOneOh <= ver);
            Assert::IsTrue(ver > verOneOh);
            Assert::IsFalse(ver < verOneOh);
            Assert::IsTrue(verOneOh < ver);

            SemanticVersion verTwoWildcard("2.*", WildcardSupport::Supported);
            Assert::IsTrue(ver == verTwoWildcard);
            Assert::IsFalse(ver > verTwoWildcard);

            SemanticVersion verThreeOh("3", WildcardSupport::Supported);
            Assert::IsFalse(ver == verThreeOh);
            Assert::IsTrue(ver < verThreeOh);

            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion verEmpty("", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion verEmpty("", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion verUnsupportedStar("*", WildcardSupport::NotSupported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion verInvalidStar("4.*.2.1", WildcardSupport::Supported); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { SemanticVersion verTooLarge("1234567890123456789012345678901234567890.1234567890123456789012345678901234567890.1234567890123456789012345678901234567890.1234567890123456789012345678901234567890", WildcardSupport::Supported); });
        }

        TEST_METHOD(VersionRangeTest)
        {
            SemanticVersion ver("2.0.0", WildcardSupport::NotSupported);
            Assert::IsTrue(Version::IsInRange("[1.9,2]", ver), L"exact range inclusive");
            Assert::IsTrue(Version::IsInRange("(1,2.1)", ver), L"exact range exclusive");
            Assert::IsFalse(Version::IsInRange("1.0", ver), L"exact match (not in range)");
            Assert::IsTrue(Version::IsInRange("2", ver), L"exact match (in range, no brackets)");
            Assert::IsTrue(Version::IsInRange("(1.5,)", ver), L"minimum exclusive");
            Assert::IsTrue(Version::IsInRange("[2]", ver), L"exact match");
            Assert::IsTrue(Version::IsInRange("(,5)", ver), L"maximum exclusive");
            Assert::IsTrue(Version::IsInRange("(,2.0.0.0]", ver), L"maximum inclusive");
            Assert::IsTrue(Version::IsInRange("[2.0,9)", ver), L"mixed range (min <= version < max)");
            Assert::IsTrue(Version::IsInRange("*", ver), L"wildcard major");
            Assert::IsTrue(Version::IsInRange("2.*", ver), L"wildcard minor");
            Assert::IsTrue(Version::IsInRange("2.0.*", ver), L"wildcard patch");
            Assert::IsTrue(Version::IsInRange("2.0.0.*", ver), L"wildcard revision");
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("steve", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("(1)", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("(,)", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("[,]", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("1,", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("1,2", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("1,2]", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("[1,2", ver); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { Version::IsInRange("[2,1]", ver); });
        }
    };
}
