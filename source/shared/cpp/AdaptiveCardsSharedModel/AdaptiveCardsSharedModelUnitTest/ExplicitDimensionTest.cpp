#include "stdafx.h"
#include "CppUnitTest.h"
#include "Image.h"
#include <Windows.h>
#include <StrSafe.h>
#include "SharedAdaptiveCard.h"
#include "AdaptiveCardParseException.h"
#include "BaseCardElement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ExplicitDimensionTest)
    {
    public:
        TEST_METHOD(PositiveTest)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"width\": \"10px\",\
                        \"height\": \"50px\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image =  std::static_pointer_cast<Image>(elem);
            int width = image->GetWidth();
            Assert::AreEqual(10, width);
            int height = image->GetHeight();
            Assert::AreEqual(50, height);
        }
        TEST_METHOD(PositiveTestWithOneDimensionOnly)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"height\": \"10px\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
            std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image =  std::static_pointer_cast<Image>(elem);
            int height = image->GetHeight();
            Assert::AreEqual(10, height);
            int width = image->GetWidth();
            Assert::AreEqual(0, width);
        }

        TEST_METHOD(MalformedUnitTest)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"height\": \"10pic\"\
                    }\
                ]\
            }";
            try
            {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
                std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
                std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            }
            catch(const AdaptiveCardParseException &e)
            { 
                Assert::AreEqual<bool>(e.GetStatusCode() == ErrorStatusCode::InvalidPropertyValue, true);
            }
        }

        TEST_METHOD(MalformedUnitLengthTest)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"height\": \"10px  \"\
                    }\
                ]\
            }";
            try
            {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
                std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
                std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            }
            catch(const AdaptiveCardParseException &e)
            { 
                Assert::AreEqual<bool>(e.GetStatusCode() == ErrorStatusCode::InvalidPropertyValue, true);
            }
        }

        TEST_METHOD(MalformedUnitTypeTest)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"height\": \"10.0px\"\
                    }\
                ]\
            }";
            try
            {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
                std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
                std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            }
            catch(const AdaptiveCardParseException &e)
            { 
                Assert::AreEqual<bool>(e.GetStatusCode() == ErrorStatusCode::InvalidPropertyValue, true);
            }
        }

        TEST_METHOD(MalformedNegativeIntValueTest)
        {
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\",\
                        \"height\": \"-10px\"\
                    }\
                ]\
            }";
            try
            {
                std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, 1.0);
                std::shared_ptr<BaseCardElement> elem =  parseResult->GetAdaptiveCard()->GetBody().front();
                std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            }
            catch(const AdaptiveCardParseException &e)
            { 
                Assert::AreEqual<bool>(e.GetStatusCode() == ErrorStatusCode::InvalidPropertyValue, true);
            }
        }
    };
}
