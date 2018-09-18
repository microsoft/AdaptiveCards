#include "stdafx.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include <StrSafe.h>
#include "SharedAdaptiveCard.h"
#include "AdaptiveCardParseException.h"
#include "BaseCardElement.h"
#include "Image.h"
#include "Column.h"
#include "ColumnSet.h"

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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            int width = image->GetPixelWidth();
            Assert::AreEqual(10, width);
            int height = image->GetPixelHeight();
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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            int height = image->GetPixelHeight();
            Assert::AreEqual(10, height);
            int width = image->GetPixelWidth();
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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            Assert::AreEqual<int>(1, parseResult->GetWarnings().size());
            Assert::AreEqual<bool>(true, parseResult->GetWarnings().at(0)->GetStatusCode() == 
                WarningStatusCode::InvalidDimensionSpecified);
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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            Assert::AreEqual<int>(1, parseResult->GetWarnings().size());
            Assert::AreEqual<bool>(true, parseResult->GetWarnings().at(0)->GetStatusCode() == 
                WarningStatusCode::InvalidDimensionSpecified);
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
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            Assert::AreEqual<int>(0, parseResult->GetWarnings().size());
            Assert::AreEqual<int>(10, image->GetPixelHeight());
            Assert::AreEqual<int>(0, image->GetPixelWidth());
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

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
            Assert::AreEqual<int>(parseResult->GetWarnings().size(), 1);
            Assert::AreEqual<bool>(parseResult->GetWarnings().at(0)->GetStatusCode() == 
                WarningStatusCode::InvalidDimensionSpecified, true);
        }

        TEST_METHOD(MalformedDimensionValuesTest)
        {
            std::vector<std::string>payloads = 
            {
                "{\
                      \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                      \"type\" : \"AdaptiveCard\",\
                      \"version\" : \"1.0\",\
                      \"body\" : [\
                          {\
                              \"type\": \"Image\",\
                              \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                              \"width\" : \".20px\",\
                              \"height\" : \"50.1234.12px\"\
                          }\
                      ]\
                }",
                "{\
                      \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                      \"type\" : \"AdaptiveCard\",\
                      \"version\" : \"1.0\",\
                      \"body\" : [\
                          {\
                              \"type\": \"Image\",\
                              \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                              \"width\" : \"20, 00px\",\
                              \"height\" : \"20,0.00   px\"\
                          }\
                      ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                          {\
                              \"type\": \"Image\",\
                              \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                              \"width\" : \"2000 px\",\
                              \"height\" : \"20a0px\"\
                          }\
                      ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                          {\
                              \"type\": \"Image\",\
                              \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                              \"width\" : \"20.a00px\",\
                              \"height\" : \"20.00\"\
                          }\
                      ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                          {\
                              \"type\": \"Image\",\
                              \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                              \"width\" : \" 20.00px\",\
                              \"height\" : \"2 0.00px\"\
                          }\
                       ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                       {\
                             \"type\": \"Image\",\
                             \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                             \"width\" : \"200px .00px\",\
                             \"height\" : \"2 0px00px\"\
                       }\
                     ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                       {\
                             \"type\": \"Image\",\
                             \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                             \"width\" : \"200px .00px\",\
                             \"height\" : \"2 0px00px\"\
                       }\
                     ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                       {\
                             \"type\": \"Image\",\
                             \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                             \"width\" : \"200.00 px\",\
                             \"height\" : \"200.0.px\"\
                       }\
                     ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                       {\
                             \"type\": \"Image\",\
                             \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                             \"width\" : \"20,000px\",\
                             \"height\" : \"20,000.0px\"\
                       }\
                     ]\
                  }",
                  "{\
                       \"$schema\": \"http ://adaptivecards.io/schemas/adaptive-card.json\",\
                       \"type\" : \"AdaptiveCard\",\
                       \"version\" : \"1.0\",\
                       \"body\" : [\
                       {\
                             \"type\": \"Image\",\
                             \"url\" : \"http ://adaptivecards.io/content/cats/1.png\",\
                             \"width\" : \"20.px\",\
                             \"height\" : \"050px\"\
                       }\
                     ]\
                  }"
            }; 

            for (auto payload : payloads)
            {
                try {
                    std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(payload, "1.1");
                    std::shared_ptr<BaseCardElement> elem = parseResult->GetAdaptiveCard()->GetBody().front();
                    std::shared_ptr<Image> image = std::static_pointer_cast<Image>(elem);
                    
                    Assert::AreEqual<int>(2, parseResult->GetWarnings().size());
                    Assert::AreEqual<unsigned int>(0U, image->GetPixelHeight());
                    Assert::AreEqual<unsigned int>(0U, image->GetPixelWidth());
                }
                catch(const AdaptiveCardParseException &e)
                {
                    // no exception should be thrown
                    Assert::Fail();
                }
            } 
        }
    };

    TEST_CLASS(ExplicitDimensionForColumnTest)
    {
    public:
        TEST_METHOD(PositiveValueTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"auto\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<std::string>(column->GetWidth(), "auto");
        }

        TEST_METHOD(PositiveRelativeWidthTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"20\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<std::string>(column->GetWidth(), "20");
            Assert::AreEqual<bool>(column->GetPixelWidth() != 20, true);
        }

        TEST_METHOD(PositiveExplicitWidthTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"20px\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<std::string>("20px",  column->GetWidth());
            Assert::AreEqual<bool>(column->GetPixelWidth() == 20, true);
        }

        TEST_METHOD(ExplicitWidthMalformedUnitTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"20px20\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            Assert::AreEqual<int>(parseResult->GetWarnings().size(), 1);
            Assert::AreEqual<bool>(parseResult->GetWarnings().at(0)->GetStatusCode() == 
                WarningStatusCode::InvalidDimensionSpecified, true);
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<int>(0, column->GetPixelWidth());
            Assert::AreEqual<string>("20px20", column->GetWidth());
        }

        TEST_METHOD(ExplicitWidthMalformedValueTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"-20px\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            Assert::AreEqual<int>(parseResult->GetWarnings().size(), 1);
            Assert::AreEqual<bool>(parseResult->GetWarnings().at(0)->GetStatusCode() == 
                WarningStatusCode::InvalidDimensionSpecified, true);
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<int>(0, column->GetPixelWidth());
            Assert::AreEqual<string>("-20px", column->GetWidth());
        }

        TEST_METHOD(ExplicitWidthFloatValueTest)
        {
            std::string testJsonString =
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\":\"ColumnSet\",\
                        \"columns\": [\
                            {\
                                \"type\": \"Column\",\
                                \"width\": \"20.5px\",\
                                \"items\": [\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<std::string>("20.5px", column->GetWidth());
            Assert::AreEqual<bool>(column->GetPixelWidth() == 20, true);
        }
    };
}
