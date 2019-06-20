// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "Image.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ImageBackgroundColorTest)
    {

    public:
        TEST_METHOD(NoBackgroundColorTest)
        {
            std::string testJsonString =
                "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string(""), backgroundColor);
        }
        TEST_METHOD(AARRGGBBTest)
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
                        \"backgroundColor\": \"#ABF65314\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#ABF65314"), backgroundColor);
        }

        TEST_METHOD(RRGGBBTest)
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
                        \"backgroundColor\": \"#00A1F1\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#FF00A1F1"), backgroundColor);
        }

        TEST_METHOD(LowerCaseCharactersTest)
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
                        \"backgroundColor\": \"#ffa65314\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#ffa65314"), backgroundColor);
        }

        TEST_METHOD(InvalidLengthTest)
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
                        \"backgroundColor\": \"#A00A1F1\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#00000000"), backgroundColor);
        }

        TEST_METHOD(InvalidCharacterTest)
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
                        \"backgroundColor\": \"#ABF6P314\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#00000000"), backgroundColor);
        }

        TEST_METHOD(InvalidFormatTest)
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
                        \"backgroundColor\": \"@ABF65314\"\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            std::string backgroundColor = image->GetBackgroundColor();
            Assert::AreEqual(std::string("#00000000"), backgroundColor);
        }

    };
}
