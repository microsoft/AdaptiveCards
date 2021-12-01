// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "ParseUtil.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ParseUtilTest)
    {
    public:
        static Json::Value s_GetJsonObject(const std::string &json)
        {
            std::istringstream jsonStream(json);
            Json::Value jsonValue;
            jsonStream >> jsonValue;
            return jsonValue;
        }

        static Json::Value s_GetValidJsonObject()
        {
            return s_GetJsonObject("{ \"foo\": \"bar\" }");
        }

        static Json::Value s_GetJsonObjectWithType(const std::string &typeName)
        {
            std::string jsonTemplate("{ \"foo\": \"bar\", \"type\": \"");
            jsonTemplate.append(typeName);
            jsonTemplate.append("\"}");
            return s_GetJsonObject(jsonTemplate);
        }

        static Json::Value s_GetJsonObjectWithAccent(const std::string &value)
        {
            std::string jsonTemplate("{ \"foo\": \"bar\", \"accent\": ");
            jsonTemplate.append(value);
            jsonTemplate.append("}");
            return s_GetJsonObject(jsonTemplate);
        }

        static void s_EmptyFn(const Json::Value&)
        {

        }

        static void s_AlwaysThrowsFn(const Json::Value&)
        {
            throw std::exception("always thrown");
        }

        TEST_METHOD(GetJsonValueFromStringTests)
        {
            Assert::ExpectException<AdaptiveCardParseException>([]() { ParseUtil::GetJsonValueFromString("definitely not json"); });
            auto jsonValue = ParseUtil::GetJsonValueFromString("{ \"foo\": \"bar\" }");
            Assert::AreEqual(jsonValue["foo"].asCString(), "bar", false);
        }

        TEST_METHOD(ThrowIfNotJsonObjectTests)
        {
            Json::Value value;
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ThrowIfNotJsonObject(value); });
            value = s_GetValidJsonObject();
            ParseUtil::ThrowIfNotJsonObject(value);
        }

        TEST_METHOD(ExpectKeyAndValueTypeTests)
        {
            auto value = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectKeyAndValueType(value, nullptr, &s_EmptyFn); });
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectKeyAndValueType(value, "steve", &s_EmptyFn); });
            ParseUtil::ExpectKeyAndValueType(value, "foo", &s_EmptyFn);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectKeyAndValueType(value, "FOO", &s_EmptyFn); });
            Assert::ExpectException<std::exception>([&]() { ParseUtil::ExpectKeyAndValueType(value, "foo", &s_AlwaysThrowsFn); });
        }

        TEST_METHOD(GetTypeAsStringTests)
        {
            auto value = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetTypeAsString(value); });
            Assert::AreEqual(ParseUtil::TryGetTypeAsString(value), ""s);

            std::string typeName("someType");
            auto typedValue = s_GetJsonObjectWithType(typeName);
            auto typeAsString = ParseUtil::GetTypeAsString(typedValue);
            Assert::AreEqual(typeName, typeAsString);
            Assert::AreEqual(ParseUtil::TryGetTypeAsString(typedValue), typeName);
        }

        TEST_METHOD(ExpectTypeStringTests)
        {
            auto missingType = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectTypeString(missingType, CardElementType::AdaptiveCard); });

            auto invalidType = s_GetJsonObjectWithType("InvalidType"s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectTypeString(invalidType, CardElementType::AdaptiveCard); });

            auto validType = s_GetJsonObjectWithType("AdaptiveCard"s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExpectTypeString(validType, CardElementType::Custom); });
            ParseUtil::ExpectTypeString(validType, CardElementType::AdaptiveCard);
        }

        TEST_METHOD(ExtractJsonValueTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::ExtractJsonValue(jsonObj, AdaptiveCardSchemaKey::Accent, true); });
            auto propertyValue = ParseUtil::ExtractJsonValue(jsonObj, AdaptiveCardSchemaKey::Accent, false);
            Assert::IsTrue(propertyValue.isNull());

            auto jsonObjWithAccent = s_GetJsonObjectWithAccent("true"s);
            propertyValue = ParseUtil::ExtractJsonValue(jsonObjWithAccent, AdaptiveCardSchemaKey::Accent, true);
            Assert::IsTrue(propertyValue.asBool());
        }

        TEST_METHOD(GetArrayTests)
        {
            bool throwsExpected = false;
            auto jsonObj = s_GetValidJsonObject();
            try
            {
                ParseUtil::GetArray(jsonObj, AdaptiveCardSchemaKey::Accent, true);
                throwsExpected = false;
            }
            catch (AdaptiveCardParseException e)
            {
                Assert::IsTrue(ErrorStatusCode::RequiredPropertyMissing == e.GetStatusCode());
                Assert::AreEqual("Could not parse required key: accent. It was not found"s, e.GetReason());
                throwsExpected = true;
            }
            Assert::IsTrue(throwsExpected);

            auto emptyRet = ParseUtil::GetArray(jsonObj, AdaptiveCardSchemaKey::Accent, false);
            Assert::IsTrue(emptyRet.isNull());

            try
            {
                auto jsonObjWithAccentString = s_GetJsonObjectWithAccent("true"s);
                ParseUtil::GetArray(jsonObjWithAccentString, AdaptiveCardSchemaKey::Accent, true);
                throwsExpected = false;
            }
            catch (AdaptiveCardParseException e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode());
                Assert::AreEqual("Could not parse specified key: accent. It was not an array"s, e.GetReason());
                throwsExpected = true;
            }
            Assert::IsTrue(throwsExpected);

            try
            {
                auto jsonObjWithAccentObject = s_GetJsonObjectWithAccent("{}"s);
                ParseUtil::GetArray(jsonObjWithAccentObject, AdaptiveCardSchemaKey::Accent, true);
                throwsExpected = false;
            }
            catch (AdaptiveCardParseException e)
            {
                Assert::IsTrue(ErrorStatusCode::InvalidPropertyValue == e.GetStatusCode());
                Assert::AreEqual("Could not parse specified key: accent. It was not an array"s, e.GetReason());
                throwsExpected = true;
            }
            Assert::IsTrue(throwsExpected);

            try
            {
                auto jsonObjWithAccentEmptyArray = s_GetJsonObjectWithAccent("[]"s);
                ParseUtil::GetArray(jsonObjWithAccentEmptyArray, AdaptiveCardSchemaKey::Accent, true);
                throwsExpected = false;
            }
            catch (AdaptiveCardParseException e)
            {
                Assert::IsTrue(ErrorStatusCode::RequiredPropertyMissing == e.GetStatusCode());
                Assert::AreEqual("Could not parse required key: accent. It was not found"s, e.GetReason());
                throwsExpected = true;
            }
            Assert::IsTrue(throwsExpected);

            auto jsonObjWithAccentArray = s_GetJsonObjectWithAccent("[\"thing1\", \"thing2\"]"s);
            auto arrayRet = ParseUtil::GetArray(jsonObjWithAccentArray, AdaptiveCardSchemaKey::Accent, true);
            Assert::AreEqual(arrayRet[0].asCString(), "thing1");
            Assert::AreEqual(arrayRet[1].asCString(), "thing2");
        }

        TEST_METHOD(GetBoolTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetBool(jsonObj, AdaptiveCardSchemaKey::Accent, false, true); });
            Assert::IsFalse(ParseUtil::GetBool(jsonObj, AdaptiveCardSchemaKey::Accent, false, false));

            auto jsonObjWithAccent = s_GetJsonObjectWithAccent("true"s);
            Assert::IsTrue(ParseUtil::GetBool(jsonObjWithAccent, AdaptiveCardSchemaKey::Accent, false, true));

            auto jsonObjWithAccentArray = s_GetJsonObjectWithAccent("[\"thing1\", \"thing2\"]"s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetBool(jsonObjWithAccentArray, AdaptiveCardSchemaKey::Accent, false, true); });
        }

        TEST_METHOD(GetIntTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetInt(jsonObj, AdaptiveCardSchemaKey::Accent, 0, true); });
            auto defaultValue = ParseUtil::GetInt(jsonObj, AdaptiveCardSchemaKey::Accent, 0, false);
            Assert::AreEqual(defaultValue, 0);

            auto jsonObjWithInvalidType = s_GetJsonObjectWithAccent("\"Invalid\""s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetInt(jsonObjWithInvalidType, AdaptiveCardSchemaKey::Accent, 0, true); });

            auto jsonObjWithValidType = s_GetJsonObjectWithAccent("1"s);
            auto actualValue = ParseUtil::GetInt(jsonObjWithValidType, AdaptiveCardSchemaKey::Accent, 0, false);
            Assert::AreEqual(actualValue, 1);
        }

        TEST_METHOD(GetOptionalIntTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            auto defaultValue = ParseUtil::GetOptionalInt(jsonObj, AdaptiveCardSchemaKey::Accent);
            Assert::IsFalse(defaultValue.has_value());

            auto jsonObjWithInvalidType = s_GetJsonObjectWithAccent("\"Invalid\""s);

            auto jsonObjWithValidType = s_GetJsonObjectWithAccent("1"s);
            auto actualValue = ParseUtil::GetOptionalInt(jsonObjWithValidType, AdaptiveCardSchemaKey::Accent);
            Assert::AreEqual(actualValue.value(), 1);
        }

        TEST_METHOD(GetUIntTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetUInt(jsonObj, AdaptiveCardSchemaKey::Accent, 0, true); });
            auto defaultValue = ParseUtil::GetUInt(jsonObj, AdaptiveCardSchemaKey::Accent, 0, false);
            Assert::AreEqual(defaultValue, 0U);

            auto jsonObjWithInvalidType = s_GetJsonObjectWithAccent("\"Invalid\""s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetUInt(jsonObjWithInvalidType, AdaptiveCardSchemaKey::Accent, 0, true); });

            auto jsonObjWithNegativeNumber = s_GetJsonObjectWithAccent("-1"s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetUInt(jsonObjWithNegativeNumber, AdaptiveCardSchemaKey::Accent, 0, true); });

            auto jsonObjWithValidType = s_GetJsonObjectWithAccent("1"s);
            auto actualValue = ParseUtil::GetUInt(jsonObjWithValidType, AdaptiveCardSchemaKey::Accent, 0, false);
            Assert::AreEqual(actualValue, 1U);
        }

        TEST_METHOD(GetStringTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetString(jsonObj, AdaptiveCardSchemaKey::Accent, true); });
            Assert::AreEqual(""s, ParseUtil::GetString(jsonObj, AdaptiveCardSchemaKey::Accent, false));

            auto jsonObjWithIntType = s_GetJsonObjectWithAccent("1"s);
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetString(jsonObjWithIntType, AdaptiveCardSchemaKey::Accent, true); });

            auto jsonObjWithValidType = s_GetJsonObjectWithAccent("\"Valid\""s);
            auto actualString = ParseUtil::GetString(jsonObjWithValidType, AdaptiveCardSchemaKey::Accent, true);
            Assert::AreEqual(actualString, "Valid"s);
        }

        TEST_METHOD(GetJsonStringTests)
        {
            auto jsonObj = s_GetValidJsonObject();
            Assert::ExpectException<AdaptiveCardParseException>([&]() { ParseUtil::GetJsonString(jsonObj, AdaptiveCardSchemaKey::Accent, true); });
            auto defaultValue = ParseUtil::GetJsonString(jsonObj, AdaptiveCardSchemaKey::Accent, false);
            Assert::AreEqual(defaultValue, ""s);

            auto jsonObjWithIntType = s_GetJsonObjectWithAccent("1"s);
            auto intString = ParseUtil::GetJsonString(jsonObjWithIntType, AdaptiveCardSchemaKey::Accent, false);
            Assert::AreEqual(intString, "1\n"s);

            auto jsonObjWithValidType = s_GetJsonObjectWithAccent("\"Valid\""s);
            auto actualString = ParseUtil::GetJsonString(jsonObjWithValidType, AdaptiveCardSchemaKey::Accent, true);
            Assert::AreEqual(actualString, "\"Valid\"\n"s);
        }
    };
}
