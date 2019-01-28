#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

using namespace std::string_literals;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(AdditionalPropertyTest)
    {
    public:
        TEST_METHOD(CanGetAdditionalProperitesTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
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
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            Json::Value value = elem->GetAdditionalProperties();
            Json::FastWriter fastWriter;
            std::string jsonString = fastWriter.write(value);
            Assert::AreEqual("{\"unknown\":\"testing unknown\"}\n"s, jsonString);
        }

        TEST_METHOD(UnknownElementRoundtripping)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"Standard textblock\"\
                    },\
                    {\
                        \"type\": \"SomeRandomType\",\
                        \"property\": \"value\",\
                        \"someOtherProperty\": \"some other value\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            const auto outputCard = parseResult->GetAdaptiveCard()->Serialize();
            Assert::AreEqual("{\"actions\":[],\"body\":[{\"text\":\"Standard textblock\",\"type\":\"TextBlock\"},{\"property\":\"value\",\"someOtherProperty\":\"some other value\",\"type\":\"SomeRandomType\"}],\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}\n"s,
                outputCard);
        }
    };
}
