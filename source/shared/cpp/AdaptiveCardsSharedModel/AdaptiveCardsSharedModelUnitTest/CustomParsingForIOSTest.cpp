#include "stdafx.h"
#include "UnknownElement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(CustomParsingForIOSTest)
    {
    public:
        TEST_METHOD(CanGetCustomJsonPayload)
        {
            std::string testJsonString =
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
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            Json::FastWriter fastWriter;
            std::string jsonString = fastWriter.write(value);

            std::string expected = "{\"payload\":\"You can even draw attention to certain text with color\"}\n";
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(CanGetCustomJsonPayloadWithKnownElementFollowing)
        {
            std::string testJsonString =
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
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            Json::FastWriter fastWriter;
            std::string jsonString = fastWriter.write(value);

            std::string expected = "{\"payload\":\"You can even draw attention to certain text with color\"}\n";
            Assert::AreEqual(expected, jsonString);
        }

        TEST_METHOD(CanGetJsonPayloadOfArrayType)
        {
            std::string testJsonString =
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
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<UnknownElement> delegate = std::static_pointer_cast<UnknownElement>(elem);
            Json::Value value = delegate->GetAdditionalProperties();
            Json::FastWriter fastWriter;
            std::string jsonString = fastWriter.write(value);

            std::string expected = "{\"payload\":[{\"testloadone\":\"You can even draw attention to certain text with color\"},{\"testloadtwo\":\"You can even draw attention to certain text with markdown\"}]}\n";
            Assert::AreEqual(expected, jsonString);
        }
    };
}
