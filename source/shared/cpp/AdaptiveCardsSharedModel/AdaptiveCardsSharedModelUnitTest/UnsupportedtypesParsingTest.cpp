// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "UnknownElement.h"
#include "UnknownAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(UnknownElementParsing)
    {
    public:
        TEST_METHOD(CanGetCustomJsonPayload)
        {
            const std::string testJsonString{
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Random\",\
                        \"payload\": \"You can even draw attention to certain text with color\"\
                    }\
                ]\
            }"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            Assert::AreEqual(elem->GetElementTypeString(), std::string("Random"));

            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            std::string jsonString = ParseUtil::JsonToString(value);

            const std::string expected{R"({"payload":"You can even draw attention to certain text with color","type":"Random"}
)"};
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(CanGetCustomJsonPayloadWithKnownElementFollowing)
        {
            const std::string testJsonString{
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Unknown\",\
                        \"payload\": \"You can even draw attention to certain text with color\"\
                    },\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"You can even draw attention to certain text with color\",\
                        \"wrap\": true,\
                        \"color\": \"attention\",\
                        \"unknown\": \"testing unknown\"\
                    }\
                ]\
            }"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            std::string jsonString = ParseUtil::JsonToString(value);

            const std::string expected {R"({"payload":"You can even draw attention to certain text with color","type":"Unknown"})""\n"};
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(CanGetJsonPayloadOfArrayType)
        {
            const std::string testJsonString{
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"RadioButton\",\
                        \"payload\": [\
                            {\
                                \"testloadone\": \"You can even draw attention to certain text with color\"\
                            },\
                            {\
                                \"testloadtwo\": \"You can even draw attention to certain text with markdown\"\
                            }\
                        ]\
                    },\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"You can even draw attention to certain text with color\",\
                        \"wrap\": true,\
                        \"color\": \"attention\",\
                        \"unknown\": \"testing unknown\"\
                    }\
                ]\
            }"};
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            Assert::AreEqual(elem->GetElementTypeString(), std::string("RadioButton"));

            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            std::string jsonString = ParseUtil::JsonToString(value);

            std::string expected{R"({"payload":[{"testloadone":"You can even draw attention to certain text with color"},{"testloadtwo":"You can even draw attention to certain text with markdown"}],"type":"RadioButton"})""\n"};
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(CanHandleCustomAction)
        {
            const std::string testJsonString{ R"(
                {
                    "$schema":"http://adaptivecards.io/schemas/adaptive-card.json",
                    "type": "AdaptiveCard",
                    "version": "1.0",
                    "body": [
                        {
                            "type": "TextBlock",
                            "text": "You can even draw attention to certain text with color",
                            "wrap": true,
                            "color": "attention"
                        }
                    ],
                    "actions": [
                        {
                            "type": "Alert",
                            "title": "Submit",
                            "data": {
                                "id": "1234567890"
                            }
                        }]})"};

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseActionElement> elem = parseResult->GetAdaptiveCard()->GetActions().front();
            Assert::AreEqual(elem->GetElementTypeString(), std::string("Alert"));

            std::shared_ptr<UnknownAction> delegate = std::static_pointer_cast<UnknownAction>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            std::string jsonString = ParseUtil::JsonToString(value);

            const std::string expected {R"({"data":{"id":"1234567890"},"title":"Submit","type":"Alert"}
)"};
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(RoundTripTestForCustomAction)
        {
            const std::string testJsonString{ R"(
                {
                    "type": "AdaptiveCard",
                    "version": "1.0",
                    "body": [
                        {
                            "type": "TextBlock",
                            "text": "You can even draw attention to certain text with color",
                            "wrap": true,
                            "color": "Attention"
                        }
                    ],
                    "actions": [
                        {
                            "type": "Alert",
                            "title": "Submit",
                            "data": {
                                "id": "1234567890"
                            }
                        }]})"};

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            const auto expectedValue = ParseUtil::GetJsonValueFromString(testJsonString);
            const auto expectedString = ParseUtil::JsonToString(expectedValue);
            const auto serializedCard = parseResult->GetAdaptiveCard()->SerializeToJsonValue();
            const auto serializedCardAsString = ParseUtil::JsonToString(serializedCard);
            Assert::AreEqual(expectedString, serializedCardAsString);
            Assert::IsTrue(expectedValue == serializedCard);
        }
    };
}
