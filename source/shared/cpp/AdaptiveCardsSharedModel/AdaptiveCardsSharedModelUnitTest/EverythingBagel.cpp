#include "stdafx.h"
#include "EverythingBagel.h"
#include "SharedAdaptiveCard.h"
#include "ChoiceInput.h"
#include "ChoiceSetInput.h"
#include "Column.h"
#include "ColumnSet.h"
#include "Container.h"
#include "DateInput.h"
#include "Fact.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "NumberInput.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"

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
        Assert::AreEqual(size_t{ 3 }, columns.size());

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
            Assert::AreEqual(size_t{ 1 }, items.size());
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
            Assert::AreEqual(size_t{ 1 }, items.size());
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
            Assert::AreEqual(size_t{ 2 }, items.size());
            auto imageItem = std::static_pointer_cast<Image>(items.at(0));
            Assert::AreEqual("https://adaptivecards.io/content/cats/3.png"s, imageItem->GetUrl());

            auto textBlockItem = std::static_pointer_cast<TextBlock>(items.at(1));
            Assert::AreEqual("Column3_TextBlock_text"s, textBlockItem->GetText());
            Assert::AreEqual("Column3_TextBlock_id"s, textBlockItem->GetId());
        }
    }

    void ValidateColumnSetContainer(const Container &container)
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
        Assert::AreEqual(size_t{ 1 }, items.size());
        auto columnSet = std::static_pointer_cast<ColumnSet>(items.at(0));
        ValidateColumnSet(*columnSet);
    }

    void ValidateFactSet(const FactSet &factSet)
    {
        Assert::IsTrue(factSet.GetElementType() == CardElementType::FactSet);
        Assert::AreEqual(CardElementTypeToString(CardElementType::FactSet), factSet.GetElementTypeString());
        Assert::AreEqual("FactSet_id"s, factSet.GetId());

        auto facts = factSet.GetFacts();
        Assert::AreEqual(size_t{ 2 }, facts.size());

        // validate first fact
        {
            auto fact = std::static_pointer_cast<Fact>(facts.at(0));
            Assert::AreEqual("Topping"s, fact->GetTitle());
            Assert::AreEqual("poppyseeds"s, fact->GetValue());
        }

        // validate second fact
        {
            auto fact = std::static_pointer_cast<Fact>(facts.at(1));
            Assert::AreEqual("Topping"s, fact->GetTitle());
            Assert::AreEqual("onion flakes"s, fact->GetValue());
        }
    }

    void ValidateImageSet(const ImageSet &imageSet)
    {
        Assert::IsTrue(imageSet.GetElementType() == CardElementType::ImageSet);
        Assert::AreEqual(CardElementTypeToString(CardElementType::ImageSet), imageSet.GetElementTypeString());
        Assert::AreEqual("ImageSet_id"s, imageSet.GetId());
        Assert::IsTrue(ImageSize::Auto == imageSet.GetImageSize());

        auto images = imageSet.GetImages();
        Assert::AreEqual(size_t{ 3 }, images.size());
        for (unsigned int i = 0; i < images.size(); i++)
        {
            auto currImage = std::static_pointer_cast<Image>(images.at(i));
            Assert::IsTrue(currImage->GetElementType() == CardElementType::Image);
            std::string expectedUrl = "https://adaptivecards.io/content/cats/";
            expectedUrl.append(std::to_string(i+1));
            expectedUrl.append(".png");
            Assert::AreEqual(expectedUrl, currImage->GetUrl());
        }
    }

    void ValidateInputText(const TextInput &textInput)
    {
        Assert::IsTrue(textInput.GetElementType() == CardElementType::TextInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TextInput), textInput.GetElementTypeString());
        Assert::AreEqual("Input.Text_id"s, textInput.GetId());

        Assert::IsFalse(textInput.GetIsMultiline());
        Assert::IsFalse(textInput.GetIsRequired());
        Assert::AreEqual(10U, textInput.GetMaxLength());
        Assert::AreEqual("Input.Text_placeholder"s, textInput.GetPlaceholder());
        Assert::IsTrue(Spacing::Small == textInput.GetSpacing());
        Assert::IsTrue(TextInputStyle::Text == textInput.GetTextInputStyle());
        Assert::AreEqual("Input.Text_value"s, textInput.GetValue());
    }

    void ValidateInputNumber(const NumberInput &numberInput)
    {
        Assert::IsTrue(numberInput.GetElementType() == CardElementType::NumberInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::NumberInput), numberInput.GetElementTypeString());
        Assert::AreEqual("Input.Number_id"s, numberInput.GetId());

        Assert::IsFalse(numberInput.GetIsRequired());
        Assert::AreEqual(10, numberInput.GetMax());
        Assert::AreEqual(5, numberInput.GetMin());
        Assert::AreEqual(7, numberInput.GetValue());
        Assert::AreEqual("Input.Number_placeholder"s, numberInput.GetPlaceholder());
    }

    void ValidateInputDate(const DateInput &dateInput)
    {
        Assert::IsTrue(dateInput.GetElementType() == CardElementType::DateInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::DateInput), dateInput.GetElementTypeString());
        Assert::AreEqual("Input.Date_id"s, dateInput.GetId());

        Assert::AreEqual("1/1/2020"s, dateInput.GetMax());
        Assert::AreEqual("8/1/2018"s, dateInput.GetMin());
        Assert::AreEqual("8/9/2018"s, dateInput.GetValue());
        Assert::AreEqual("Input.Date_placeholder"s, dateInput.GetPlaceholder());
    }

    void ValidateInputTime(const TimeInput &timeInput)
    {
        Assert::IsTrue(timeInput.GetElementType() == CardElementType::TimeInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TimeInput), timeInput.GetElementTypeString());
        Assert::AreEqual("Input.Time_id"s, timeInput.GetId());

        Assert::AreEqual("10:00"s, timeInput.GetMin());
        Assert::AreEqual("17:00"s, timeInput.GetMax());
        Assert::AreEqual("13:00"s, timeInput.GetValue());
    }

    void ValidateInputToggle(const ToggleInput &toggleInput)
    {
        Assert::IsTrue(toggleInput.GetElementType() == CardElementType::ToggleInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::ToggleInput), toggleInput.GetElementTypeString());
        Assert::AreEqual("Input.Toggle_id"s, toggleInput.GetId());

        Assert::AreEqual("Input.Toggle_title"s, toggleInput.GetTitle());
        Assert::AreEqual("Input.Toggle_on"s, toggleInput.GetValue());
        Assert::AreEqual("Input.Toggle_on"s, toggleInput.GetValueOn());
        Assert::AreEqual("Input.Toggle_off"s, toggleInput.GetValueOff());
    }

    void ValidateTextBlockInInput(const TextBlock &textBlock)
    {
        Assert::IsTrue(textBlock.GetElementType() == CardElementType::TextBlock);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TextBlock), textBlock.GetElementTypeString());
        Assert::AreEqual(""s, textBlock.GetId());
        Assert::AreEqual("Everybody's got choices"s, textBlock.GetText());
        Assert::IsTrue(TextWeight::Bolder == textBlock.GetTextWeight());
        Assert::IsTrue(TextSize::Large == textBlock.GetTextSize());
    }

    void ValidateInputChoiceSet(const ChoiceSetInput &choiceSet)
    {
        Assert::IsTrue(choiceSet.GetElementType() == CardElementType::ChoiceSetInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::ChoiceSetInput), choiceSet.GetElementTypeString());
        Assert::AreEqual("Input.ChoiceSet_id"s, choiceSet.GetId());
        Assert::IsTrue(ChoiceSetStyle::Compact == choiceSet.GetChoiceSetStyle());
        Assert::AreEqual("Input.Choice2,Input.Choice4"s, choiceSet.GetValue());
        Assert::IsTrue(choiceSet.GetIsMultiSelect());

        auto choices = choiceSet.GetChoices();
        Assert::AreEqual(size_t{ 4 }, choices.size());

        for (unsigned int i = 0; i < choices.size(); i++)
        {
            auto currChoice = choices.at(i);
            std::string expectedTitle = "Input.Choice";
            expectedTitle.append(std::to_string(i + 1));
            Assert::AreEqual(expectedTitle, currChoice->GetValue());
            expectedTitle.append("_title");
            Assert::AreEqual(expectedTitle, currChoice->GetTitle());
        }
    }

    void ValidateInputContainer(const Container &container)
    {
        Assert::AreEqual("Container_id_inputs"s, container.GetId());

        auto items = container.GetItems();
        Assert::AreEqual(size_t{ 7 }, items.size());

        auto textInput = std::static_pointer_cast<TextInput>(items.at(0));
        ValidateInputText(*textInput);

        auto numberInput = std::static_pointer_cast<NumberInput>(items.at(1));
        ValidateInputNumber(*numberInput);

        auto dateInput = std::static_pointer_cast<DateInput>(items.at(2));
        ValidateInputDate(*dateInput);

        auto timeInput = std::static_pointer_cast<TimeInput>(items.at(3));
        ValidateInputTime(*timeInput);

        auto toggleInput = std::static_pointer_cast<ToggleInput>(items.at(4));
        ValidateInputToggle(*toggleInput);

        auto textBlock = std::static_pointer_cast<TextBlock>(items.at(5));
        ValidateTextBlockInInput(*textBlock);

        auto choiceSet = std::static_pointer_cast<ChoiceSetInput>(items.at(6));
        ValidateInputChoiceSet(*choiceSet);
    }

    void ValidateBody(const AdaptiveCard &everythingBagel)
    {
        auto body = everythingBagel.GetBody();
        Assert::AreEqual(size_t{ 6 }, body.size());

        // validate textblock
        auto textBlock = std::static_pointer_cast<TextBlock>(body.at(0));
        ValidateTextBlock(*textBlock);

        // validate image
        auto image = std::static_pointer_cast<Image>(body.at(1));
        ValidateImage(*image);

        // validate columnset container
        auto columnSetContainer = std::static_pointer_cast<Container>(body.at(2));
        ValidateColumnSetContainer(*columnSetContainer);

        // validate factset
        auto factSet = std::static_pointer_cast<FactSet>(body.at(3));
        ValidateFactSet(*factSet);

        // validate imageset
        auto imageSet = std::static_pointer_cast<ImageSet>(body.at(4));
        ValidateImageSet(*imageSet);

        // validate input container
        auto inputContainer = std::static_pointer_cast<Container>(body.at(5));
        ValidateInputContainer(*inputContainer);
    }

    void ValidateToplevelActions(const AdaptiveCard &everythingBagel)
    {
        auto actions = everythingBagel.GetActions();
        Assert::AreEqual(size_t{ 2 }, actions.size());

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
            Assert::AreEqual(size_t{ 0 }, resourceUris.size());
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
            Assert::AreEqual(size_t{ 0 }, resourceUris.size());

            // validate the subcard
            {
                auto subCard = std::static_pointer_cast<AdaptiveCard>(showCardAction->GetCard());
                Assert::AreEqual(size_t{ 0 }, subCard->GetActions().size());
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
                Assert::AreEqual(size_t{ 0 }, parseWarnings.size());
            }

            // get the card
            auto everythingBagel = std::static_pointer_cast<AdaptiveCard>(parseResult->GetAdaptiveCard());

            // validate card's structure
            ValidateTopLevelProperties(*everythingBagel);
            ValidateBody(*everythingBagel);
            ValidateToplevelActions(*everythingBagel);
            ValidateFallbackCard(*everythingBagel);

            // re-serialize the card and verify

            // uncomment the following line to output the serialized json
            //Logger::WriteMessage("Submit Data: '"s.append(everythingBagel->Serialize()).append("'").c_str());
            Assert::AreEqual(std::string(EVERYTHING_JSON), everythingBagel->Serialize());
        }
    };
}
