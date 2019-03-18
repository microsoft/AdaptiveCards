#include "stdafx.h"
#include "Paragraph.h"
#include "ParseUtil.h"

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
            Assert::AreEqual("{\"unknown\":\"testing unknown\"}\n"s, ParseUtil::JsonToString(value));
        }

        TEST_METHOD(CanGetAdditionalProperitesTest_Action)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"You can even draw attention to certain text with color\"\
                    }\
                ],\
                \"actions\": [\
                    {\
                        \"type\": \"Action.Submit\",\
                        \"MyAdditionalProperty\": \"Foo\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseActionElement> action =  parseResult->GetAdaptiveCard()->GetActions().front();
            Json::Value value = action->GetAdditionalProperties();
            Assert::AreEqual("{\"MyAdditionalProperty\":\"Foo\"}\n"s, ParseUtil::JsonToString(value));
        }

        TEST_METHOD(CanGetAdditionalProperitesTest_ParagraphAndInlines)
        {
            std::string testJsonString =
            "{\
                \"type\": \"Paragraph\",\
                \"inlines\": [\
                    {\
                        \"type\":\"TextRun\",\
                        \"text\":\"Here is some text\",\
                        \"MyAdditionalProperty\": \"Bar\"\
                    }\
                ],\
                \"MyAdditionalProperty\": \"Foo\"\
            }";

            ParseContext parseContext;
            auto paragraph = Paragraph::Deserialize(parseContext, ParseUtil::GetJsonValueFromString(testJsonString));

            Json::Value value = paragraph->GetAdditionalProperties();
            Assert::AreEqual("{\"MyAdditionalProperty\":\"Foo\"}\n"s, ParseUtil::JsonToString(value));

            value = paragraph->GetInlines()[0]->GetAdditionalProperties();
            Assert::AreEqual("{\"MyAdditionalProperty\":\"Bar\"}\n"s, ParseUtil::JsonToString(value));
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
