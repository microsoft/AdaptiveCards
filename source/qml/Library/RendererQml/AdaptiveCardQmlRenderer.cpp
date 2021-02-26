#include "AdaptiveCardQmlRenderer.h"
#include "pch.h"

namespace RendererQml
{
	AdaptiveCardQmlRenderer::AdaptiveCardQmlRenderer()
		: AdaptiveCardQmlRenderer(std::make_shared<AdaptiveCards::HostConfig>())
	{
	}

	AdaptiveCardQmlRenderer::AdaptiveCardQmlRenderer(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig)
		: AdaptiveCardsRendererBase(AdaptiveCards::SemanticVersion("1.2"))
	{
		SetObjectTypes();
		SetHostConfig(hostConfig);
	}

	std::shared_ptr<RenderedQmlAdaptiveCard> AdaptiveCardQmlRenderer::RenderCard(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, AdaptiveCardDependency::OnClickFunction onClick)
	{
		std::shared_ptr<RenderedQmlAdaptiveCard> output;
		auto context = std::make_shared<AdaptiveRenderContext>(GetHostConfig(), GetElementRenderers());
		context->SetOnClickFunction(onClick);
		std::shared_ptr<QmlTag> tag;

		try
		{
			context->SetLang(card->GetLanguage());
			tag = context->Render(card, &AdaptiveCardRender);
			output = std::make_shared<RenderedQmlAdaptiveCard>(tag, card, context->GetWarnings());
		}
		catch (const std::exception & e)
		{
			context->AddWarning(AdaptiveWarning(Code::RenderException, e.what()));
		}

		return output;
	}

    void AdaptiveCardQmlRenderer::AddContainerElements(std::shared_ptr<QmlTag> uiContainer, const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& elements, std::shared_ptr<AdaptiveRenderContext> context)
    {
        if (!elements.empty())
        {
            auto bodyLayout = std::make_shared<QmlTag>("Column");
            bodyLayout->Property("id", "bodyLayout");
            bodyLayout->Property("width", "parent.width");
            //TODO: Set spacing from host config
            bodyLayout->Property("spacing", "8");
            uiContainer->Property("Layout.preferredHeight", "bodyLayout.height");
            uiContainer->AddChild(bodyLayout);

            for (const auto& cardElement : elements)
            {
                auto uiElement = context->Render(cardElement);

                if (uiElement != nullptr)
                {
                    //TODO: Add separator
                    //TODO: Add collection element
                    bodyLayout->AddChild(uiElement);
                }
            }
        }
    }

    void AdaptiveCardQmlRenderer::SetObjectTypes()
    {
        (*GetElementRenderers()).Set<AdaptiveCards::TextBlock>(AdaptiveCardQmlRenderer::TextBlockRender);
        (*GetElementRenderers()).Set<AdaptiveCards::RichTextBlock>(AdaptiveCardQmlRenderer::RichTextBlockRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Image>(AdaptiveCardQmlRenderer::ImageRender);
        /*(*GetElementRenderers()).Set<AdaptiveCards::Media>(AdaptiveCardQmlRenderer::MediaRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Container>(AdaptiveCardQmlRenderer::ContainerRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Column>(AdaptiveCardQmlRenderer::ColumnRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ColumnSet>(AdaptiveCardQmlRenderer::ColumnSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::FactSet>(AdaptiveCardQmlRenderer::FactSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ImageSet>(AdaptiveCardQmlRenderer::ImageSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ActionSet>(AdaptiveCardQmlRenderer::ActionSetRender);*/
        (*GetElementRenderers()).Set<AdaptiveCards::ChoiceSetInput>(AdaptiveCardQmlRenderer::ChoiceSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::TextInput>(AdaptiveCardQmlRenderer::TextInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::NumberInput>(AdaptiveCardQmlRenderer::NumberInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::DateInput>(AdaptiveCardQmlRenderer::DateInputRender);
        /*(*GetElementRenderers()).Set<AdaptiveCards::TimeInput>(AdaptiveCardQmlRenderer::TimeInputRender);
        /*(*GetElementRenderers()).Set<AdaptiveCards::DateInput>(AdaptiveCardQmlRenderer::DateInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::TimeInput>(AdaptiveCardQmlRenderer::TimeInputRender);*/
        (*GetElementRenderers()).Set<AdaptiveCards::ToggleInput>(AdaptiveCardQmlRenderer::ToggleInputRender);
        /*(*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::OpenUrlAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ShowCardAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ToggleVisibilityAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);*/
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::AdaptiveCardRender(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto uiCard = std::make_shared<QmlTag>("Rectangle");
        uiCard->AddImports("import QtQuick 2.15");
        uiCard->AddImports("import QtQuick.Layouts 1.3");
        uiCard->AddImports("import QtQuick.Controls 2.15");
        uiCard->AddImports("import QtGraphicalEffects 1.15");
        uiCard->Property("id", "adaptiveCard");
        uiCard->Property("implicitHeight", "adaptiveCardLayout.implicitHeight");
        //TODO: Width can be set as config
        uiCard->Property("width", "600");

		auto columnLayout = std::make_shared<QmlTag>("ColumnLayout");
		columnLayout->Property("id", "adaptiveCardLayout");
		columnLayout->Property("width", "parent.width");
		uiCard->AddChild(columnLayout);

		auto rectangle = std::make_shared<QmlTag>("Rectangle");
		rectangle->Property("id", "adaptiveCardRectangle");
		rectangle->Property("color", context->GetRGBColor(context->GetConfig()->GetContainerStyles().defaultPalette.backgroundColor));
		rectangle->Property("Layout.margins", std::to_string(context->GetConfig()->GetSpacing().paddingSpacing));
		rectangle->Property("Layout.fillWidth", "true");
		rectangle->Property("Layout.preferredHeight", "40");

		if (card->GetMinHeight() > 0)
		{
			rectangle->Property("Layout.minimumHeight", std::to_string(card->GetMinHeight()));
		}
		columnLayout->AddChild(rectangle);

		//TODO: Add card vertical content alignment

		AddContainerElements(rectangle, card->GetBody(), context);

		return uiCard;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::TextBlockRender(std::shared_ptr<AdaptiveCards::TextBlock> textBlock, std::shared_ptr<AdaptiveRenderContext> context)
	{
		//TODO:Parse markdown in the text

		//TODO: To get the Qml equivalant of monospace fontType and add it to config
		std::string fontFamily = context->GetConfig()->GetFontFamily(textBlock->GetFontType());
		int fontSize = context->GetConfig()->GetFontSize(textBlock->GetFontType(), textBlock->GetTextSize());

		auto uiTextBlock = std::make_shared<QmlTag>("Text");
		std::string textType = textBlock->GetElementTypeString();
		std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(textBlock->GetHorizontalAlignment());

		uiTextBlock->Property("width", "parent.width");
		uiTextBlock->Property("elide", "Text.ElideRight");
		uiTextBlock->Property("text", "\"" + textBlock->GetText() + "\"");

		uiTextBlock->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));

		//TODO: Need to fix the color calculation
		std::string color = context->GetColor(textBlock->GetTextColor(), textBlock->GetIsSubtle(), false);

		uiTextBlock->Property("color", color);

		//Value based on what is mentioned in the html renderer
		uiTextBlock->Property("lineHeight", "1.33");

		uiTextBlock->Property("font.pixelSize", std::to_string(fontSize));

		//TODO: lighter weight showing same behaviour as default
		uiTextBlock->Property("font.weight", Utils::GetWeight(textBlock->GetTextWeight()));

		if (!textBlock->GetId().empty())
		{
			uiTextBlock->Property("id", textBlock->GetId());
		}

		if (!textBlock->GetIsVisible())
		{
			uiTextBlock->Property("visible", "false");
		}

		if (textBlock->GetMaxLines() > 0)
		{
			uiTextBlock->Property("maximumLineCount", std::to_string(textBlock->GetMaxLines()));
		}

		if (textBlock->GetWrap())
		{
			uiTextBlock->Property("wrapMode", "Text.WordWrap");
		}

		if (!fontFamily.empty())
		{
			uiTextBlock->Property("font.family", fontFamily);
		}

		return uiTextBlock;

	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::TextInputRender(std::shared_ptr<AdaptiveCards::TextInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
		//TODO: Add inline action

		std::shared_ptr<QmlTag> uiTextInput;
		std::shared_ptr<QmlTag> scrollViewTag;

		if (input->GetIsMultiline())
		{
			scrollViewTag = std::make_shared<QmlTag>("ScrollView");
			scrollViewTag->Property("width", "parent.width");
			scrollViewTag->Property("height", "50");
			scrollViewTag->Property("ScrollBar.vertical.interactive", "true");

			uiTextInput = std::make_shared<QmlTag>("TextArea");
			uiTextInput->Property("id", input->GetId());
			uiTextInput->Property("wrapMode", "Text.Wrap");
			uiTextInput->Property("padding", "10");

			if (input->GetMaxLength() > 0)
			{
				uiTextInput->Property("onTextChanged", Formatter() << "remove(" << input->GetMaxLength() << ", length)");
			}

			scrollViewTag->AddChild(uiTextInput);
		}
		else
		{
			uiTextInput = std::make_shared<QmlTag>("TextField");
			uiTextInput->Property("id", input->GetId());
			uiTextInput->Property("width", "parent.width");

			if (input->GetMaxLength() > 0)
			{
				uiTextInput->Property("maximumLength", std::to_string(input->GetMaxLength()));
			}
		}

		uiTextInput->Property("font.pixelSize", std::to_string(context->GetConfig()->GetFontSize(AdaptiveSharedNamespace::FontType::Default, AdaptiveSharedNamespace::TextSize::Default)));

		auto glowTag = std::make_shared<QmlTag>("Glow");
		glowTag->Property("samples", "25");
		glowTag->Property("color", "'skyblue'");

		auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
		backgroundTag->Property("radius", "5");
		//TODO: These color styling should come from css
		backgroundTag->Property("color", Formatter() << input->GetId() << ".hovered ? 'lightgray' : 'white'");
		backgroundTag->Property("border.color", Formatter() << input->GetId() << ".activeFocus? 'black' : 'grey'");
		backgroundTag->Property("border.width", "1");
		backgroundTag->Property("layer.enabled", Formatter() << input->GetId() << ".activeFocus ? true : false");
		backgroundTag->Property("layer.effect", glowTag->ToString());
		uiTextInput->Property("background", backgroundTag->ToString());

		if (!input->GetValue().empty())
		{
			uiTextInput->Property("text", "\"" + input->GetValue() + "\"");
		}

		if (!input->GetPlaceholder().empty())
		{
			uiTextInput->Property("placeholderText", "\"" + input->GetPlaceholder() + "\"");
		}

		//TODO: Add stretch property

		if (!input->GetIsVisible())
		{
			uiTextInput->Property("visible", "false");
		}

		if (input->GetIsMultiline())
		{
			return scrollViewTag;
		}

		return uiTextInput;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::NumberInputRender(std::shared_ptr<AdaptiveCards::NumberInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const auto inputId = input->GetId();

		auto glowTag = std::make_shared<QmlTag>("Glow");
		glowTag->Property("samples", "25");
		glowTag->Property("color", "'skyblue'");

		auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
		backgroundTag->Property("radius", "5");
		//TODO: These color styling should come from css
		backgroundTag->Property("color", Formatter() << inputId + "_contentItem" << ".hovered ? 'lightgray' : 'white'");
		backgroundTag->Property("layer.enabled", Formatter() << inputId + "_contentItem" << ".activeFocus ? true : false");
		backgroundTag->Property("layer.effect", glowTag->ToString());

		auto contentItemTag = std::make_shared<QmlTag>("TextField");
		contentItemTag->Property("id", inputId + "_contentItem");
		contentItemTag->Property("padding", "10");
		contentItemTag->Property("font.pixelSize", std::to_string(context->GetConfig()->GetFontSize(AdaptiveSharedNamespace::FontType::Default, AdaptiveSharedNamespace::TextSize::Default)));
		contentItemTag->Property("readOnly", Formatter() << "!" << inputId << ".editable");
		contentItemTag->Property("validator", Formatter() << inputId << ".validator");
		contentItemTag->Property("inputMethodHints", "Qt.ImhFormattedNumbersOnly");
		contentItemTag->Property("text", Formatter() << inputId << ".textFromValue(" << inputId << ".value, " << inputId << ".locale)");
		if (!input->GetPlaceholder().empty())
		{
			contentItemTag->Property("placeholderText", "\"" + input->GetPlaceholder() + "\"");
		}
		contentItemTag->Property("background", backgroundTag->ToString());

		auto doubleValidatorTag = std::make_shared<QmlTag>("DoubleValidator");

		auto uiNumberInput = std::make_shared<QmlTag>("SpinBox");
		uiNumberInput->Property("id", input->GetId());
		uiNumberInput->Property("width", "parent.width");
		uiNumberInput->Property("stepSize", "1");
		uiNumberInput->Property("editable", "true");
		uiNumberInput->Property("validator", doubleValidatorTag->ToString());

		if ((input->GetMin() == input->GetMax() && input->GetMin() == 0) || input->GetMin() > input->GetMax())
		{
			input->SetMin(INT_MIN);
			input->SetMax(INT_MAX);
		}
		if (input->GetValue() < input->GetMin())
		{
			input->SetValue(input->GetMin());
		}
		if (input->GetValue() > input->GetMax())
		{
			input->SetValue(input->GetMax());
		}

		uiNumberInput->Property("from", std::to_string(input->GetMin().value()));
		uiNumberInput->Property("to", std::to_string(input->GetMax().value()));
		uiNumberInput->Property("value", std::to_string(input->GetValue().value()));

		//TODO: Add stretch property

		if (!input->GetIsVisible())
		{
			uiNumberInput->Property("visible", "false");
		}

		uiNumberInput->Property("contentItem", contentItemTag->ToString());

		return uiNumberInput;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::RichTextBlockRender(std::shared_ptr<AdaptiveCards::RichTextBlock> richTextBlock, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto uiTextBlock = std::make_shared<QmlTag>("Text");
		std::string textType = richTextBlock->GetElementTypeString();
		std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(richTextBlock->GetHorizontalAlignment());

		uiTextBlock->Property("textFormat", "Text.RichText");
		uiTextBlock->Property("wrapMode", "Text.WordWrap");
		uiTextBlock->Property("width", "parent.width");

		uiTextBlock->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));
		std::string textrun_all = "\"";

		if (!richTextBlock->GetIsVisible())
		{
			uiTextBlock->Property("visible", "false");
		}

		for (const auto& inlineRun : richTextBlock->GetInlines())
		{
			if (Utils::IsInstanceOfSmart<AdaptiveCards::TextRun>(inlineRun))
			{
				auto textRun = std::dynamic_pointer_cast<AdaptiveCards::TextRun>(inlineRun);
				textrun_all.append(TextRunRender(textRun, context));
			}
		}
		textrun_all = textrun_all.append("\"");
		uiTextBlock->Property("text", textrun_all);

		return uiTextBlock;

	}

	std::string AdaptiveCardQmlRenderer::TextRunRender(std::shared_ptr<AdaptiveCards::TextRun> textRun, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const std::string fontFamily = context->GetConfig()->GetFontFamily(textRun->GetFontType());
		const int fontSize = context->GetConfig()->GetFontSize(textRun->GetFontType(), textRun->GetTextSize());
		const int weight = context->GetConfig()->GetFontWeight(textRun->GetFontType(), textRun->GetTextWeight());

		//Value based on what is mentioned in the html renderer
		const auto lineHeight = fontSize * 1.33;

		std::string uiTextRun = "<span style='";
		std::string textType = textRun->GetInlineTypeString();

		//TODO: Add font to hostconfig
		uiTextRun.append("font-family:" + std::string("\\\"") + fontFamily + std::string("\\\"") + ";");

		//TODO: Need to fix the color calculation
		std::string color = context->GetColor(textRun->GetTextColor(), textRun->GetIsSubtle(), false).substr(3);
		uiTextRun.append("color:" + color + ";");

		std::string lineheight = Formatter() << std::fixed << std::setprecision(2) << lineHeight << "px";
		uiTextRun.append("line-height:" + lineheight + ";");

		uiTextRun.append("font-size:" + std::to_string(fontSize) + "px" + ";");

		uiTextRun.append("font-weight:" + std::to_string(weight) + ";");

		//TODO: Exact calculation for background color
		if (textRun->GetHighlight())
		{
			uiTextRun.append("background-color:" + Utils::GetTextHighlightColor(color) + ";");
		}

		if (textRun->GetItalic())
		{
			uiTextRun.append("font-style:" + std::string("italic") + ";");
		}

		if (textRun->GetStrikethrough())
		{
			uiTextRun.append("text-decoration:" + std::string("line-through") + ";");
		}

		uiTextRun.append("'>");
		uiTextRun.append(TextUtils::ApplyTextFunctions(textRun->GetText(), context->GetLang()));
		uiTextRun.append("</span>");

		return uiTextRun;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ToggleInputRender(std::shared_ptr<AdaptiveCards::ToggleInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const auto valueOn = !input->GetValueOn().empty() ? input->GetValueOn() : "true";
		const auto valueOff = !input->GetValueOff().empty() ? input->GetValueOff() : "false";
		const bool isChecked = input->GetValue().compare(valueOn) == 0 ? true : false;

		//TODO: Add Height
		return GetCheckBox(RendererQml::Checkbox(input->GetId(),
			CheckBoxType::Toggle,
			input->GetTitle(),
			input->GetValue(),
			valueOn,
			valueOff,
			context->GetConfig()->GetFontSize(AdaptiveCards::FontType::Default, AdaptiveCards::TextSize::Default),
			input->GetWrap(),
			input->GetIsVisible(),
			isChecked));

	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ChoiceSetRender(std::shared_ptr<AdaptiveCards::ChoiceSetInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
		int ButtonNumber = 0;
		RendererQml::Checkboxes choices;
		const std::string id = input->GetId();
		enum CheckBoxType type = !input->GetIsMultiSelect() && input->GetChoiceSetStyle() == AdaptiveCards::ChoiceSetStyle::Compact ? ComboBox : input->GetIsMultiSelect() ? CheckBox : RadioButton;
		const int fontSize = context->GetConfig()->GetFontSize(AdaptiveCards::FontType::Default, AdaptiveCards::TextSize::Default);
		const bool isWrap = input->GetWrap();
		const bool isVisible = input->GetIsVisible();
		bool isChecked;

		std::vector<std::string> parsedValues;
		parsedValues = Utils::ParseChoiceSetInputDefaultValues(input->GetValue());

		for (const auto& choice : input->GetChoices())
		{
			isChecked = (std::find(parsedValues.begin(), parsedValues.end(), choice->GetValue()) != parsedValues.end() && (input->GetIsMultiSelect() || parsedValues.size() == 1)) ? true : false;
			choices.emplace_back(RendererQml::Checkbox(id + GenerateButtonId(type, ButtonNumber++),
				type,
				choice->GetTitle(),
				choice->GetValue(),
				fontSize,
				isWrap,
				isVisible,
				isChecked));
		}

		RendererQml::ChoiceSet choiceSet(id,
			input->GetIsMultiSelect(),
			input->GetChoiceSetStyle(),
			parsedValues,
			choices,
			input->GetPlaceholder());

		if (CheckBoxType::ComboBox == type)
		{
			return GetComboBox(choiceSet);
		}
		else
		{
			return GetButtonGroup(choiceSet);
		}

		std::shared_ptr<QmlTag> uiColumn;
		return uiColumn;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetComboBox(ChoiceSet choiceset)
	{
		auto uiComboBox = std::make_shared<QmlTag>("ComboBox");
				
		uiComboBox->Property("id",choiceset.id);
		uiComboBox->Property("textRole", "'text'");
		uiComboBox->Property("valueRole", "'value'");
		uiComboBox->Property("width", "parent.width");
		//TODO : Add Height
				
		uiComboBox->Property("model", GetModel(choiceset.choices)); 
				
		if (!choiceset.placeholder.empty())
		{
			uiComboBox->Property("currentIndex", "-1");
			uiComboBox->Property("displayText", "currentIndex === -1 ? '" + choiceset.placeholder + "' : currentText");
		}
		else if (choiceset.values.size() ==1)
		{
			std::string target = choiceset.values[0];
			auto index = std::find_if(choiceset.choices.begin(), choiceset.choices.end(), [target](const Checkbox& options) {
				return options.value == target;
				}) - choiceset.choices.begin();
			uiComboBox->Property("currentIndex", std::to_string(index));
			uiComboBox->Property("displayText", "currentText");
		}
		
		auto uiItemDelegate = std::make_shared<QmlTag>("ItemDelegate");
		uiItemDelegate->Property("width", "parent.width");
		
		auto uiItemDelegate_Text = std::make_shared<QmlTag>("Text");
		uiItemDelegate_Text->Property("text", "modelData.text");
		uiItemDelegate_Text->Property("font", "parent.font");
		uiItemDelegate_Text->Property("verticalAlignment", "Text.AlignVCenter");

		if (choiceset.choices[0].isWrap)
		{
			uiItemDelegate_Text->Property("wrapMode", "Text.Wrap");
		}
		else
		{
			uiItemDelegate_Text->Property("elide", "Text.ElideRight");
		}

		uiItemDelegate->Property("contentItem", uiItemDelegate_Text->ToString());
				
		uiComboBox->Property("delegate", uiItemDelegate->ToString());

		auto uiContentItem_Text = std::make_shared<QmlTag>("Text");
		uiContentItem_Text->Property("text", "parent.displayText");
		uiContentItem_Text->Property("font", "parent.font");
		uiContentItem_Text->Property("verticalAlignment", "Text.AlignVCenter");
		uiContentItem_Text->Property("leftPadding", "parent.font.pixelSize + parent.spacing");
		uiContentItem_Text->Property("elide", "Text.ElideRight");
				
		uiComboBox->Property("contentItem", uiContentItem_Text->ToString());
				
		return uiComboBox;
	}

	std::string AdaptiveCardQmlRenderer::GetModel(std::vector<Checkbox>& Choices)
	{
		std::ostringstream model;
		model << "[";
		for (const auto& choice : Choices)
		{
			model << "{ value: '" << choice.value << "', text: '" << choice.text << "'},\n";
		}
		model << "]";
		return model.str();
	}

	// Default values are specified by a comma separated string
	std::vector<std::string> Utils::ParseChoiceSetInputDefaultValues(const std::string& value)
	{
		std::vector<std::string> parsedValues;
		std::string element;
		std::stringstream ss(value);
		while (std::getline(ss, element, ','))
		{
			Utils::Trim(element);		
			if (!element.empty())
			{
				parsedValues.push_back(element);
			}
		}
		return parsedValues;
	}

	std::string AdaptiveCardQmlRenderer::GenerateButtonId(enum CheckBoxType ButtonType, int  ButtonNumber)
	{
		
		return "_" + std::to_string(ButtonType) + "_" + std::to_string(ButtonNumber);
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetButtonGroup(ChoiceSet choiceset)
	{
		auto uiColumn = std::make_shared<QmlTag>("Column");
	
		auto uiButtonGroup = std::make_shared<QmlTag>("ButtonGroup");
	
		uiButtonGroup->Property("id", choiceset.id);
	
		if (choiceset.isMultiSelect)
		{
			uiButtonGroup->Property("buttons", choiceset.id + "_checkbox.children");
			uiButtonGroup->Property("exclusive", "false");
		}
		else
		{
			uiButtonGroup->Property("buttons", choiceset.id + "_radio.children");
		}
	
		uiColumn->AddChild(uiButtonGroup);
	
		auto uiInnerColumn = std::make_shared<QmlTag>("ColumnLayout");
	
		if (choiceset.isMultiSelect)
		{
			uiInnerColumn->Property("id", choiceset.id + "_checkbox");
		}
		else
		{
			uiInnerColumn->Property("id", choiceset.id + "_radio");
		}
	
		// render as a series of buttons
		for (const auto& choice : choiceset.choices)
		{
			uiInnerColumn->AddChild(GetCheckBox(choice));
		}
	
		uiColumn->AddChild(uiInnerColumn);
		return uiColumn;
	}


	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetCheckBox(Checkbox checkbox)
	{
		std::shared_ptr<QmlTag> uiButton;

		if (checkbox.type == CheckBoxType::RadioButton)
		{
			uiButton = std::make_shared<QmlTag>("RadioButton");
		}
		else
		{
			uiButton = std::make_shared<QmlTag>("CheckBox");
		}

		if (checkbox.type == CheckBoxType::Toggle)
		{
			uiButton->Property("readonly property string valueOn", "\"" + checkbox.valueOn + "\"");
			uiButton->Property("readonly property string valueOff", "\"" + checkbox.valueOff + "\"");
		}

		uiButton->Property("id", checkbox.id);
		uiButton->Property("text", "\"" + checkbox.text + "\"");
		uiButton->Property("width", "parent.width");
		uiButton->Property("font.pixelSize", std::to_string(checkbox.fontSize));

		if (!checkbox.isVisible)
		{
			uiButton->Property("visible", "false");
		}
		
		if (checkbox.isChecked)
		{
			uiButton->Property("checked", "true");
		}
	
		auto uiOuterRectangle = std::make_shared<QmlTag>("Rectangle");
		uiOuterRectangle->Property("width", "parent.font.pixelSize");
		uiOuterRectangle->Property("height", "parent.font.pixelSize");
		uiOuterRectangle->Property("y", "parent.topPadding + (parent.availableHeight - height) / 2");
		if (checkbox.type == CheckBoxType::RadioButton)
		{
			uiOuterRectangle->Property("radius", "height/2"); 
		}
		else
		{
			uiOuterRectangle->Property("radius", "3");
		}
		uiOuterRectangle->Property("border.color", checkbox.id + ".checked ? '#0075FF' : '767676'");
	
		//To be replaced with image of checkmark.
		auto uiInnerRectangle = std::make_shared<QmlTag>("Rectangle");
		uiInnerRectangle->Property("width", "parent.width/2");
		uiInnerRectangle->Property("height", "parent.height/2");
		uiInnerRectangle->Property("x", "width/2");
		uiInnerRectangle->Property("y", "height/2");
		if (checkbox.type == CheckBoxType::RadioButton)
		{
			uiInnerRectangle->Property("radius", "height/2");
		}
		else
		{
			uiInnerRectangle->Property("radius", "2"); 
		}
		uiInnerRectangle->Property("color", checkbox.id + ".down ? '#ffffff' : '#0075FF'");
		uiInnerRectangle->Property("visible", checkbox.id + ".checked");
	
		uiOuterRectangle->AddChild(uiInnerRectangle);
	
		uiButton->Property("indicator", uiOuterRectangle->ToString());
	
		auto uiText = std::make_shared<QmlTag>("Text");
		uiText->Property("text", "parent.text");
		uiText->Property("font", "parent.font");
		uiText->Property("horizontalAlignment", "Text.AlignLeft");
		uiText->Property("verticalAlignment", "Text.AlignVCenter");
		uiText->Property("leftPadding", "parent.indicator.width + parent.spacing");
	
		if (checkbox.isWrap)
		{
			uiText->Property("wrapMode", "Text.Wrap");
		}
		else
		{
			uiText->Property("elide", "Text.ElideRight");
		}
	
		uiButton->Property("contentItem", uiText->ToString());
	
		return uiButton;
	}
    
    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::DateInputRender(std::shared_ptr<AdaptiveCards::DateInput> input, std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto uiDateInput = std::make_shared<QmlTag>("TextField");

        uiDateInput->Property("id", input->GetId());
        uiDateInput->Property("width", "parent.width");
        const int fontSize = context->GetConfig()->GetFontSize(AdaptiveCards::FontType::Default, AdaptiveCards::TextSize::Default);

        uiDateInput->Property("font.family", "\"" + context->GetConfig()->GetFontFamily(AdaptiveCards::FontType::Default) + "\"");
        uiDateInput->Property("font.pixelSize", std::to_string(fontSize));


        uiDateInput->Property("placeholderText", Formatter() << (!input->GetPlaceholder().empty() ? "\"" + input->GetPlaceholder() + "\"" : "\"mm-dd-yyyy\""));

        if (!input->GetValue().empty())
        {
            uiDateInput->Property("text", "\"" + Utils::GetDate(input->GetValue(), false) + "\"");
        }

        //TODO: Add stretch property

        if (!input->GetIsVisible())
        {
            uiDateInput->Property("visible", "false");
        }

        uiDateInput->Property("validator", "RegExpValidator { regExp: /^(0[0-9]|1[0-2])-(0?[0-9]|[12][0-9]|3[01])-(\\d{4})$/}");

        std::string calendar_box_id = input->GetId() + "_cal_box";

        uiDateInput->Property("inputMask", "text != \"\" ? \"00-00-0000;0\" : \"\"");
        uiDateInput->Property("onFocusChanged", "{if(activeFocus === false){ z=0; if( " + calendar_box_id + ".visible === true){ " + calendar_box_id + ".visible=false}}}");

        auto glowTag = std::make_shared<QmlTag>("Glow");
        glowTag->Property("samples", "25");
        glowTag->Property("color", "'skyblue'");

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        backgroundTag->Property("radius", "5");
        //TODO: These color styling should come from css
        backgroundTag->Property("color", Formatter() << input->GetId() << ".hovered ? 'lightgray' : 'white'");
        backgroundTag->Property("border.color", Formatter() << input->GetId() << ".activeFocus? 'black' : 'grey'");
        backgroundTag->Property("border.width", "1");
        backgroundTag->Property("layer.enabled", Formatter() << input->GetId() << ".activeFocus ? true : false");
        backgroundTag->Property("layer.effect", glowTag->ToString());
        uiDateInput->Property("background", backgroundTag->ToString());

        auto imageTag = std::make_shared<QmlTag>("Image");
        imageTag->Property("anchors.fill", "parent");
        imageTag->Property("anchors.margins", "5");

        //Finding absolute Path at runtime
        std::string file_path = __FILE__;
        std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
        dir_path.append("\\Images\\calendarIcon.png");
        std::replace(dir_path.begin(), dir_path.end(), '\\', '/');
        imageTag->Property("source", "\"" + std::string("file:/") + dir_path + "\"");

        //Relative wrt main.qml not working
        //imageTag->Property("source", "\"" + std::string("file:/../../Library/RendererQml/Images/calendarIcon.png") + "\"");


        auto mouseAreaTag = std::make_shared<QmlTag>("MouseArea");

        mouseAreaTag->AddChild(imageTag);
        mouseAreaTag->Property("height", "parent.height");
        mouseAreaTag->Property("width", "height");
        mouseAreaTag->Property("anchors.right", "parent.right");
        mouseAreaTag->Property("enabled", "true");

        std::string onClicked_value = "{ parent.focus=true; " + calendar_box_id + ".visible=!" + calendar_box_id + ".visible; parent.z=" + calendar_box_id + ".visible?1:0; }";
        mouseAreaTag->Property("onClicked", onClicked_value);

        uiDateInput->AddChild(mouseAreaTag);

        auto calendarTag = std::make_shared<QmlTag>("Calendar");
        calendarTag->AddImports("import QtQuick.Controls 1.4");
        calendarTag->Property("anchors.fill", "parent");
        calendarTag->Property("minimumDate", !input->GetMin().empty() ? Utils::GetDate(input->GetMin(), true) : "new Date(1900,1,1)");
        calendarTag->Property("maximumDate", !input->GetMax().empty() ? Utils::GetDate(input->GetMax(), true) : "new Date(2050,1,1)");
        calendarTag->Property("onReleased", "{parent.visible=false; " + input->GetId() + ".text=selectedDate.toLocaleString(Qt.locale(\"en_US\"), \"MM-dd-yyyy\")}");

        auto calendarBoxTag = std::make_shared<QmlTag>("Rectangle");
        calendarBoxTag->Property("id", calendar_box_id);
        calendarBoxTag->Property("visible", "false");
        calendarBoxTag->Property("anchors.left", "parent.left");
        calendarBoxTag->Property("anchors.top", "parent.bottom");
        calendarBoxTag->Property("width", "275");
        calendarBoxTag->Property("height", "275");
        calendarBoxTag->Property("Component.onCompleted", "{ Qt.createQmlObject('" + calendarTag->ToString() + "'," + calendar_box_id + ",'calendar')}");
        uiDateInput->AddChild(calendarBoxTag);

        return uiDateInput;
    }
	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ImageRender(std::shared_ptr<AdaptiveCards::Image> image, std::shared_ptr<AdaptiveRenderContext> context)
	{
		//TODO: Height(Stretch/Automatic)

		std::shared_ptr<QmlTag> maskTag;
		auto uiRectangle = std::make_shared<QmlTag>("Rectangle");
		auto uiImage = std::make_shared<QmlTag>("Image");

		std::string file_path = __FILE__;
		std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
		dir_path.append("\\Images\\Cat.png");
		std::replace(dir_path.begin(), dir_path.end(), '\\', '/');

		uiImage->Property("id", image->GetId());
		uiImage->Property("source", "\"" + std::string("file:/") + dir_path + "\"");
		uiImage->Property("width", "parent.width");
		uiImage->Property("fillMode", "Image.PreserveAspectFit");
		
		uiRectangle->Property("height", Formatter() << image->GetId() << ".implicitHeight");
		
		if (!image->GetIsVisible())
		{
			uiRectangle->Property("visible", "false");
		}

		if (image->GetPixelWidth() != 0 || image->GetPixelHeight() != 0)
		{
			if (image->GetPixelWidth() != 0)
			{
				uiRectangle->Property("width",  Formatter() << "Math.min(" << image->GetPixelWidth() << ", parent.width)");
			}
			if (image->GetPixelHeight() != 0)
			{
				uiRectangle->Property("height", Formatter() << image->GetPixelHeight());
				uiImage->Property("height", "parent.height");

				if (image->GetPixelWidth() == 0)
				{
					uiImage->RemoveProperty("width");
					uiImage->Property("fillMode", "height < implicitHeight ? Image.PreserveAspectFit : Image.NoOption");
					uiRectangle->Property("width", Formatter() << image->GetId() << ".width");
				}
				else
				{
					uiImage->RemoveProperty("fillMode");
				}
			}
		}
		else
		{
			switch (image->GetImageSize())
			{
			case AdaptiveCards::ImageSize::None:
			case AdaptiveCards::ImageSize::Auto:
				uiRectangle->Property("width", "parent.width");
				uiImage->RemoveProperty("fillMode");
				break;
			case AdaptiveCards::ImageSize::Small:
				uiRectangle->Property("width", Formatter() << context->GetConfig()->GetImageSizes().smallSize);
				break;
			case AdaptiveCards::ImageSize::Medium:
				uiRectangle->Property("width", Formatter() << context->GetConfig()->GetImageSizes().mediumSize);
				break;
			case AdaptiveCards::ImageSize::Large:
				uiRectangle->Property("width", Formatter() << context->GetConfig()->GetImageSizes().largeSize);
				break;
			case AdaptiveCards::ImageSize::Stretch:
				uiRectangle->Property("width", "parent.width");
				uiImage->RemoveProperty("fillMode");
				break;
			}
		}

		if (!image->GetBackgroundColor().empty())
		{
			uiRectangle->Property("color", context->GetRGBColor(image->GetBackgroundColor()));
		}

		switch (image->GetHorizontalAlignment())
		{
		case AdaptiveCards::HorizontalAlignment::Left:
			uiRectangle->Property("anchors.left", "parent.left");
			break;
		case AdaptiveCards::HorizontalAlignment::Center:
			uiRectangle->Property("anchors.horizontalCenter", "parent.horizontalCenter");
			break;
		case AdaptiveCards::HorizontalAlignment::Right:
			uiRectangle->Property("anchors.right", "parent.right");
			break;
		}

		//TODO:calculation to get oval object
		switch (image->GetImageStyle())
		{
		case AdaptiveCards::ImageStyle::Default:
			break;
		case AdaptiveCards::ImageStyle::Person:
			maskTag = std::make_shared<QmlTag>("OpacityMask");
			maskTag->Property("maskSource", "parent");
			uiImage->Property("layer.enabled", "true");
			uiImage->Property("layer.effect", maskTag->ToString());
			uiRectangle->Property("radius", "width/2");
			break;
		}

		uiRectangle->AddChild(uiImage);

		return uiRectangle;
	}
}
	
