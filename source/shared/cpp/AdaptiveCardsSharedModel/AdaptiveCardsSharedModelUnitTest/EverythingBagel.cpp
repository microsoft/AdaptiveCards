#include "stdafx.h"
#include "SharedAdaptiveCard.h"
#include "Column.h"
#include "ColumnSet.h"
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
    void ValidateTopLevelProperties(const AdaptiveCard &everythingBagel)
    {
        Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, everythingBagel.GetBackgroundImage());
        Assert::IsTrue(CardElementType::AdaptiveCard == everythingBagel.GetElementType());
        Assert::AreEqual("fallbackText"s, everythingBagel.GetFallbackText());
        Assert::IsTrue(HeightType::Auto == everythingBagel.GetHeight());
        Assert::AreEqual("en"s, everythingBagel.GetLanguage());
        Assert::IsTrue(!everythingBagel.GetSelectAction());
        Assert::AreEqual("speak"s, everythingBagel.GetSpeak());
        Assert::IsTrue(ContainerStyle::None == everythingBagel.GetStyle());
        Assert::AreEqual("1.0"s, everythingBagel.GetVersion());
        Assert::IsTrue(VerticalContentAlignment::Top == everythingBagel.GetVerticalContentAlignment());
    }

    void ValidateTextBlock(const TextBlock &textBlock)
    {
        Assert::IsTrue(textBlock.GetElementType() == CardElementType::TextBlock);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TextBlock), textBlock.GetElementTypeString());
        Assert::AreEqual("TextBlock_id"s, textBlock.GetId());
        Assert::AreEqual("TextBlock_text"s, textBlock.GetText());
        Assert::IsTrue(ForegroundColor::Default == textBlock.GetTextColor());
        Assert::IsTrue(HorizontalAlignment::Left == textBlock.GetHorizontalAlignment());
        Assert::IsTrue(Spacing::Default == textBlock.GetSpacing());
        Assert::AreEqual(1U, textBlock.GetMaxLines());
        Assert::AreEqual("en"s, textBlock.GetLanguage());
        Assert::IsTrue(TextSize::Default == textBlock.GetTextSize());
        Assert::IsTrue(TextWeight::Default == textBlock.GetTextWeight());
        Assert::IsFalse(textBlock.GetIsSubtle());
        Assert::IsFalse(textBlock.GetSeparator());
        Assert::IsFalse(textBlock.GetWrap());
    }

    void ValidateImage(const Image &image)
    {
        Assert::IsTrue(image.GetElementType() == CardElementType::Image);
        Assert::AreEqual(CardElementTypeToString(CardElementType::Image), image.GetElementTypeString());
        Assert::AreEqual("Image_id"s, image.GetId());
        Assert::AreEqual("Image_altText"s, image.GetAltText());
        Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, image.GetUrl());
        Assert::AreEqual(""s, image.GetBackgroundColor());
        Assert::IsTrue(ImageStyle::Person == image.GetImageStyle());
        Assert::IsTrue(Spacing::None == image.GetSpacing());
        Assert::IsTrue(HeightType::Auto == image.GetHeight());
        Assert::IsTrue(HorizontalAlignment::Center == image.GetHorizontalAlignment());
        Assert::IsTrue(ImageSize::Auto == image.GetImageSize());
        Assert::IsTrue(image.GetSeparator());

        auto imageAction = std::static_pointer_cast<OpenUrlAction>(image.GetSelectAction());
        Assert::IsTrue((bool)imageAction);
        Assert::AreEqual("Image_Action.OpenUrl"s, imageAction->GetTitle());
        Assert::AreEqual("https://adaptivecards.io/"s, imageAction->GetUrl());
        Assert::IsTrue(ActionType::OpenUrl == imageAction->GetElementType());
        Assert::AreEqual(ActionTypeToString(ActionType::OpenUrl), imageAction->GetElementTypeString());
    }

    void ValidateColumnSet(const ColumnSet &columnSet)
    {
        Assert::IsTrue(columnSet.GetElementType() == CardElementType::ColumnSet);
        Assert::AreEqual(CardElementTypeToString(CardElementType::ColumnSet), columnSet.GetElementTypeString());
        Assert::AreEqual("ColumnSet_id"s, columnSet.GetId());
        Assert::IsTrue(Spacing::Large == columnSet.GetSpacing());
        Assert::IsTrue(columnSet.GetSeparator());

        auto columns = columnSet.GetColumns();
        Assert::AreEqual(3U, columns.size());

        // validate first column
        {
            auto firstColumn = std::static_pointer_cast<Column>(columns.at(0));
            Assert::IsTrue(firstColumn->GetElementType() == CardElementType::Column);
            Assert::AreEqual(CardElementTypeToString(CardElementType::Column), firstColumn->GetElementTypeString());
            Assert::AreEqual("Column_id1"s, firstColumn->GetId());
            Assert::AreEqual("auto"s, firstColumn->GetWidth());
            Assert::AreEqual(0, firstColumn->GetPixelWidth());
            Assert::IsTrue(ContainerStyle::Default == firstColumn->GetStyle());

            auto items = firstColumn->GetItems();
            Assert::AreEqual(1U, items.size());
            auto imageItem = std::static_pointer_cast<Image>(items.at(0));
            Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, imageItem->GetUrl());
        }

        // validate second column
        {
            auto secondColumn = std::static_pointer_cast<Column>(columns.at(1));
            Assert::AreEqual("Column_id2"s, secondColumn->GetId());
            Assert::AreEqual("20px"s, secondColumn->GetWidth());
            Assert::AreEqual(20, secondColumn->GetPixelWidth());
            Assert::IsTrue(ContainerStyle::Emphasis == secondColumn->GetStyle());

            auto items = secondColumn->GetItems();
            Assert::AreEqual(1U, items.size());
            auto imageItem = std::static_pointer_cast<Image>(items.at(0));
            Assert::AreEqual("https://adaptivecards.io/content/cats/2.png"s, imageItem->GetUrl());
        }

        // validate third column
        {
            auto thirdColumn = std::static_pointer_cast<Column>(columns.at(2));
            Assert::AreEqual("Column_id3"s, thirdColumn->GetId());
            Assert::AreEqual("stretch"s, thirdColumn->GetWidth());
            Assert::AreEqual(0, thirdColumn->GetPixelWidth());
            Assert::IsTrue(ContainerStyle::Default == thirdColumn->GetStyle());

            auto items = thirdColumn->GetItems();
            Assert::AreEqual(2U, items.size());
            auto imageItem = std::static_pointer_cast<Image>(items.at(0));
            Assert::AreEqual("https://adaptivecards.io/content/cats/3.png"s, imageItem->GetUrl());

            auto textBlockItem = std::static_pointer_cast<TextBlock>(items.at(1));
            Assert::AreEqual("Column3_TextBlock_text"s, textBlockItem->GetText());
            Assert::AreEqual("Column3_TextBlock_id"s, textBlockItem->GetId());
        }
    }

    void ValidateContainer(const Container &container)
    {
        Assert::IsTrue(container.GetElementType() == CardElementType::Container);
        Assert::AreEqual(CardElementTypeToString(CardElementType::Container), container.GetElementTypeString());
        Assert::AreEqual("Container_id"s, container.GetId());
        Assert::IsTrue(Spacing::Medium == container.GetSpacing());
        Assert::IsTrue(ContainerStyle::Default == container.GetStyle());

        // validate container action
        {
            auto action = std::static_pointer_cast<SubmitAction>(container.GetSelectAction());
            Assert::IsTrue((bool)action);
            Assert::AreEqual("Container_Action.Submit"s, action->GetTitle());
            auto dataString = action->GetDataJson();
            Assert::AreEqual("\"Container_data\"\n"s, dataString);
        }

        auto items = container.GetItems();
        Assert::AreEqual(1U, items.size());
        auto columnSet = std::static_pointer_cast<ColumnSet>(items.at(0));
        ValidateColumnSet(*columnSet);
    }

    void ValidateBody(const AdaptiveCard &everythingBagel)
    {
        auto body = everythingBagel.GetBody();
        Assert::AreEqual(6U, body.size());

        // validate textblock
        auto textBlock = std::static_pointer_cast<TextBlock>(body.at(0));
        ValidateTextBlock(*textBlock);

        // validate image
        auto image = std::static_pointer_cast<Image>(body.at(1));
        ValidateImage(*image);
        
        // validate container
        auto container = std::static_pointer_cast<Container>(body.at(2));
        ValidateContainer(*container);
    }

    void ValidateToplevelActions(const AdaptiveCard &everythingBagel)
    {
        auto actions = everythingBagel.GetActions();
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

    void ValidateFallbackCard(const AdaptiveCard &everythingBagel)
    {
        auto fallbackCard = everythingBagel.MakeFallbackTextCard("fallback"s, "en"s);
        auto fallbackTextBlock = std::static_pointer_cast<TextBlock>(fallbackCard->GetBody().at(0));
        Assert::AreEqual("fallback"s, fallbackTextBlock->GetText());
        Assert::AreEqual("en"s, fallbackTextBlock->GetLanguage());
    }

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

            // get the card
            auto everythingBagel = std::static_pointer_cast<AdaptiveCard>(parseResult->GetAdaptiveCard());

            // validate card's structure
            ValidateTopLevelProperties(*everythingBagel);
            ValidateBody(*everythingBagel);
            ValidateToplevelActions(*everythingBagel);
            ValidateFallbackCard(*everythingBagel);
        }
    };
}