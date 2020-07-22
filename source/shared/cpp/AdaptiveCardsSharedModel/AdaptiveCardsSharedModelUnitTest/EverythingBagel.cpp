// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "EverythingBagel.h"

#include "ActionSet.h"
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
#include "RichTextBlock.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TextRun.h"
#include "TimeInput.h"
#include "ToggleInput.h"

using namespace std::string_literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    void ValidateBackgroundImage(const BackgroundImage& backImage, ImageFillMode mode, HorizontalAlignment hAlignment, VerticalAlignment vAlignment)
    {
        Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, backImage.GetUrl());
        Assert::IsTrue(mode == backImage.GetFillMode());
        Assert::IsTrue(hAlignment == backImage.GetHorizontalAlignment());
        Assert::IsTrue(vAlignment == backImage.GetVerticalAlignment());
    }

    void ValidateTopLevelProperties(const AdaptiveCard &everythingBagel)
    {
        ValidateBackgroundImage(*everythingBagel.GetBackgroundImage(), ImageFillMode::Cover, HorizontalAlignment::Left, VerticalAlignment::Top);
        Assert::IsTrue(CardElementType::AdaptiveCard == everythingBagel.GetElementType());
        Assert::AreEqual("fallbackText"s, everythingBagel.GetFallbackText());
        Assert::IsTrue(HeightType::Auto == everythingBagel.GetHeight());
        Assert::AreEqual("en"s, everythingBagel.GetLanguage());
        Assert::IsTrue(!everythingBagel.GetSelectAction());
        Assert::AreEqual("speak"s, everythingBagel.GetSpeak());
        Assert::IsTrue(ContainerStyle::None == everythingBagel.GetStyle());
        Assert::AreEqual("1.0"s, everythingBagel.GetVersion());
        Assert::IsTrue(VerticalContentAlignment::Top == everythingBagel.GetVerticalContentAlignment());
        Assert::IsTrue(everythingBagel.GetInputNecessityIndicators() == InputNecessityIndicators::RequiredInputs);
    }

    void ValidateTextBlock(const TextBlock &textBlock, FontType fontType, std::string id)
    {
        Assert::IsTrue(textBlock.GetElementType() == CardElementType::TextBlock);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TextBlock), textBlock.GetElementTypeString());
        Assert::AreEqual(id, textBlock.GetId());
        Assert::AreEqual("TextBlock_text"s, textBlock.GetText());
        Assert::IsTrue(ForegroundColor::Default == textBlock.GetTextColor());
        Assert::IsTrue(HorizontalAlignment::Left == textBlock.GetHorizontalAlignment());
        Assert::IsTrue(Spacing::Default == textBlock.GetSpacing());
        Assert::AreEqual(1U, textBlock.GetMaxLines());
        Assert::AreEqual("en"s, textBlock.GetLanguage());
        Assert::IsTrue(TextSize::Default == textBlock.GetTextSize());
        Assert::IsTrue(TextWeight::Default == textBlock.GetTextWeight());
        Assert::IsTrue(fontType == textBlock.GetFontType());
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
        Assert::IsFalse(image.GetIsVisible());

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
            Assert::IsFalse(action->GetIgnoreInputValidation());
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
        Assert::IsTrue(textInput.GetErrorMessage().empty());
        Assert::AreEqual("([A-Z])\\w+"s, textInput.GetRegex());

        Assert::AreEqual("Input.Text_label"s, textInput.GetLabel());

        auto inlineAction = std::static_pointer_cast<SubmitAction>(textInput.GetInlineAction());
        Assert::IsTrue((bool)inlineAction);
        Assert::AreEqual("Input.Text_Action.Submit"s, inlineAction->GetTitle());
        Assert::AreEqual("https://adaptivecards.io/content/cats/1.png"s, inlineAction->GetIconUrl());
        Assert::IsFalse(inlineAction->GetIgnoreInputValidation());
    }

    void ValidateInputNumber(const NumberInput &numberInput)
    {
        Assert::IsTrue(numberInput.GetElementType() == CardElementType::NumberInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::NumberInput), numberInput.GetElementTypeString());
        Assert::AreEqual("Input.Number_id"s, numberInput.GetId());

        Assert::IsTrue(numberInput.GetIsRequired());
        Assert::AreEqual(10, numberInput.GetMax());
        Assert::AreEqual(5, numberInput.GetMin());
        Assert::AreEqual(7, numberInput.GetValue());
        Assert::AreEqual("Input.Number_placeholder"s, numberInput.GetPlaceholder());
        Assert::IsTrue(numberInput.GetErrorMessage().empty());
        Assert::AreEqual("Input.Number_label"s, numberInput.GetLabel());
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
        Assert::IsFalse(dateInput.GetIsRequired());
        Assert::IsTrue(dateInput.GetErrorMessage().empty());
		Assert::AreEqual("Input.Date_label"s, dateInput.GetLabel());
    }

    void ValidateInputTime(const TimeInput &timeInput)
    {
        Assert::IsTrue(timeInput.GetElementType() == CardElementType::TimeInput);
        Assert::AreEqual(CardElementTypeToString(CardElementType::TimeInput), timeInput.GetElementTypeString());
        Assert::AreEqual("Input.Time_id"s, timeInput.GetId());

        Assert::AreEqual("10:00"s, timeInput.GetMin());
        Assert::AreEqual("17:00"s, timeInput.GetMax());
        Assert::AreEqual("13:00"s, timeInput.GetValue());
        Assert::IsTrue(timeInput.GetIsRequired());
        Assert::AreEqual("Input.Time.ErrorMessage"s, timeInput.GetErrorMessage());
        Assert::AreEqual("Input.Time_label"s, timeInput.GetLabel());
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
        Assert::IsFalse(toggleInput.GetIsRequired());
        Assert::IsTrue(toggleInput.GetErrorMessage().empty());
        Assert::AreEqual("Input.Toggle_label"s, toggleInput.GetLabel());
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
        Assert::IsFalse(choiceSet.GetIsRequired());
        Assert::IsTrue(choiceSet.GetErrorMessage().empty());

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

		Assert::AreEqual("Input.ChoiceSet_label"s, choiceSet.GetLabel());
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

    void ValidateActionSet(const ActionSet &actionSet)
    {
        auto actions = actionSet.GetActions();
        Assert::AreEqual(size_t{ 2 }, actions.size());

        auto submitAction = actions.at(0);
        Assert::AreEqual("ActionSet.Action.Submit_id", submitAction->GetId().c_str());
        Assert::IsTrue(std::static_pointer_cast<SubmitAction>(submitAction)->GetIgnoreInputValidation());

        auto openUrlAction = actions.at(1);
        Assert::AreEqual("ActionSet.Action.OpenUrl_id", openUrlAction->GetId().c_str());
    }

    void ValidateRichTextBlock(const RichTextBlock &richTextBlock)
    {
        Assert::IsTrue(richTextBlock.GetElementType() == CardElementType::RichTextBlock);
        Assert::AreEqual(CardElementTypeToString(CardElementType::RichTextBlock), richTextBlock.GetElementTypeString());
        Assert::AreEqual("RichTextBlock_id"s, richTextBlock.GetId());
        Assert::IsTrue(HorizontalAlignment::Right == richTextBlock.GetHorizontalAlignment());

        auto inlines = richTextBlock.GetInlines();
        Assert::AreEqual(size_t(3), inlines.size());

        Assert::IsTrue(InlineElementType::TextRun == inlines[0]->GetInlineType());
        Assert::AreEqual("TextRun"s, inlines[0]->GetInlineTypeString());

        auto inlineTextElement = std::static_pointer_cast<TextRun>(inlines[0]);

        Assert::AreEqual("This is a text run"s, inlineTextElement->GetText());
        Assert::IsTrue(ForegroundColor::Dark == inlineTextElement->GetTextColor());
        Assert::AreEqual("en"s, inlineTextElement->GetLanguage());
        Assert::IsTrue(TextSize::Large == inlineTextElement->GetTextSize());
        Assert::IsTrue(TextWeight::Bolder == inlineTextElement->GetTextWeight());
        Assert::IsTrue(FontType::Monospace == inlineTextElement->GetFontType());
        Assert::IsTrue(inlineTextElement->GetIsSubtle());
        Assert::IsTrue(inlineTextElement->GetItalic());
        Assert::IsTrue(inlineTextElement->GetHighlight());
        Assert::IsTrue(inlineTextElement->GetStrikethrough());
        Assert::IsTrue(inlineTextElement->GetUnderline());

        Assert::IsTrue(InlineElementType::TextRun == inlines[1]->GetInlineType());
        Assert::AreEqual("TextRun"s, inlines[1]->GetInlineTypeString());

        inlineTextElement = std::static_pointer_cast<TextRun>(inlines[1]);
        auto selectAction = inlineTextElement->GetSelectAction();
        Assert::IsTrue(selectAction != nullptr);
        Assert::IsTrue(ActionType::Submit == selectAction->GetElementType());
        Assert::IsFalse(std::static_pointer_cast<SubmitAction>(selectAction)->GetIgnoreInputValidation());

        Assert::IsTrue(InlineElementType::TextRun == inlines[1]->GetInlineType());
        Assert::AreEqual("TextRun"s, inlines[1]->GetInlineTypeString());

        inlineTextElement = std::static_pointer_cast<TextRun>(inlines[2]);
        Assert::AreEqual("This is a text run specified as a string"s, inlineTextElement->GetText());
    }

    void ValidateBody(const AdaptiveCard &everythingBagel)
    {
        auto body = everythingBagel.GetBody();
        Assert::AreEqual(size_t{ 10 }, body.size());

        // validate textblock (no fontType)
        auto textBlock = std::static_pointer_cast<TextBlock>(body.at(0));
        ValidateTextBlock(*textBlock, FontType::Default, "TextBlock_id");

        // validate textblock (monospace)
        textBlock = std::static_pointer_cast<TextBlock>(body.at(1));
        ValidateTextBlock(*textBlock, FontType::Monospace, "TextBlock_id_mono");

        // validate textblock (default)
        textBlock = std::static_pointer_cast<TextBlock>(body.at(2));
        ValidateTextBlock(*textBlock, FontType::Default, "TextBlock_id_def");

        // validate image
        auto image = std::static_pointer_cast<Image>(body.at(3));
        ValidateImage(*image);

        // validate columnset container
        auto columnSetContainer = std::static_pointer_cast<Container>(body.at(4));
        ValidateColumnSetContainer(*columnSetContainer);

        // validate factset
        auto factSet = std::static_pointer_cast<FactSet>(body.at(5));
        ValidateFactSet(*factSet);

        // validate imageset
        auto imageSet = std::static_pointer_cast<ImageSet>(body.at(6));
        ValidateImageSet(*imageSet);

        // validate input container
        auto inputContainer = std::static_pointer_cast<Container>(body.at(7));
        ValidateInputContainer(*inputContainer);

        // validate action set
        auto actionSet = std::static_pointer_cast<ActionSet>(body.at(8));
        ValidateActionSet(*actionSet);

        auto richTextBlock = std::static_pointer_cast<RichTextBlock>(body.at(9));
        ValidateRichTextBlock(*richTextBlock);
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
            Assert::AreEqual("{\"submitValue\":true}\n"s, submitAction->GetDataJson());
            Assert::IsFalse(submitAction->GetIgnoreInputValidation());

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
            Assert::AreEqual(size_t{ 1 }, resourceUris.size());

            // validate the subcard
            {
                auto subCard = std::static_pointer_cast<AdaptiveCard>(showCardAction->GetCard());
                Assert::AreEqual(size_t{ 0 }, subCard->GetActions().size());
                ValidateBackgroundImage(*subCard->GetBackgroundImage(), ImageFillMode::Repeat, HorizontalAlignment::Right, VerticalAlignment::Center);
                Assert::IsTrue(CardElementType::AdaptiveCard == subCard->GetElementType());
                Assert::AreEqual(""s, subCard->GetFallbackText());
                Assert::IsTrue(HeightType::Auto == subCard->GetHeight());
                Assert::AreEqual("en"s, subCard->GetLanguage());
                Assert::IsTrue(!subCard->GetSelectAction());
                Assert::AreEqual(""s, subCard->GetSpeak());
                Assert::IsTrue(ContainerStyle::None == subCard->GetStyle());
                Assert::AreEqual("1.0"s, subCard->GetVersion());
                Assert::IsTrue(VerticalContentAlignment::Top == subCard->GetVerticalContentAlignment());

                //Logger::WriteMessage("Submit Data: '"s.append(subCard->Serialize()).append("'").c_str());
                Assert::AreEqual("{\"actions\":[],\"backgroundImage\":{\"fillMode\":\"repeat\",\"horizontalAlignment\":\"right\",\"url\":\"https://adaptivecards.io/content/cats/1.png\",\"verticalAlignment\":\"center\"},\"body\":[{\"isSubtle\":true,\"text\":\"Action.ShowCard text\",\"type\":\"TextBlock\"}],\"lang\":\"en\",\"type\":\"AdaptiveCard\",\"version\":\"1.0\"}\n"s,
                    subCard->Serialize());
            }
        }
    }

    void ValidateFallbackCard(const AdaptiveCard &everythingBagel)
    {
        auto fallbackCard = everythingBagel.MakeFallbackTextCard("fallback"s, "en"s, "speak"s);
        auto fallbackTextBlock = std::static_pointer_cast<TextBlock>(fallbackCard->GetBody().at(0));
        Assert::AreEqual("fallback"s, fallbackTextBlock->GetText());
        Assert::AreEqual("en"s, fallbackTextBlock->GetLanguage());
        Assert::AreEqual("speak"s, fallbackCard->GetSpeak());
    }

    TEST_CLASS(EverythingBagel)
    {
    public:
        TEST_METHOD(EverythingBagelTests)
        {
            auto parseResult = AdaptiveCard::DeserializeFromFile("EverythingBagel.json", "1.0");

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
            Logger::WriteMessage("Expected: '"s.append(EVERYTHING_JSON).append("'").c_str());
            Logger::WriteMessage("Actual: '"s.append(everythingBagel->Serialize()).append("'").c_str());
            const std::string expectedJson {EVERYTHING_JSON};
            const std::string actualJson {everythingBagel->Serialize()};
            Assert::AreEqual(expectedJson, actualJson);
        }
    };
}
