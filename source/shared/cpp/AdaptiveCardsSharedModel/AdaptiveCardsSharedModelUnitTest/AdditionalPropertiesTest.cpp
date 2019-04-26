// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "ParseUtil.h"
#include "TextRun.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

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

        TEST_METHOD(CanGetAdditionalProperitesTest_Inlines)
        {
            std::string testJsonString =
            "{\
                \"type\":\"TextRun\",\
                \"text\":\"Here is some text\",\
                \"MyAdditionalProperty\": \"Bar\"\
            }";

            ParseContext parseContext;
            auto textRun = TextRun::Deserialize(parseContext, ParseUtil::GetJsonValueFromString(testJsonString));

            Json::Value value = textRun->GetAdditionalProperties();
            Assert::AreEqual("{\"MyAdditionalProperty\":\"Bar\"}\n"s, ParseUtil::JsonToString(value));
        }

            std::string expected = "{\"unknown\":\"testing unknown\"}\n";
            Assert::AreEqual(expected, jsonString);
        }
    };
}
