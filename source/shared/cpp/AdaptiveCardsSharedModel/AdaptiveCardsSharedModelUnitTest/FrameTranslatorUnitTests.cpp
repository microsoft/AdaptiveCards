#include "stdafx.h"
#include "CppUnitTest.h"
#include <time.h>
#include <Windows.h>
#include <StrSafe.h>
#include "FrameTranslator.h"
#include "BaseCardElement.h"
#include "SharedAdaptiveCard.h"

// BECKYTODO - look into where the frame code is in the object model project

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(FrameTranslatorTests)
    {
    public:
        TEST_METHOD(AAFrameTranslatorTest)
        {
            std::string testSource =
                "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"This is the body\"\
                    }\
                ],\
                \"actions\":[\
		            {\
                    \"type\": \"Action.Submit\",\
                    \"title\" : \"Action\"\
                    },\
                    {\
                    \"type\": \"Action.Submit\",\
                    \"title\" : \"Set\"\
                    }\
                ]\
            }";

            std::string testFrame =
                "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                {\
                    \"type\": \"Container\",\
                    \"items\" : \"${body}\"\
                },\
                {\
                    \"type\": \"ActionSet\",\
                    \"actions\" : \"${actions}\"\
                }\
                ]\
            }";

            std::string expectedResultString =
                "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                {\
                    \"type\": \"Container\",\
                    \"items\" : [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"This is the body\"\
                    }\
                ]},\
                {\
                    \"type\": \"ActionSet\",\
                    \"actions\" : [\
		                {\
                        \"type\": \"Action.Submit\",\
                        \"title\" : \"Action\"\
                        },\
                        {\
                        \"type\": \"Action.Submit\",\
                        \"title\" : \"Set\"\
                        }\
                    ]\
                }\
                ]\
            }";

            Json::Value soureCardJson = ParseUtil::GetJsonValueFromString(testSource);
            Json::Value frameJson = ParseUtil::GetJsonValueFromString(testFrame);

            Json::Value result;
            ApplyFrame(soureCardJson, frameJson, result);

            Json::FastWriter fastWriter;
            std::string resultString = fastWriter.write(result);

            Json::Value expectedJson = ParseUtil::GetJsonValueFromString(expectedResultString);
            expectedResultString = fastWriter.write(expectedJson);

            Assert::AreEqual(expectedResultString, resultString);
        }

        TEST_METHOD(AACardPruningTest)
        {
            std::string testSource =
                "{\
                    \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                    \"type\": \"AdaptiveCard\",\
                    \"version\": \"1.0\",\
                    \"body\": [\
                        {\
                            \"type\": \"TextBlock\",\
                            \"text\": \"This is the body\"\
                        }\
                    ],\
                    \"actions\":[\
		                {\
                        \"type\": \"Action.Submit\",\
                        \"title\" : \"Action\"\
                        },\
                        {\
                        \"type\": \"Action.Submit\",\
                        \"title\" : \"Set\"\
                        }\
                    ]\
                }";

            std::string testFrame =
                "{\
                    \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                    \"type\" : \"AdaptiveCard\",\
                    \"version\" : \"1.0\",\
                    \"body\" : [\
                    {\
                        \"type\": \"Container\",\
                        \"items\" : \"${foo}\"\
                    },\
                    {\
                        \"type\": \"ActionSet\",\
                        \"actions\" : \"${actions}\"\
                    }\
                    ]\
                }";

            std::string expectedResultString =
                "{\
                    \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                    \"type\" : \"AdaptiveCard\",\
                    \"version\" : \"1.0\",\
                    \"body\" : [\
                    {\
                        \"type\": \"ActionSet\",\
                        \"actions\" : [\
		                    {\
                            \"type\": \"Action.Submit\",\
                            \"title\" : \"Action\"\
                            },\
                            {\
                            \"type\": \"Action.Submit\",\
                            \"title\" : \"Set\"\
                            }\
                        ]\
                    }\
                    ]\
                }";

            Json::Value sourceCardJson = ParseUtil::GetJsonValueFromString(testSource);
            Json::Value frameJson = ParseUtil::GetJsonValueFromString(testFrame);

            auto parseResult = AdaptiveCard::DeserializeFromStringWithFrame(
                testSource, testFrame, 1.0);

            std::string resultString = parseResult->GetAdaptiveCard()->Serialize();

            Json::FastWriter fastWriter;
            Json::Value expectedJson = fastWriter.write(ParseUtil::GetJsonValueFromString(expectedResultString));

            Assert::AreEqual(expectedResultString, resultString);
        }
    };
};
