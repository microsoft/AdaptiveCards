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
                \"version\": \"1.0\",\
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

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
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
                \"version\": \"1.0\",\
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

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Container> container = std::static_pointer_cast<Container>(element);
            Assert::AreEqual<bool>(container->GetMinHeight() == 100, true);
        }

        void ValidateFactSetMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"FactSet\",\
                        \"minHeight\": \"125px\",\
                        \"facts\": [\
                            {\
                                \"title\": \"Fact 1\",\
                                \"value\" : \"Value 1\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<FactSet> factSet = std::static_pointer_cast<FactSet>(element);
            Assert::AreEqual<bool>(factSet->GetMinHeight() == 125, true);
        }

        void ValidateImageMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\" : \"http://adaptivecards.io/content/cats/1.png\",\
                        \"minHeight\" : \"150px\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Image> image = std::static_pointer_cast<Image>(element);
            Assert::AreEqual<bool>(image->GetMinHeight() == 150, true);
        }

        void ValidateImageSetMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"ImageSet\",\
                        \"minHeight\": \"175px\",\
                        \"images\": [\
                            {\
                                \"type\": \"Image\",\
                                \"url\": \"http://adaptivecards.io/content/cats/1.png\"\
                            },\
                            {\
                                \"type\": \"Image\",\
                                \"url\": \"http://adaptivecards.io/content/cats/1.png\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ImageSet> imageSet = std::static_pointer_cast<ImageSet>(element);
            Assert::AreEqual<bool>(imageSet->GetMinHeight() == 175, true);
        }

        void ValidateChoiceSetInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.ChoiceSet\",\
                        \"id\": \"myColor\",\
                        \"style\": \"compact\",\
                        \"isMultiSelect\": false,\
                        \"value\": \"1\",\
                        \"minHeight\": \"200px\",\
                        \"choices\": [\
                            {\
                                \"title\": \"Red\",\
                                \"value\": \"1\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ChoiceSetInput> choiceSetInput = std::static_pointer_cast<ChoiceSetInput>(element);
            Assert::AreEqual<bool>(choiceSetInput->GetMinHeight() == 200, true);
        }

        void ValidateDateInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.Date\",\
                        \"id\": \"date\",\
                        \"minHeight\": \"225px\",\
                        \"placeholder\": \"Enter a date\",\
                        \"value\": \"2017-10-12\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<DateInput> dateInput = std::static_pointer_cast<DateInput>(element);
            Assert::AreEqual<bool>(dateInput->GetMinHeight() == 225, true);
        }

        void ValidateNumberInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.Number\",\
                        \"id\": \"number\",\
                        \"minHeight\": \"250px\",\
                        \"placeholder\": \"Enter a number\",\
                        \"min\": 1,\
                        \"max\": 10,\
                        \"value\": 3\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<NumberInput> numberInput = std::static_pointer_cast<NumberInput>(element);
            Assert::AreEqual<bool>(numberInput->GetMinHeight() == 250, true);
        }

        void ValidateTextInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Input.Text\",\
                        \"id\": \"input2\",\
                        \"minHeight\": \"275px\",\
                        \"placeholder\": \"enter comment\",\
                        \"maxLength\": 500,\
                        \"isMultiline\": true\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<TextInput> textInput = std::static_pointer_cast<TextInput>(element);
            Assert::AreEqual<bool>(textInput->GetMinHeight() == 275, true);
        }

        void ValidateTimeInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.Time\",\
                        \"id\": \"time\",\
                        \"minHeight\": \"300px\",\
                        \"min\": \"09:00\",\
                        \"max\": \"17:00\",\
                        \"value\": \"15:30\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<TimeInput> timeInput = std::static_pointer_cast<TimeInput>(element);
            Assert::AreEqual<bool>(timeInput->GetMinHeight() == 300, true);
        }

        void ValidateToggleInputMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Input.Toggle\",\
                        \"id\": \"acceptTerms\",\
                        \"minHeight\": \"325px\",\
                        \"title\": \"I accept the terms and agreements\",\
                        \"value\": \"true\",\
                        \"valueOn\": \"true\",\
                        \"valueOff\": \"false\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<ToggleInput> toggleInput = std::static_pointer_cast<ToggleInput>(element);
            Assert::AreEqual<bool>(toggleInput->GetMinHeight() == 325, true);
        }

        void ValidateTextBlockMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\": \"Text\",\
                        \"minHeight\": \"350px\"\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<TextBlock> textBlock = std::static_pointer_cast<TextBlock>(element);
            Assert::AreEqual<bool>(textBlock->GetMinHeight() == 350, true);
        }

        void ValidateMediaMinHeight()
        {
            std::string testJsonString =
                "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"body\": [\
                    {\
                        \"type\": \"Media\",\
                        \"poster\": \"https://adaptivecards.io/content/poster-video.png\",\
                        \"minHeight\": \"375px\",\
                        \"sources\": [\
                            {\
                                \"mimeType\": \"video/mp4\",\
                                \"url\": \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4\"\
                            }\
                        ]\
                    }\
                ]\
            }";

            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(testJsonString, "1.0");
            std::shared_ptr<BaseCardElement> element = parseResult->GetAdaptiveCard()->GetBody().front();
            std::shared_ptr<Media> media = std::static_pointer_cast<Media>(element);
            Assert::AreEqual<bool>(media->GetMinHeight() == 375, true);
        }

        TEST_METHOD(MinHeightForAllElementsTest)
        {
            ValidateColumnSetMinHeight();
            ValidateContainerMinHeight();
            ValidateFactSetMinHeight();
            ValidateImageMinHeight();
            ValidateImageSetMinHeight();
            ValidateChoiceSetInputMinHeight();
            ValidateDateInputMinHeight();
            ValidateNumberInputMinHeight();
            ValidateTextInputMinHeight();
            ValidateTimeInputMinHeight();
            ValidateToggleInputMinHeight();
            ValidateTextBlockMinHeight();
            ValidateMediaMinHeight();
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
