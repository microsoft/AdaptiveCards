// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"

#include "AdaptiveCardParseException.h"
#include "Column.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "ChoiceSetInput.h"
#include "DateInput.h"
#include "NumberInput.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"
#include "TextBlock.h"
#include "Media.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

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
            Assert::AreEqual<size_t>(1, parseResult->GetWarnings().size());
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
            Assert::AreEqual<size_t>(1, parseResult->GetWarnings().size());
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
            Assert::AreEqual<size_t>(0, parseResult->GetWarnings().size());
            Assert::AreEqual<size_t>(10, image->GetPixelHeight());
            Assert::AreEqual<size_t>(0, image->GetPixelWidth());
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
            Assert::AreEqual<size_t>(1, parseResult->GetWarnings().size());
            Assert::AreEqual<bool>(true, parseResult->GetWarnings().at(0)->GetStatusCode() ==
                WarningStatusCode::InvalidDimensionSpecified);
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

                    Assert::AreEqual<size_t>(2, parseResult->GetWarnings().size());
                    Assert::AreEqual<unsigned int>(0U, image->GetPixelHeight());
                    Assert::AreEqual<unsigned int>(0U, image->GetPixelWidth());
                }
                catch(const AdaptiveCardParseException &)
                {
                    // no exception should be thrown
                    Assert::Fail();
                }
            }
        }

        void ValidateColumnSetMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.2\",\
                \"body\": [\
                    {\
                        \"type\": \"ColumnSet\",\
                        \"minHeight\": \"50px\",\
                        \"columns\" : [\
                            {\
                                \"type\": \"Column\",\
                                \"minHeight\": \"75px\",\
                                \"items\": [\
                                    {\
                                        \"type\": \"TextBlock\",\
                                        \"text\": \"Column 1\"\
                                    }\
                                ]\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            Assert::AreEqual<bool>(columnSet->GetMinHeight() == 50, true);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<bool>(column->GetMinHeight() == 75, true);
        }

        void ValidateContainerMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.2\",\
                \"body\": [\
                    {\
                        \"type\": \"Container\",\
                        \"minHeight\": \"100px\",\
                        \"items\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\": \"This is some text\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Container> container = std::static_pointer_cast<Container>(element);
            Assert::AreEqual<bool>(container->GetMinHeight() == 100, true);
        }

        void ValidateAdaptiveCardMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.2\",\
                \"minHeight\": \"100px\",\
                \"body\": [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"This is some text\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.2");
            Assert::AreEqual<bool>(parseResult->GetAdaptiveCard()->GetMinHeight() == 100, true);
        }

        TEST_METHOD(MinHeightForAllElementsTest)
        {
            // This test validates columnset and column minHeigh property
            ValidateColumnSetMinHeight();
            ValidateContainerMinHeight();
            ValidateAdaptiveCardMinHeight();
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
            Assert::AreEqual<size_t>(1, parseResult->GetWarnings().size());
            Assert::AreEqual<bool>(true, parseResult->GetWarnings().at(0)->GetStatusCode() ==
                WarningStatusCode::InvalidDimensionSpecified);
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<int>(0, column->GetPixelWidth());
            Assert::AreEqual<std::string>("20px20", column->GetWidth());
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
            Assert::AreEqual<size_t>(1, parseResult->GetWarnings().size());
            Assert::AreEqual<bool>(true, parseResult->GetWarnings().at(0)->GetStatusCode() ==
                WarningStatusCode::InvalidDimensionSpecified);
            std::shared_ptr<BaseCardElement> element =  parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ColumnSet> columnSet = std::static_pointer_cast<ColumnSet>(element);
            std::shared_ptr<Column> column = columnSet->GetColumns().front();
            Assert::AreEqual<int>(0, column->GetPixelWidth());
            Assert::AreEqual<std::string>("-20px", column->GetWidth());
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
