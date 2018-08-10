#include "stdafx.h"
#include "SharedAdaptiveCard.h"
#include "Container.h"
#include "Image.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "TextBlock.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(EverythingBagel)
    {
    public:
        TEST_METHOD(EverythingBagelTests)
        {
            auto parseResult = AdaptiveCard::DeserializeFromFile("EverythingBagel.json", 1.0);

            // ensure we're warning free
            {
                auto parseWarnings = parseResult->GetWarnings();
                Assert::AreEqual(0U, parseWarnings.size());
            }

            // get the card and start validating the structure
            auto everythingBagel = std::static_pointer_cast<AdaptiveCard>(parseResult->GetAdaptiveCard());

            // validate toplevel properties
            Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, everythingBagel->GetBackgroundImage());
            Assert::IsTrue(CardElementType::AdaptiveCard == everythingBagel->GetElementType());
            Assert::AreEqual("fallbackText"s, everythingBagel->GetFallbackText());
            Assert::IsTrue(HeightType::Auto == everythingBagel->GetHeight());
            Assert::AreEqual("en"s, everythingBagel->GetLanguage());
            Assert::IsTrue(!everythingBagel->GetSelectAction());
            Assert::AreEqual("speak"s, everythingBagel->GetSpeak());
            Assert::IsTrue(ContainerStyle::None == everythingBagel->GetStyle());
            Assert::AreEqual("1.0"s, everythingBagel->GetVersion());
            Assert::IsTrue(VerticalContentAlignment::Top == everythingBagel->GetVerticalContentAlignment());
            
            // validate body
            {
                auto body = everythingBagel->GetBody();
                Assert::AreEqual(6U, body.size());

                // validate textblock
                {
                    auto textBlock = std::static_pointer_cast<TextBlock>(body.at(0));
                    Assert::IsTrue(textBlock->GetElementType() == CardElementType::TextBlock);
                    Assert::AreEqual(CardElementTypeToString(CardElementType::TextBlock), textBlock->GetElementTypeString());
                    Assert::AreEqual("TextBlock_id"s, textBlock->GetId());
                    Assert::AreEqual("TextBlock_text"s, textBlock->GetText());
                    Assert::IsTrue(ForegroundColor::Default == textBlock->GetTextColor());
                    Assert::IsTrue(HorizontalAlignment::Left == textBlock->GetHorizontalAlignment());
                    Assert::IsTrue(Spacing::Default == textBlock->GetSpacing());
                    Assert::AreEqual(1U, textBlock->GetMaxLines());
                    Assert::AreEqual("en"s, textBlock->GetLanguage());
                    Assert::IsTrue(TextSize::Default == textBlock->GetTextSize());
                    Assert::IsTrue(TextWeight::Default == textBlock->GetTextWeight());
                    Assert::IsFalse(textBlock->GetIsSubtle());
                    Assert::IsFalse(textBlock->GetSeparator());
                    Assert::IsFalse(textBlock->GetWrap());
                }

                // validate image
                {
                    auto image = std::static_pointer_cast<Image>(body.at(1));
                    Assert::IsTrue(image->GetElementType() == CardElementType::Image);
                    Assert::AreEqual(CardElementTypeToString(CardElementType::Image), image->GetElementTypeString());
                    Assert::AreEqual("Image_id"s, image->GetId());
                    Assert::AreEqual("Image_altText"s, image->GetAltText());
                    Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, image->GetUrl());
                    Assert::AreEqual(""s, image->GetBackgroundColor());
                    Assert::IsTrue(Spacing::None == image->GetSpacing());
                    Assert::IsTrue(HeightType::Auto == image->GetHeight());
                    Assert::IsTrue(HorizontalAlignment::Center == image->GetHorizontalAlignment());
                    Assert::IsTrue(ImageSize::Auto == image->GetImageSize());
                    Assert::IsTrue(image->GetSeparator());

                    auto imageAction = std::static_pointer_cast<OpenUrlAction>(image->GetSelectAction());
                    Assert::IsTrue((bool)imageAction);
                    Assert::AreEqual("Image_Action.OpenUrl"s, imageAction->GetTitle());
                    Assert::AreEqual("https://adaptivecards.io/"s, imageAction->GetUrl());
                    Assert::IsTrue(ActionType::OpenUrl == imageAction->GetElementType());
                    Assert::AreEqual(ActionTypeToString(ActionType::OpenUrl), imageAction->GetElementTypeString());
                }

                // validate container
                {
                    auto container = std::static_pointer_cast<Container>(body.at(2));
                }
            }

            // validate actions
            {
                auto actions = everythingBagel->GetActions();
                Assert::AreEqual(2U, actions.size());

                // validate submit action
                {
                    auto submitAction = std::static_pointer_cast<SubmitAction>(actions.at(0));
                    Assert::IsTrue(submitAction->GetElementType() == ActionType::Submit);
                    Assert::AreEqual(ActionTypeToString(ActionType::Submit), submitAction->GetElementTypeString());
                    Assert::AreEqual(""s, submitAction->GetIconUrl());
                    Assert::AreEqual("Action.Submit_id"s, submitAction->GetId());
                    Assert::AreEqual("Action.Submit"s, submitAction->GetTitle());
                    //Logger::WriteMessage("Submit Data: '"s.append(submitAction->GetDataJson()).append("'").c_str());
                    Assert::AreEqual("{\n   \"submitValue\" : true\n}\n"s, submitAction->GetDataJson());

                    auto additionalProps = submitAction->GetAdditionalProperties();
                    Assert::IsTrue(additionalProps.empty());

                    std::vector<RemoteResourceInformation> resourceUris;
                    submitAction->GetResourceInformation(resourceUris);
                    Assert::AreEqual(0U, resourceUris.size());
                }

                // validate showcard action
                {
                    auto showCardAction = std::static_pointer_cast<ShowCardAction>(actions.at(1));
                    Assert::IsTrue(showCardAction->GetElementType() == ActionType::ShowCard);
                    Assert::AreEqual(ActionTypeToString(ActionType::ShowCard), showCardAction->GetElementTypeString());
                    Assert::AreEqual(""s, showCardAction->GetIconUrl());
                    Assert::AreEqual("Action.ShowCard_id"s, showCardAction->GetId());
                    Assert::AreEqual("Action.ShowCard"s, showCardAction->GetTitle());

                    auto additionalProps = showCardAction->GetAdditionalProperties();
                    Assert::IsTrue(additionalProps.empty());

                    std::vector<RemoteResourceInformation> resourceUris;
                    showCardAction->GetResourceInformation(resourceUris);
                    Assert::AreEqual(0U, resourceUris.size());

                    // validate the subcard
                    {
                        auto subCard = std::static_pointer_cast<AdaptiveCard>(showCardAction->GetCard());
                        Assert::AreEqual(0U, subCard->GetActions().size());
                        Assert::AreEqual(""s, subCard->GetBackgroundImage());
                        Assert::IsTrue(CardElementType::AdaptiveCard == subCard->GetElementType());
                        Assert::AreEqual(""s, subCard->GetFallbackText());
                        Assert::IsTrue(HeightType::Auto == subCard->GetHeight());
                        Assert::AreEqual("en"s, subCard->GetLanguage());
                        Assert::IsTrue(!subCard->GetSelectAction());
                        Assert::AreEqual(""s, subCard->GetSpeak());
                        Assert::IsTrue(ContainerStyle::None == subCard->GetStyle());
                        Assert::AreEqual(""s, subCard->GetVersion());
                        Assert::IsTrue(VerticalContentAlignment::Top == subCard->GetVerticalContentAlignment());

                        //Logger::WriteMessage("Submit Data: '"s.append(subCard->Serialize()).append("'").c_str());
                        Assert::AreEqual("{\"actions\":[],\"body\":[{\"isSubtle\":true,\"text\":\"Action.ShowCard text\",\"type\":\"TextBlock\"}],\"lang\":\"en\",\"type\":\"AdaptiveCard\",\"version\":\"\"}\n"s,
                            subCard->Serialize());
                    }
                }
            }
        }
    };
}