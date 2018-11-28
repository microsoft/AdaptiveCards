#include "stdafx.h"
#include "CppUnitTest.h"
#include "AdaptiveBase64Util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(Base64Test)
    {
    public:

        bool ContainSameCharacters(const std::string& s, const std::vector<char>& v)
        {
            if (s.size() != v.size())
            {
                return false;
            }

            auto stringIterator = s.begin();
            auto vectorIterator = v.begin();
            for (; stringIterator != s.end() && vectorIterator != v.end(); stringIterator++, vectorIterator++)
            {
                if (*stringIterator != *vectorIterator)
                {
                    return false;
                }
            }

            return true;
        }

        TEST_METHOD(EncodingTest)
        {
            std::vector<std::string> decodedData{ "", "f", "fo", "foo", "foob", "fooba", "foobar" };
            std::vector<std::string> expectedEncodedData{ "", "Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy" };

            for (size_t i{}; i < decodedData.size(); ++i)
            {
                Assert::AreEqual(expectedEncodedData[i].c_str(),
                                 AdaptiveBase64Util::Encode(std::vector<char>(decodedData[i].begin(), decodedData[i].end())).c_str());
            }
        }

        TEST_METHOD(DecodingTest)
        {
            std::vector<std::string> expectedDecodedData{ "", "f", "fo", "foo", "foob", "fooba", "foobar" };
            std::vector<std::string> encodedData{ "", "Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy" };

            // According to this https://stackoverflow.com/questions/25419851/what-should-stdvectordata-return-if-the-vector-is-empty data in an empty vector will return null
            Assert::IsTrue(expectedDecodedData[0].size() ==
                AdaptiveBase64Util::Decode(std::string(encodedData[0].begin(), encodedData[0].end())).size());

            for (size_t i{1}; i < encodedData.size(); ++i)
            {
                Assert::IsTrue(ContainSameCharacters(expectedDecodedData[i],
                                                    AdaptiveBase64Util::Decode(std::string(encodedData[i].begin(), encodedData[i].end()))));
            }
        }

        TEST_METHOD(FailToDecodeTest)
        {
            std::vector<std::string> badUri{ "foo_bar", "foo(bar)", "foo-bar", "foo*bar", "foo\"bar", "foo&bar", "foo^bar", "foo#bar", "foo@bar", "foo!bar" };

            // If it crashes in any case the test will fail
            for (const auto& uri : badUri)
            {
                AdaptiveBase64Util::Decode(uri);
            }

        }
    };
}
