#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>
#include <Windows.h>
#include <StrSafe.h>
#include "SharedAdaptiveCard.h"
#include "BaseCardElement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(GatherImagesTest)
    {
    public:
        TEST_METHOD(CanGatherImages)
        {
            // Expected images to find in the card
            std::vector<std::string> expectedValues = {
                "BackgroundImage.png",
                "Image.png",
                "ImageSet.Image1.png",
                "ImageSet.Image2.png",
                "Container.Image1.png",
                "Container.Image2.png",
                "ColumnSet.Column1.Image.png",
                "ColumnSet.Column2.Image.png",
                "ShowCard.Image.png"
            };

            // Test card containing all supported image locations
            std::string testJsonString = 
            "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"backgroundImage\": \"BackgroundImage.png\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image.png\"\
                    },\
                    {\
                        \"type\": \"ImageSet\",\
			            \"images\": \
                        [ \
                            {\
                                \"type\": \"Image\", \
                                \"url\" : \"ImageSet.Image1.png\" \
                            }, \
                            {\
                                \"type\": \"Image\", \
                                \"url\" : \"ImageSet.Image2.png\" \
                            } \
                        ] \
                    },\
                    {\
                        \"type\": \"Container\",\
			            \"items\": \
                        [ \
                            {\
                                \"type\": \"Image\", \
                                \"url\" : \"Container.Image1.png\" \
                            }, \
                            {\
                                \"type\": \"Image\", \
                                \"url\" : \"Container.Image2.png\" \
                            } \
                        ] \
                    },\
                    {\
                        \"type\": \"ColumnSet\",\
			            \"columns\": \
                        [ \
                            { \
                                \"type\": \"Column\",\
			                    \"items\": \
                                [ \
                                    {\
                                        \"type\": \"Image\", \
                                        \"url\" : \"ColumnSet.Column1.Image.png\" \
                                    } \
                                ] \
                            }, \
                            { \
                                \"type\": \"Column\",\
			                    \"items\": \
                                [ \
                                    {\
                                        \"type\": \"Image\", \
                                        \"url\" : \"ColumnSet.Column2.Image.png\" \
                                    } \
                                ] \
                            } \
                       ] \
                    }\
                ],\
	            \"actions\": \
                [ \
                    { \
                        \"type\": \"Action.ShowCard\", \
                        \"title\" : \"Action.ShowCard\", \
                        \"card\" : \
                        { \
                            \"type\": \"AdaptiveCard\", \
                            \"body\" : \
                            [ \
                                { \
                                    \"type\": \"Image\", \
                                    \"url\" : \"ShowCard.Image.png\" \
                                } \
                            ] \
                        } \
                    } \
                ] \
            }";

            // Parse the card and get the image uris
            auto imageUris = AdaptiveCard::DeserializeFromString(testJsonString, 1.0)->GetAdaptiveCard()->GetResourceUris();

            // Confirm we find the expected images
            Assert::AreEqual(expectedValues.size(), imageUris.size());

            for (auto expectedValue : expectedValues)
            {
                if (imageUris.end() == std::find(imageUris.begin(), imageUris.end(), expectedValue))
                {
                    Assert::Fail(L"Expected image not found");
                }
            }
        }

        TEST_METHOD(CanGatherCustomImages)
        {
            // Expected images to find in the card
            std::vector<std::string> expectedValues = {
                "BackgroundImage.png",
                "Image.png",
                "Custom.png",
                "Action.Custom.png"
            };

            // Test card containing custom element and action with images
            std::string testJsonString =
                "{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\": \"AdaptiveCard\",\
                \"version\": \"1.0\",\
                \"backgroundImage\": \"BackgroundImage.png\",\
                \"body\": [\
                    {\
                        \"type\": \"Image\",\
                        \"url\": \"Image.png\"\
                    },\
                    {\
                        \"type\": \"CustomTypeWithImage\",\
                        \"customImageProperty\": \"Custom.png\"\
                    }\
                ], \
                \"actions\" : \
                [ \
                    {\
                        \"type\": \"CustomActionWithImage\",\
                        \"customImageProperty\": \"Action.Custom.png\"\
                    }\
                ] \
            }";

            // Define custom type. This implements both element and action for convenience
            class TestCustomElement : public BaseCardElement, public BaseActionElement
            {
                public:
                    TestCustomElement(
                        const Json::Value& value) :
                        BaseCardElement(AdaptiveCards::CardElementType::Custom),
                        BaseActionElement(AdaptiveCards::ActionType::Custom)
                    {
                        m_customImage = value.get("customImageProperty", Json::Value()).asString();
                    }

                    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override
                    {
                        resourceUris.push_back(m_customImage);
                    }

                private:
                    std::string m_customImage;
            };

            // Define custom element parser
            class TestCustomParser : public BaseCardElementParser
            {
            public:
                virtual std::shared_ptr<BaseCardElement> Deserialize(
                    std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
                    std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
                    std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& warnings,
                    const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }
            };

            // Define custom action parser
            class TestCustomActionParser : public ActionElementParser
            {
            public:
                virtual std::shared_ptr<BaseActionElement> Deserialize(
                    std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
                    std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
                    std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& warnings,
                    const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }
            };

            // Register the custom parsers
            auto elementRegistration = std::make_shared<ElementParserRegistration>();
            elementRegistration->AddParser("CustomTypeWithImage", std::make_shared<TestCustomParser>());

            auto actionRegistration = std::make_shared<ActionParserRegistration>();
            actionRegistration->AddParser("CustomActionWithImage", std::make_shared<TestCustomActionParser>());

            // Parse the card and get the image uris
            auto imageUris = AdaptiveCard::DeserializeFromString(testJsonString, 1.0, elementRegistration, actionRegistration)->GetAdaptiveCard()->GetResourceUris();

            // Confirm we find the expected images
            Assert::AreEqual(expectedValues.size(), imageUris.size());

            for (auto expectedValue : expectedValues)
            {
                if (imageUris.end() == std::find(imageUris.begin(), imageUris.end(), expectedValue))
                {
                    Assert::Fail(L"Expected image not found");
                }
            }
        }
    };
}
