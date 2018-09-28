#include "stdafx.h"
#include "CppUnitTest.h"
#include "Media.h"
#include "TextBlock.h"
#include "SharedAdaptiveCard.h"
#include "ShowCardAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(ObjectModelTest)
    {
    public:
        // An empty JSON does not produce any selectAction
        TEST_METHOD(SelectActionEmptyJsonTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            Json::Value json;
            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                elementParserRegistration,
                actionParserRegistration,
                warnings,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON without selectAction key does not produce any selectAction
        TEST_METHOD(SelectActionNonExistentTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // Card without card-level selectAction
            std::string cardStr = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Container\",\
                        \"items\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub.\",\
                                \"wrap\" : true\
                            }\
                        ]\
                    }\
                ]\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(cardStr);

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                elementParserRegistration,
                actionParserRegistration,
                warnings,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON with selectAction of incorrect type does not produce any selectAction
        TEST_METHOD(SelectActionInvalidTypeTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // An arbitrary JSON with OpenUrl selectAction
            std::string str = "{\
                \"type\" : \"ColumnSet\",\
                \"selectAction\": {\
                    \"type\": \"Action.Invalid\",\
                    \"title\" : \"Submit\",\
                    \"data\": {\
                        \"x\": 13\
                    }\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                elementParserRegistration,
                actionParserRegistration,
                warnings,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsTrue(selectAction == nullptr);
        }

        // A card JSON with an OpenUrl selectAction
        TEST_METHOD(SelectActionOpenUrlTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // Card with card-level OpenUrl selectAction
            std::string str = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Container\",\
                        \"items\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub.\",\
                                \"wrap\" : true\
                            }\
                        ]\
                    }\
                ],\
                \"selectAction\": {\
                    \"type\": \"Action.OpenUrl\",\
                    \"title\" : \"View\",\
                    \"url\" : \"http://select-action.io\"\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                elementParserRegistration,
                actionParserRegistration,
                warnings,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.OpenUrl"s);
        }

        // An arbitrary JSON with a Submit selectAction (for other elements such as Container, ColumnSet, etc.)
        TEST_METHOD(SelectActionAnyJsonTest)
        {
            std::shared_ptr<ElementParserRegistration> elementParserRegistration;
            elementParserRegistration.reset(new ElementParserRegistration());

            std::shared_ptr<ActionParserRegistration> actionParserRegistration;
            actionParserRegistration.reset(new ActionParserRegistration());

            // An arbitrary JSON with OpenUrl selectAction
            std::string str = "{\
                \"type\" : \"ColumnSet\",\
                \"selectAction\": {\
                    \"type\": \"Action.Submit\",\
                    \"title\" : \"Submit\",\
                    \"data\": {\
                        \"x\": 13\
                    }\
                }\
            }";
            Json::Value json = ParseUtil::GetJsonValueFromString(str);

            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
            std::shared_ptr<BaseActionElement> selectAction = ParseUtil::GetAction(
                elementParserRegistration,
                actionParserRegistration,
                warnings,
                json,
                AdaptiveCardSchemaKey::SelectAction,
                false);

            Assert::IsFalse(selectAction == nullptr);
            Assert::AreEqual(selectAction->GetElementTypeString(), "Action.Submit"s);
        }

        TEST_METHOD(MediaElementTest)
        {
            std::string cardWithMediaElement = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"1.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"Media\",\
                        \"poster\" : \"http://adaptivecards.io/content/cats/1.png\",\
                        \"altText\" : \"This is a video\",\
                        \"sources\": [ \
                            {\
                                \"mimeType\": \"video/mp4\",\
                                \"url\" : \"http://source1.mp4\" \
                            },\
                            { \
                                \"mimeType\": \"video/avi\", \
                                \"url\" : \"http://source2.avi\" \
                            }\
                        ]\
                    }\
                ]\
            }";

            auto card = AdaptiveCard::DeserializeFromString(cardWithMediaElement, "1.0")->GetAdaptiveCard();
            std::shared_ptr<Media> mediaElement = std::static_pointer_cast<Media> (card->GetBody()[0]);

            Assert::IsTrue(mediaElement->GetElementType() == CardElementType::Media);
            Assert::AreEqual(mediaElement->GetElementTypeString(), "Media"s);
            Assert::AreEqual(mediaElement->GetPoster(), "http://adaptivecards.io/content/cats/1.png"s);
            Assert::AreEqual(mediaElement->GetAltText(), "This is a video"s);

            auto sources = mediaElement->GetSources();
            Assert::IsTrue(sources.size() == 2);
            Assert::AreEqual(sources[0]->GetMimeType(), "video/mp4"s);
            Assert::AreEqual(sources[0]->GetUrl(), "http://source1.mp4"s);
            Assert::AreEqual(sources[1]->GetMimeType(), "video/avi"s);
            Assert::AreEqual(sources[1]->GetUrl(), "http://source2.avi"s);
        }

        TEST_METHOD(ShowCardSerialization)
        {
            std::string cardWithShowCard = "{\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\
                \"type\" : \"AdaptiveCard\",\
                \"version\" : \"2.0\",\
                \"body\" : [\
                    {\
                        \"type\": \"TextBlock\",\
                        \"text\" : \"This card's action will show another card\"\
                    }\
                ],\
                \"actions\": [\
                    {\
                        \"type\": \"Action.ShowCard\",\
                        \"title\" : \"Action.ShowCard\",\
                        \"card\" : {\
                        \"type\": \"AdaptiveCard\",\
                        \"body\" : [\
                            {\
                                \"type\": \"TextBlock\",\
                                \"text\" : \"What do you think?\"\
                            }\
                        ],\
                        \"actions\": [\
                            {\
                                \"type\": \"Action.Submit\",\
                                \"title\" : \"Neat!\"\
                            }\
                        ]\
                        }\
                    }\
                ]\
            }";

            auto mainCard = AdaptiveCard::DeserializeFromString(cardWithShowCard, "2.0")->GetAdaptiveCard();
            auto showCard = (std::static_pointer_cast<ShowCardAction>(mainCard->GetActions()[0]))->GetCard();

            Assert::AreEqual(showCard->GetVersion(), "2.0"s);
            Assert::AreEqual(showCard->GetBody().size(), (size_t)1);
            Assert::IsTrue(showCard->GetBody()[0]->GetElementType() == CardElementType::TextBlock);
            Assert::AreEqual(std::static_pointer_cast<TextBlock>(showCard->GetBody()[0])->GetText(), "What do you think?"s);

            Assert::AreEqual(showCard->GetActions().size(), (size_t)1);
            Assert::IsTrue(showCard->GetActions()[0]->GetElementType() == ActionType::Submit);
            Assert::AreEqual(showCard->GetActions()[0]->GetTitle(), "Neat!"s);

            auto serializedShowCard = showCard->Serialize();
            auto roundTrippedShowCard = AdaptiveCard::DeserializeFromString(serializedShowCard, "2.0")->GetAdaptiveCard();

            Assert::AreEqual(showCard->GetVersion(), "2.0"s);
            Assert::AreEqual(roundTrippedShowCard->GetBody().size(), (size_t)1);
            Assert::IsTrue(roundTrippedShowCard->GetBody()[0]->GetElementType() == CardElementType::TextBlock);
            Assert::AreEqual(std::static_pointer_cast<TextBlock>(roundTrippedShowCard->GetBody()[0])->GetText(), "What do you think?"s);

            Assert::AreEqual(roundTrippedShowCard->GetActions().size(), (size_t)1);
            Assert::IsTrue(roundTrippedShowCard->GetActions()[0]->GetElementType() == ActionType::Submit);
            Assert::AreEqual(roundTrippedShowCard->GetActions()[0]->GetTitle(), "Neat!"s);
        }
    };
}
