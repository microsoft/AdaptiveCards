// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(GatherImagesTest)
    {
    private:
        void ValidateResourceInformation(
            std::vector<RemoteResourceInformation>& expectedValues,
            std::vector<RemoteResourceInformation>& resourceInfos)
        {
            Assert::AreEqual(expectedValues.size(), resourceInfos.size());

            for (auto expectedValue : expectedValues)
            {
                bool found = false;
                for (auto resourceInfo : resourceInfos)
                {
                    if (resourceInfo.url == expectedValue.url &&
                        resourceInfo.mimeType == expectedValue.mimeType)
                    {
                        found = true;
                    }
                }

                if (!found)
                {
                    Assert::Fail(L"Expected resource information not found");
                }
            }
        }

    public:
        TEST_METHOD(CanGatherImages)
        {
            // Expected images to find in the card
            std::vector<RemoteResourceInformation> expectedValues = {
                {"BackgroundImage.png", "image"},
                { "Image.png", "image" },
                { "ImageSet.Image1.png", "image" },
                { "ImageSet.Image2.png", "image" },
                { "Container.Image1.png", "image" },
                { "Container.Image2.png", "image" },
                { "ColumnSet.Column1.Image.png", "image" },
                { "ColumnSet.Column2.Image.png", "image" },
                { "ShowCard.Image.png", "image" },
                { "Media.Poster.png", "image" },
                { "Media1.mp4", "video/mp4" },
                { "Media2.ogg", "video/ogg" },
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
                        \"type\": \"Media\",\
                        \"poster\": \"Media.Poster.png\",\
                        \"sources\" : [ \
                            {\
                                \"mimeType\": \"video/mp4\",\
                                \"url\" : \"Media1.mp4\"\
                            },\
                            {\
                                \"mimeType\": \"video/ogg\",\
                                \"url\" : \"Media2.ogg\"\
                            }\
                        ]\
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
            auto resourceInformation = AdaptiveCard::DeserializeFromString(testJsonString, "1.0")->GetAdaptiveCard()->GetResourceInformation();
            ValidateResourceInformation(expectedValues, resourceInformation);
        }

        TEST_METHOD(CanGatherCustomImages)
        {
            // Expected images to find in the card
            std::vector<RemoteResourceInformation> expectedValues = {
                { "BackgroundImage.png", "image" },
                { "Image.png", "image" },
                { "Custom.png", "image" },
                { "Action.Custom.png", "image" },
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
                TestCustomElement(const Json::Value& value) : BaseCardElement(AdaptiveCards::CardElementType::Custom),
                                                              BaseActionElement(AdaptiveCards::ActionType::Custom)
                {
                    m_customImage = value.get("customImageProperty", Json::Value()).asString();
                }

                virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceUris) override
                {
                    RemoteResourceInformation resourceInfo;
                    resourceInfo.url = m_customImage;
                    resourceInfo.mimeType = "image";
                    resourceUris.push_back(resourceInfo);
                }

            private:
                std::string m_customImage;
            };

            // Define custom element parser
            class TestCustomParser : public BaseCardElementParser
            {
            public:
                virtual ~TestCustomParser(){}
                virtual std::shared_ptr<BaseCardElement> Deserialize(ParseContext &/*context*/, const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }
                virtual std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext &context, const std::string& value) override
                {
                    return Deserialize(context, ParseUtil::GetJsonValueFromString(value));
                }
            };

            // Define custom action parser
            class TestCustomActionParser : public ActionElementParser
            {
            public:
                virtual ~TestCustomActionParser() {}
                virtual std::shared_ptr<BaseActionElement> Deserialize(ParseContext &/*context*/, const Json::Value& value) override
                {
                    return std::make_shared<TestCustomElement>(value);
                }

                virtual std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext &context, const std::string& jsonString) override
                {
                    return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
                }
            };

            // Register the custom parsers
            auto elementRegistration = std::make_shared<ElementParserRegistration>();
            elementRegistration->AddParser("CustomTypeWithImage", std::make_shared<TestCustomParser>());

            auto actionRegistration = std::make_shared<ActionParserRegistration>();
            actionRegistration->AddParser("CustomActionWithImage", std::make_shared<TestCustomActionParser>());

            ParseContext context(elementRegistration, actionRegistration);
            // Parse the card and get the image uris
            auto resourceInformation = AdaptiveCard::DeserializeFromString(testJsonString, "1.0", context)->GetAdaptiveCard()->GetResourceInformation();
            ValidateResourceInformation(expectedValues, resourceInformation);
        }

        TEST_METHOD(CanGatherImagesInActions)
        {
            // Expected images to find in the card
            std::vector<RemoteResourceInformation> expectedValues = {
                { "BackgroundImage.png", "image" },
                { "Image.png", "image" },
                { "SubmitAction.png", "image" },
                { "OpenUrl.png", "image" },
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
                        \"type\": \"Action.Submit\",\
                        \"title\": \"Snooze\",\
                        \"iconUrl\": \"SubmitAction.png\"\
                    },\
                    {\
                        \"type\": \"Action.Submit\",\
                        \"title\": \"Dismiss\"\
                    },\
                    {\
                        \"type\": \"Action.OpenUrl\",\
                        \"title\" : \"Action.OpenUrl\",\
                        \"iconUrl\": \"OpenUrl.png\",\
                        \"url\" : \"http://adaptivecards.io\"\
                    }\
                ] \
            }";

            // Parse the card and get the image uris
            auto resourceInformation = AdaptiveCard::DeserializeFromString(testJsonString, "1.0")->GetAdaptiveCard()->GetResourceInformation();
            ValidateResourceInformation(expectedValues, resourceInformation);
        }
    };
}
