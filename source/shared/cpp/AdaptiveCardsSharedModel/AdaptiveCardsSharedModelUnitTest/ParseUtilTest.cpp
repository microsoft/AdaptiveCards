#include "stdafx.h"
#include "ParseUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ParseUtilTest)
    {
    public:
        TEST_METHOD(GetJsonValueFromStringTests)
        {
            Assert::ExpectException<AdaptiveCardParseException>([]() { ParseUtil::GetJsonValueFromString("definitely not json"); });
            auto jsonValue = ParseUtil::GetJsonValueFromString("{ \"foo\": \"bar\" }");
            Assert::AreEqual(jsonValue["foo"].asCString(), "bar", false);
            ParseUtil::ExpectString(jsonValue["foo"]);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectString(jsonValue); });

            // since we have a valid json object here, might as well test the success path of ThrowIfNotJsonObject
            ParseUtil::ThrowIfNotJsonObject(jsonValue);
        }

        TEST_METHOD(ThrowIfNotJsonObjectTests)
        {
            Json::Value value;
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ThrowIfNotJsonObject(value); });
        }
    };
}