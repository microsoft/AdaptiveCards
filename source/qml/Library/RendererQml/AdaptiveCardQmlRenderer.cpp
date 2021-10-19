#include "AdaptiveCardQmlRenderer.h"
#include "ImageDataURI.h"
#include "pch.h"

namespace RendererQml
{
	AdaptiveCardQmlRenderer::AdaptiveCardQmlRenderer()
		: AdaptiveCardQmlRenderer(std::make_shared<AdaptiveCards::HostConfig>(), std::make_shared<AdaptiveCardRenderConfig>())
	{
	}

	AdaptiveCardQmlRenderer::AdaptiveCardQmlRenderer(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig, std::shared_ptr<AdaptiveCardRenderConfig> renderConfig)
		: AdaptiveCardsRendererBase(AdaptiveCards::SemanticVersion("1.2"))
	{
		SetObjectTypes();
		SetHostConfig(hostConfig);
		SetRenderConfig(renderConfig);
	}

	std::shared_ptr<RenderedQmlAdaptiveCard> AdaptiveCardQmlRenderer::RenderCard(std::shared_ptr<AdaptiveCards::AdaptiveCard> card)
	{
		std::shared_ptr<RenderedQmlAdaptiveCard> output;
		auto context = std::make_shared<AdaptiveRenderContext>(GetHostConfig(), GetElementRenderers(), GetRenderConfig());
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

    void AdaptiveCardQmlRenderer::SetObjectTypes()
    {
        (*GetElementRenderers()).Set<AdaptiveCards::TextBlock>(AdaptiveCardQmlRenderer::TextBlockRender);
        (*GetElementRenderers()).Set<AdaptiveCards::RichTextBlock>(AdaptiveCardQmlRenderer::RichTextBlockRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Image>(AdaptiveCardQmlRenderer::ImageRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Media>(AdaptiveCardQmlRenderer::MediaRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Container>(AdaptiveCardQmlRenderer::ContainerRender);
        (*GetElementRenderers()).Set<AdaptiveCards::Column>(AdaptiveCardQmlRenderer::ColumnRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ColumnSet>(AdaptiveCardQmlRenderer::ColumnSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::FactSet>(AdaptiveCardQmlRenderer::FactSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ImageSet>(AdaptiveCardQmlRenderer::ImageSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ActionSet>(AdaptiveCardQmlRenderer::ActionSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ChoiceSetInput>(AdaptiveCardQmlRenderer::ChoiceSetRender);
        (*GetElementRenderers()).Set<AdaptiveCards::TextInput>(AdaptiveCardQmlRenderer::TextInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::NumberInput>(AdaptiveCardQmlRenderer::NumberInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::DateInput>(AdaptiveCardQmlRenderer::DateInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::TimeInput>(AdaptiveCardQmlRenderer::TimeInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ToggleInput>(AdaptiveCardQmlRenderer::ToggleInputRender);
        (*GetElementRenderers()).Set<AdaptiveCards::OpenUrlAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ShowCardAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ToggleVisibilityAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::AdaptiveCardRender(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::shared_ptr<AdaptiveRenderContext> context, bool isChildCard)
    {
        context->setDefaultIdName("defaultId");
		int margin = context->GetConfig()->GetSpacing().paddingSpacing;

        auto uiCard = std::make_shared<QmlTag>("Rectangle");
        uiCard->AddImports("import QtQuick 2.15");
        uiCard->AddImports("import QtQuick.Layouts 1.3");
        uiCard->AddImports("import QtQuick.Controls 2.15");
        uiCard->Property("id", "adaptiveCard");
        context->setCardRootId(uiCard->GetId());
		context->setCardRootElement(uiCard);
		uiCard->Property("readonly property int margins", std::to_string(margin));
        uiCard->AddFunctions("signal buttonClicked(var title, var type, var data)");
		//1px extra height to accomodate the border of a showCard if present at the bottom
        uiCard->Property("implicitHeight", "adaptiveCardLayout.implicitHeight+1");
		uiCard->Property("Layout.fillWidth", "true");
		uiCard->Property("readonly property string bgColor", context->GetRGBColor(context->GetConfig()->GetContainerStyles().defaultPalette.backgroundColor));
		uiCard->Property("readonly property string inputElementsBorderColor", "'#CCCCCC'");
		uiCard->Property("color", "bgColor");
		uiCard->Property("border.color", isChildCard? " bgColor" : "'#B2B2B2'");
        uiCard->AddFunctions("MouseArea{anchors.fill: parent;onClicked: adaptiveCard.nextItemInFocusChain().forceActiveFocus();}");
        uiCard->Property("activeFocusOnTab", "false");

        const auto hasBackgroundImage = card->GetBackgroundImage() != nullptr;
		if (hasBackgroundImage)
		{
			auto uiFrame = std::make_shared<QmlTag>("Frame");
            uiFrame->Property("id", Formatter() << uiCard->GetId() << "_frame");
			uiFrame->Property("readonly property bool hasBackgroundImage", "true");
            uiFrame->Property("property var imgSource", card->GetBackgroundImage()->GetUrl(), true);
			uiFrame->Property("anchors.fill", "parent");
			uiFrame->Property("background", AdaptiveCardQmlRenderer::GetBackgroundImage(card->GetBackgroundImage(), context, "parent.imgSource")->ToString());
			uiCard->Property("clip", "true");
			uiCard->AddChild(uiFrame);
		}

		auto columnLayout = std::make_shared<QmlTag>("ColumnLayout");
		columnLayout->Property("id", "adaptiveCardLayout");
		columnLayout->Property("width", "parent.width");
		uiCard->AddChild(columnLayout);

		auto rectangle = std::make_shared<QmlTag>("Rectangle");
		rectangle->Property("id", "adaptiveCardRectangle");
		rectangle->Property("color", "'transparent'");
		rectangle->Property("Layout.topMargin", "margins");
		rectangle->Property("Layout.bottomMargin", "removeBottomMargin? 0 : margins");
		rectangle->Property("Layout.leftMargin", "margins");
		rectangle->Property("Layout.rightMargin", "margins");
		rectangle->Property("Layout.fillWidth", "true");
		rectangle->Property("Layout.preferredHeight", "40");
		rectangle->Property("Layout.minimumHeight", "1");

		columnLayout->AddChild(rectangle);

		//TODO: Add card vertical content alignment
        auto bodyLayout = std::make_shared<QmlTag>("Column");
        bodyLayout->Property("id", "bodyLayout");
        bodyLayout->Property("width", "parent.width");
        rectangle->Property("Layout.preferredHeight", "bodyLayout.height");
        rectangle->AddChild(bodyLayout);

		ValidateLastBodyElementIsShowCard(card->GetBody(), context);
		
		ValidateShowCardInActions(card->GetActions(), context);
		AddContainerElements(bodyLayout, card->GetBody(), context);
		AddActions(bodyLayout, card->GetActions(), context);
        addSelectAction(uiCard, uiCard->GetId(), card->GetSelectAction(), context, hasBackgroundImage);

		auto showCardsList = context->getShowCardsLoaderIdsList();
		auto removeBottomMarginValue = RemoveBottomMarginValue(showCardsList);
		rectangle->Property("property bool removeBottomMargin", removeBottomMarginValue);

		//Remove Top and Bottom Paddin if bleed for first and last element is true
		rectangle = applyVerticalBleed(bodyLayout, rectangle);

		int tempMargin = 0;

		if (rectangle->HasProperty("Layout.topMargin"))
		{
			tempMargin += margin;
		}

		if (rectangle->HasProperty("Layout.bottomMargin"))
		{
			tempMargin += margin;
		}

		bodyLayout->Property("onImplicitHeightChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight(children," << int(card->GetMinHeight()) - tempMargin << ")}");

		bodyLayout->Property("onImplicitWidthChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight(children," << int(card->GetMinHeight()) - tempMargin << ")}");

		if (card->GetMinHeight() > 0)
		{
			rectangle->Property("Layout.minimumHeight", std::to_string(card->GetMinHeight() - tempMargin));
		}

        //Add submit onclick event
        addSubmitActionButtonClickFunc(context);
        addShowCardLoaderComponents(context);
        addTextRunSelectActions(context);

		// Add height and width calculation function
        uiCard->AddFunctions(AdaptiveCardQmlRenderer::getStretchHeight());
        uiCard->AddFunctions(AdaptiveCardQmlRenderer::getStretchWidth());
        uiCard->AddFunctions(AdaptiveCardQmlRenderer::getMinWidth());
        uiCard->AddFunctions(AdaptiveCardQmlRenderer::getMinWidthActionSet());
		uiCard->AddFunctions(AdaptiveCardQmlRenderer::getMinWidthFactSet());
		return uiCard;
	}

    void AdaptiveCardQmlRenderer::AddContainerElements(std::shared_ptr<QmlTag> uiContainer, const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& elements, std::shared_ptr<AdaptiveRenderContext> context)
    {
		for (const auto& cardElement : elements)
		{
			auto uiElement = context->Render(cardElement);

			if (uiElement != nullptr)
			{
				if (!uiContainer->GetChildren().empty())
				{
					AddSeparator(uiContainer, cardElement, context);
				}

				if (cardElement->GetHeight() == AdaptiveCards::HeightType::Stretch && cardElement->GetElementTypeString() != "Image")
				{
					uiElement->Property("readonly property bool stretch", "true");
				}

				uiContainer->AddChild(uiElement);
			}
		}
    }

    void AdaptiveCardQmlRenderer::AddActions(std::shared_ptr<QmlTag> uiContainer, const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions, std::shared_ptr<AdaptiveRenderContext> context, bool removeBottomMargin)
    {
        if (context->GetConfig()->GetSupportsInteractivity())
        {
            if ((unsigned int)actions.size() == 0)
            {
                return;
            }

            std::shared_ptr<QmlTag> uiButtonStrip;
            auto actionsConfig = context->GetConfig()->GetActions();

            if (actionsConfig.actionsOrientation == AdaptiveCards::ActionsOrientation::Horizontal)
            {
                uiButtonStrip = std::make_shared<QmlTag>("Flow");
                uiButtonStrip->Property("width", "parent.width");
                uiButtonStrip->Property("spacing", std::to_string(actionsConfig.buttonSpacing));

                switch (actionsConfig.actionAlignment)
                {
                case AdaptiveCards::ActionAlignment::Right:
                    uiButtonStrip->Property("layoutDirection", "Qt.RightToLeft");
                    break;
                case AdaptiveCards::ActionAlignment::Center: //TODO: implement for centre alignment
                default:
                    uiButtonStrip->Property("layoutDirection", "Qt.LeftToRight");
                    break;
                }
            }
            else
            {
                //TODO: Implement AdaptiveCards::ActionsOrientation::Vertical
                uiButtonStrip = std::make_shared<QmlTag>("Column");
                uiButtonStrip->Property("width", "parent.width");
                uiButtonStrip->Property("spacing", std::to_string(actionsConfig.buttonSpacing));
            }

            const unsigned int maxActions = std::min<unsigned int>(actionsConfig.maxActions, (unsigned int)actions.size());
            // See if all actions have icons, otherwise force the icon placement to the left
            const auto oldConfigIconPlacement = actionsConfig.iconPlacement;
            bool allActionsHaveIcons = true;
            for (const auto& action : actions)
            {
                if (action->GetIconUrl().empty())
                {
                    allActionsHaveIcons = false;
                    break;
                }
            }

            if (!allActionsHaveIcons)
            {
                actionsConfig.iconPlacement = AdaptiveCards::IconPlacement::LeftOfTitle;
                context->GetConfig()->SetActions(actionsConfig);
            }

            // add separator and button set layout
            AddSeparator(uiContainer, std::make_shared<AdaptiveCards::Container>(), context);
            uiContainer->AddChild(uiButtonStrip);

            for (unsigned int i = 0; i < maxActions; i++)
            {
                // add actions buttons
                auto uiAction = context->Render(actions[i]);
                if (uiAction != nullptr)
                {
                    if (Utils::IsInstanceOfSmart<AdaptiveCards::ShowCardAction>(actions[i]))
                    {
                        // Add to loader source component list
						const std::string loaderId = uiAction->GetId() + "_loader";
                        const std::string componentId = uiAction->GetId() + "_component";
                        const auto showCardAction = std::dynamic_pointer_cast<AdaptiveCards::ShowCardAction>(actions[i]);
                        context->addToShowCardLoaderComponentList(componentId, showCardAction);

                        //Add show card loader to the parent container
                        AddSeparator(uiContainer, std::make_shared<AdaptiveCards::Container>(), context, true, loaderId);

						auto uiLoader = std::make_shared<QmlTag>("Loader");
                        uiLoader->Property("id", loaderId);
						//1px shift to avoid child card displaying over parent card's border
                        uiLoader->Property("x", "-margins + 1");
                        uiLoader->Property("sourceComponent", componentId);
                        uiLoader->Property("visible", "false");
						//2 px reduction in width to avoid child card displaying over parent card's border
						uiLoader->Property("width", Formatter() << uiContainer->GetProperty("id") << ".width + 2*margins - 2");
						uiLoader->Property("readonly property bool removeBottomMargin", removeBottomMargin ? "true" : "false");

						context->addToShowCardsLoaderIdsList(loaderId);
                        uiContainer->AddChild(uiLoader);
                    }

                    uiButtonStrip->AddChild(uiAction);
                }
            }

            // add show card click function
            addShowCardButtonClickFunc(context);

            // Restore the iconPlacement for the context.
            actionsConfig.iconPlacement = oldConfigIconPlacement;
        }
    }

    void AdaptiveCardQmlRenderer::addSelectAction(const std::shared_ptr<QmlTag>& parent, const std::string& rectId, const std::shared_ptr<AdaptiveCards::BaseActionElement>& selectAction, const std::shared_ptr<AdaptiveRenderContext>& context, const bool hasBackgroundImage)
    {
        if (context->GetConfig()->GetSupportsInteractivity() && selectAction != nullptr)
        {
            // SelectAction doesn't allow showCard actions
            if (Utils::IsInstanceOfSmart<AdaptiveCards::ShowCardAction>(selectAction))
            {
                context->AddWarning(AdaptiveWarning(Code::RenderException, "Inline ShowCard not supported for SelectAction"));
                return;
            }

            const auto parentColor = !parent->GetProperty("readonly property string bgColor").empty() ? parent->GetProperty("readonly property string bgColor") : "'transparent'";
            const auto hoverColor = context->GetRGBColor(context->GetConfig()->GetContainerStyles().emphasisPalette.backgroundColor);

            auto mouseArea = std::make_shared<QmlTag>("MouseArea");
            mouseArea->Property("anchors.fill", "parent");
            mouseArea->Property("acceptedButtons", "Qt.LeftButton");
            mouseArea->Property("hoverEnabled", "true");

            std::ostringstream onEntered;
            onEntered << "{" << rectId << ".color = " << hoverColor << ";";
            if (hasBackgroundImage)
            {
                onEntered << rectId << ".opacity = 0.5;";
            }
            onEntered << "}";
            mouseArea->Property("onEntered", onEntered.str());

            std::ostringstream onExited;
            onExited << "{" << rectId << ".color = " << parentColor << ";";
            if (hasBackgroundImage)
            {
                onExited << rectId << ".opacity = 1;";
            }
            onExited << "}";
            mouseArea->Property("onExited", onExited.str());

            std::string onClickedFunction;
            if (selectAction->GetElementTypeString() == "Action.OpenUrl")
            {
                onClickedFunction = getActionOpenUrlClickFunc(std::dynamic_pointer_cast<AdaptiveCards::OpenUrlAction>(selectAction), context);
            }
            else if (selectAction->GetElementTypeString() == "Action.Submit")
            {
                context->addToSubmitActionButtonList(mouseArea, std::dynamic_pointer_cast<AdaptiveCards::SubmitAction>(selectAction));
            }
            else
            {
                onClickedFunction = "";
            }
            mouseArea->Property("onClicked", Formatter() << "{\n" << onClickedFunction << "}");

            parent->AddChild(mouseArea);
        }
    }

    void AdaptiveCardQmlRenderer::addTextRunSelectActions(const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        if (context->GetConfig()->GetSupportsInteractivity())
        {
            for (const auto& textRunElement : context->getTextRunSelectActionList())
            {
                std::ostringstream onLinkActivated;
                for (const auto& action : textRunElement.second)
                {
                    onLinkActivated << "if(link === '" << action.first << "'){\n";

                    if (action.second->GetElementTypeString() == "Action.OpenUrl")
                    {
                        onLinkActivated << getActionOpenUrlClickFunc(std::dynamic_pointer_cast<AdaptiveCards::OpenUrlAction>(action.second), context);
                    }
                    else if (action.second->GetElementTypeString() == "Action.Submit")
                    {
                        onLinkActivated << getActionSubmitClickFunc(std::dynamic_pointer_cast<AdaptiveCards::SubmitAction>(action.second), context);
                    }
                    onLinkActivated << "return;\n}\n";
                }
                textRunElement.first->Property("onLinkActivated", Formatter() << "{\n" << onLinkActivated.str() << "}");
            }
        }
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetComponent(const std::string& componentId, const std::shared_ptr<QmlTag>& uiCard)
    {
        auto uiComponent = std::make_shared<QmlTag>("Component");
        uiComponent->Property("id", componentId);

        const std::string layoutId = Formatter() << componentId << "_component_layout";
        std::string uiCard_string = uiCard->ToString();
        uiCard_string = Utils::Replace(uiCard_string, "\\", "\\\\");
        uiCard_string = Utils::Replace(uiCard_string, "\"", "\\\"");

        auto uiColumn = std::make_shared<QmlTag>("ColumnLayout");
        uiColumn->Property("id", layoutId);
        uiColumn->AddFunctions("property var card");
        uiColumn->Property("property string showCard", uiCard_string, true);
        uiColumn->Property("Component.onCompleted", "reload(showCard)");
        uiColumn->AddFunctions(Formatter() << "function reload(mCard)\n{\n");
        uiColumn->AddFunctions(Formatter() << "if (card)\n{ \ncard.destroy()\n }\n");
        uiColumn->AddFunctions(Formatter() << "card = Qt.createQmlObject(mCard, " << layoutId << ", 'card')\n");
        uiColumn->AddFunctions(Formatter() << "if (card)\n{ \ncard.buttonClicked.connect(adaptiveCard.buttonClicked)\n }\n}");

		uiComponent->AddChild(uiColumn);

		return uiComponent;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::TextBlockRender(std::shared_ptr<AdaptiveCards::TextBlock> textBlock, std::shared_ptr<AdaptiveRenderContext> context)
	{
		//LIMITATION: Elide and maximumLineCount property do not work for textFormat:Text.MarkdownText

		std::string fontFamily = context->GetConfig()->GetFontFamily(textBlock->GetFontType());
		int fontSize = context->GetConfig()->GetFontSize(textBlock->GetFontType(), textBlock->GetTextSize());

		auto uiTextBlock = std::make_shared<QmlTag>("Text");
		std::string textType = textBlock->GetElementTypeString();
		std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(textBlock->GetHorizontalAlignment());

		uiTextBlock->Property("width", "parent.width");

		//Does not work for Markdown text
		uiTextBlock->Property("elide", "Text.ElideRight");

		uiTextBlock->Property("clip", "true");
		uiTextBlock->Property("textFormat", "Text.MarkdownText");

		uiTextBlock->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));

		std::string color = context->GetColor(textBlock->GetTextColor(), textBlock->GetIsSubtle(), false);

		uiTextBlock->Property("color", color);

		uiTextBlock->Property("font.pixelSize", std::to_string(fontSize));

		uiTextBlock->Property("font.weight", Utils::GetWeight(textBlock->GetTextWeight()));

		if (!textBlock->GetId().empty())
		{
            textBlock->SetId(context->ConvertToValidId(textBlock->GetId()));
			uiTextBlock->Property("id", textBlock->GetId());
		}

		if (!textBlock->GetIsVisible())
		{
			uiTextBlock->Property("visible", "false");
		}

		//Does not work for Markdown text
		if (textBlock->GetMaxLines() > 0)
		{
			uiTextBlock->Property("maximumLineCount", std::to_string(textBlock->GetMaxLines()));
		}

		if (textBlock->GetWrap())
		{
			uiTextBlock->Property("wrapMode", "Text.Wrap");
		}

		if (!fontFamily.empty())
		{
            uiTextBlock->Property("font.family", fontFamily, true);
        }

		std::string text = TextUtils::ApplyTextFunctions(textBlock->GetText(), context->GetLang());
		text = Utils::HandleEscapeSequences(text);

		const std::string linkColor = context->GetColor(AdaptiveCards::ForegroundColor::Accent, false, false);

		//CSS Property for underline, striketrhough,etc
		const std::string textDecoration = "none";
		text = Utils::MarkdownUrlToHtml(text, linkColor, textDecoration);
		
		uiTextBlock->Property("text", text, true);

		//MouseArea to Change Cursor on Hovering Links
		auto MouseAreaTag = GetTextBlockMouseArea();
		uiTextBlock->AddChild(MouseAreaTag);

		std::string onLinkActivatedFunction = Formatter() << "{"
			<< "adaptiveCard.buttonClicked(\"\", \"Action.OpenUrl\", link);"
			<< "console.log(link);"
			<< "}";
		uiTextBlock->Property("onLinkActivated", onLinkActivatedFunction);

		return uiTextBlock;

	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::TextInputRender(std::shared_ptr<AdaptiveCards::TextInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto textConfig = context->GetRenderConfig()->getInputTextConfig();
        const std::string origionalElementId = input->GetId();

        std::shared_ptr<QmlTag> uiTextInput;
        std::shared_ptr<QmlTag> scrollViewTag;
        std::shared_ptr<QmlTag> inputWrapper;

        std::string colorFunction = Formatter() << "function colorChange(colorItem,focusItem,isPressed) {\n"
            "if (isPressed) {\n"
            "colorItem.color = " << context->GetHexColor(textConfig.backgroundColorOnPressed) << "\n"
            "}\n"
            "else {\n"
            "colorItem.color = focusItem.activeFocus ? " << context->GetHexColor(textConfig.backgroundColorOnPressed) << " : focusItem.hovered ? " << context->GetHexColor(textConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(textConfig.backgroundColorNormal) << "\n"
            "}\n"
            "}\n";

        input->SetId(context->ConvertToValidId(input->GetId()));

        if (input->GetIsMultiline())
        {
            scrollViewTag = std::make_shared<QmlTag>("ScrollView");
            scrollViewTag->Property("width", "parent.width");
            scrollViewTag->Property("height", Formatter() << input->GetId() << ".visible ? " << textConfig.multiLineTextHeight << " : 0");
            scrollViewTag->Property("ScrollBar.vertical.interactive", "true");

            uiTextInput = std::make_shared<QmlTag>("TextArea");
            uiTextInput->Property("id", input->GetId());
            uiTextInput->Property("wrapMode", "Text.Wrap");
            uiTextInput->Property("selectByMouse", "true");
            uiTextInput->Property("selectedTextColor", "'white'");
            uiTextInput->Property("topPadding", Formatter() << textConfig.multiLineTextTopPadding);
            uiTextInput->Property("bottomPadding", Formatter() << textConfig.multiLineTextBottomPadding);
            uiTextInput->Property("color", context->GetHexColor(textConfig.textColor));
            uiTextInput->Property("placeholderTextColor", context->GetHexColor(textConfig.placeHolderColor));
            uiTextInput->Property("leftPadding", Formatter() << textConfig.textHorizontalPadding);
            uiTextInput->Property("rightPadding", Formatter() << textConfig.textHorizontalPadding);

            if (input->GetMaxLength() > 0)
            {
                uiTextInput->Property("onTextChanged", Formatter() << "remove(" << input->GetMaxLength() << ", length)");
            }

            auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
            backgroundTag->Property("radius", Formatter() << textConfig.borderRadius);
            backgroundTag->Property("id", Formatter() << input->GetId() << "_background");
            backgroundTag->Property("color", context->GetHexColor(textConfig.backgroundColorNormal));
            backgroundTag->Property("border.color", Formatter() << input->GetId() << ".activeFocus? " << context->GetHexColor(textConfig.borderColorOnFocus) << " : " << context->GetHexColor(textConfig.borderColorNormal));
            backgroundTag->Property("border.width", Formatter() << textConfig.borderWidth);
            uiTextInput->Property("background", backgroundTag->ToString());

            uiTextInput->AddFunctions(colorFunction);
            uiTextInput->Property("onPressed", Formatter() << "colorChange(" << backgroundTag->GetId() << "," << input->GetId() << ",true)");
            uiTextInput->Property("onReleased", Formatter() << "colorChange(" << backgroundTag->GetId() << "," << input->GetId() << ",false)");
            uiTextInput->Property("onHoveredChanged", Formatter() << "colorChange(" << backgroundTag->GetId() << "," << input->GetId() << ",false)");
            uiTextInput->Property("onActiveFocusChanged", Formatter() << "colorChange(" << backgroundTag->GetId() << "," << input->GetId() << ",false)");

            scrollViewTag->AddChild(uiTextInput);
        }
        else
        {
            inputWrapper = std::make_shared<QmlTag>("Rectangle");
            inputWrapper->Property("id", Formatter() << input->GetId() << "_wrapper");
            inputWrapper->Property("border.color", Formatter() << input->GetId() << ".activeFocus? " << context->GetHexColor(textConfig.borderColorOnFocus) << " : " << context->GetHexColor(textConfig.borderColorNormal));
            inputWrapper->Property("border.width", Formatter() << textConfig.borderWidth);
            inputWrapper->Property("radius", Formatter() << textConfig.borderRadius);
            inputWrapper->Property("height", Formatter() << textConfig.height);
            inputWrapper->Property("width", "parent.width");
            inputWrapper->Property("color", context->GetHexColor(textConfig.backgroundColorNormal));

            uiTextInput = std::make_shared<QmlTag>("TextField");
            uiTextInput->Property("id", input->GetId());
            uiTextInput->Property("selectByMouse", "true");
            uiTextInput->Property("selectedTextColor", "'white'");
            uiTextInput->Property("color", context->GetHexColor(textConfig.textColor));
            uiTextInput->Property("placeholderTextColor", context->GetHexColor(textConfig.placeHolderColor));

            auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
            backgroundTag->Property("color", "'transparent'");
            uiTextInput->Property("background", backgroundTag->ToString());
            uiTextInput->AddFunctions(colorFunction);
            uiTextInput->Property("onPressed", Formatter() << "colorChange(" << inputWrapper->GetId() << "," << input->GetId() << ",true)");
            uiTextInput->Property("onReleased", Formatter() << "colorChange(" << inputWrapper->GetId() << "," << input->GetId() << ",false)");
            uiTextInput->Property("onHoveredChanged", Formatter() << "colorChange(" << inputWrapper->GetId() << "," << input->GetId() << ",false)");
            uiTextInput->Property("onActiveFocusChanged", Formatter() << "colorChange(" << inputWrapper->GetId() << "," << input->GetId() << ",false)");

            if (input->GetMaxLength() > 0)
            {
                uiTextInput->Property("maximumLength", std::to_string(input->GetMaxLength()));
            }

            auto clearIcon = GetClearIconButton(context);
            clearIcon->Property("id", Formatter() << input->GetId() << "_clear_icon");
            clearIcon->Property("visible", Formatter() << input->GetId() << ".text.length != 0");
            clearIcon->Property("onClicked", Formatter() << "{nextItemInFocusChain().forceActiveFocus();" << input->GetId() << ".clear()}");

            uiTextInput->Property("width", Formatter() << "parent.width - " << clearIcon->GetId() << ".width");

            inputWrapper->AddChild(uiTextInput);
            inputWrapper->AddChild(clearIcon);
        }

        uiTextInput->Property("font.pixelSize", Formatter() << textConfig.pixelSize);

        if (!input->GetValue().empty())
        {
            uiTextInput->Property("text", input->GetValue(), true);
        }

        if (!input->GetPlaceholder().empty())
        {
            uiTextInput->Property("placeholderText", input->GetPlaceholder(), true);
        }

        //TODO: Add stretch property

        if (!input->GetIsVisible())
        {
            uiTextInput->Property("visible", "false");
        }

        context->addToInputElementList(origionalElementId, (uiTextInput->GetId() + ".text"));

        // Add inline action mode
        if (context->GetConfig()->GetSupportsInteractivity() && input->GetInlineAction() != nullptr)
        {
            // ShowCard Inline Action Mode is not supported
            if (input->GetInlineAction()->GetElementType() == AdaptiveCards::ActionType::ShowCard &&
                context->GetConfig()->GetActions().showCard.actionMode == AdaptiveCards::ActionMode::Inline)
            {
                context->AddWarning(AdaptiveWarning(Code::RenderException, "Inline ShowCard not supported for InlineAction"));
            }
            else
            {
                auto uiContainer = std::make_shared<QmlTag>("Row");
                uiContainer->Property("id", Formatter() << input->GetId() << "_row");
                uiContainer->Property("spacing", "5");
                uiContainer->Property("width", "parent.width");
                const auto actionsConfig = context->GetConfig()->GetActions();

                auto buttonElement = context->Render(input->GetInlineAction());
                buttonElement->RemoveProperty("background");
                buttonElement->RemoveProperty("contentItem");

                // Append the icon to the button
                // NOTE: always using icon size since it's difficult
                // to match icon's height with text's height
                auto bgRectangle = std::make_shared<QmlTag>("Rectangle");
                bgRectangle->Property("id", Formatter() << buttonElement->GetId() << "_bg");
                bgRectangle->Property("anchors.fill", "parent");
                bgRectangle->Property("color", Formatter() << buttonElement->GetId() << ".pressed ? " << context->GetHexColor(textConfig.backgroundColorOnPressed) << " : " << buttonElement->GetId() << ".hovered ? " << context->GetHexColor(textConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(textConfig.backgroundColorNormal));
                bgRectangle->Property("border.color", context->GetHexColor(textConfig.borderColorOnFocus));
                bgRectangle->Property("border.width", Formatter() << buttonElement->GetId() << ".activeFocus? " << textConfig.borderWidth << ": 0");
                buttonElement->Property("background", bgRectangle->ToString());

                if (!input->GetInlineAction()->GetIconUrl().empty())
                {
                    buttonElement->Property("height", std::to_string(actionsConfig.iconSize));
                    buttonElement->Property("width", std::to_string(actionsConfig.iconSize));

                    auto iconItem = std::make_shared<QmlTag>("Item");
                    iconItem->Property("anchors.fill", "parent");
                    auto iconImage = std::make_shared<QmlTag>("Image");
                    iconImage->Property("id", Formatter() << buttonElement->GetId() << "_img");
                    iconImage->Property("height", std::to_string(actionsConfig.iconSize));
                    iconImage->Property("width", std::to_string(actionsConfig.iconSize));
                    iconImage->Property("fillMode", "Image.PreserveAspectFit");
                    iconImage->Property("cache", "false");
                    iconImage->Property("source", Formatter() << buttonElement->GetId() + ".imgSource");
                    iconItem->AddChild(iconImage);
                    buttonElement->Property("contentItem", iconItem->ToString());
                }
                else
                {
                    buttonElement->Property("text", input->GetInlineAction()->GetTitle(), true);
                }

                if (input->GetIsMultiline())
                {
                    buttonElement->Property("anchors.bottom", "parent.bottom");
                    scrollViewTag->Property("width", Formatter() << "parent.width - " << buttonElement->GetId() << ".width - " << uiContainer->GetId() << ".spacing");
                    uiContainer->AddChild(scrollViewTag);
                }
                else
                {
                    inputWrapper->Property("width", Formatter() << "parent.width - " << buttonElement->GetId() << ".width - " << uiContainer->GetId() << ".spacing");
                    uiContainer->AddChild(inputWrapper);
                }
                uiContainer->AddChild(buttonElement);
                return uiContainer;
            }
        }

        if (input->GetIsMultiline())
        {
            return scrollViewTag;
        }

        return inputWrapper;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::NumberInputRender(std::shared_ptr<AdaptiveCards::NumberInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto numberConfig = context->GetRenderConfig()->getInputNumberConfig();

        const std::string origionalElementId = input->GetId();
        input->SetId(context->ConvertToValidId(input->GetId()));
        const auto inputId = input->GetId();

        auto numberInputRow = std::make_shared<QmlTag>("Row");
        numberInputRow->Property("id", Formatter() << inputId << "_input_row");
        numberInputRow->Property("width", "parent.width");
        numberInputRow->Property("height", Formatter() << numberConfig.height);

        auto numberInputRectangle = std::make_shared<QmlTag>("Rectangle");
        numberInputRectangle->Property("id", Formatter() << inputId << "_input");

        numberInputRectangle->Property("border.width", Formatter() << numberConfig.borderWidth);
        numberInputRectangle->Property("border.color", Formatter() << inputId << ".activeFocus ? " << context->GetHexColor(numberConfig.borderColorOnFocus) << " : " << context->GetHexColor(numberConfig.borderColorNormal));
        numberInputRectangle->Property("radius", Formatter() << numberConfig.borderRadius);
        numberInputRectangle->Property("height", "parent.height");
        numberInputRectangle->Property("color", Formatter() << inputId << ".pressed ? " << context->GetHexColor(numberConfig.backgroundColorOnPressed) << " : " << inputId << ".hovered ? " << context->GetHexColor(numberConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(numberConfig.backgroundColorNormal));

        auto uiNumberInput = std::make_shared<QmlTag>("SpinBox");
        uiNumberInput->Property("id", inputId);
        uiNumberInput->Property("width", "parent.width");
        uiNumberInput->Property("padding", "0");
        uiNumberInput->Property("stepSize", "1");
        uiNumberInput->Property("editable", "true");

        auto doubleValidatorTag = std::make_shared<QmlTag>("DoubleValidator");

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        backgroundTag->Property("color", "'transparent'");

        auto contentItemTag = std::make_shared<QmlTag>("TextField");
        contentItemTag->Property("id", inputId + "_contentItem");
        contentItemTag->Property("font.pixelSize", Formatter() << numberConfig.pixelSize);
        contentItemTag->Property("anchors.left", "parent.left");
        contentItemTag->Property("anchors.right", "parent.right");
        contentItemTag->Property("selectByMouse", "true");
        contentItemTag->Property("selectedTextColor", "'white'");
        contentItemTag->Property("readOnly", Formatter() << "!" << inputId << ".editable");
        contentItemTag->Property("validator", Formatter() << inputId << ".validator");
        contentItemTag->Property("inputMethodHints", "Qt.ImhFormattedNumbersOnly");
        contentItemTag->Property("text", Formatter() << inputId << ".value");
        contentItemTag->Property("onPressed", Formatter() << numberInputRectangle->GetId() << ".colorChange(true)");
        contentItemTag->Property("onReleased", Formatter() << numberInputRectangle->GetId() << ".colorChange(false)");
        contentItemTag->Property("onHoveredChanged", Formatter() << numberInputRectangle->GetId() << ".colorChange(false)");
        contentItemTag->Property("onActiveFocusChanged", Formatter() << numberInputRectangle->GetId() << ".colorChange(false)");
        {
            contentItemTag->Property("placeholderText", input->GetPlaceholder(), true);
        }

        auto textBackgroundTag = std::make_shared<QmlTag>("Rectangle");
        textBackgroundTag->Property("color", "'transparent'");

        contentItemTag->Property("background", textBackgroundTag->ToString());
        contentItemTag->Property("onEditingFinished", Formatter() << "{ if(text < " << inputId << ".from || text > " << inputId << ".to){\nremove(0,length)\nif(" << inputId << ".hasDefaultValue)\ninsert(0, " << inputId << ".defaultValue)\nelse\ninsert(0, " << inputId << ".from)\n}\n}");
        contentItemTag->Property("color", context->GetHexColor(numberConfig.textColor));
        contentItemTag->Property("placeholderTextColor", context->GetHexColor(numberConfig.placeHolderColor));

        //Dummy indicator element to remove the default indicators of SpinBox
        auto upDummyTag = getDummyElementforNumberInput(true);

        //Dummy indicator element to remove the default indicators of SpinBox
        auto downDummyTag = getDummyElementforNumberInput(false);

        auto upDownIcon = GetIconTag(context);
        upDownIcon->RemoveProperty("anchors.top");
        upDownIcon->RemoveProperty("anchors.bottom");
        upDownIcon->RemoveProperty("anchors.margins");
        upDownIcon->Property("id", Formatter() << inputId << "_up_down_icon");
        upDownIcon->Property("width", "parent.width");
        upDownIcon->Property("height", "parent.height");
        upDownIcon->Property("icon.width", Formatter() << numberConfig.upDownIconSize);
        upDownIcon->Property("icon.height", Formatter() << numberConfig.upDownIconSize);
        upDownIcon->Property("icon.color", context->GetHexColor(numberConfig.upDownIconColor));
        upDownIcon->Property("icon.source", RendererQml::vector_up_down, true);
        upDownIcon->Property("background", textBackgroundTag->ToString());

        auto upIndicatorTag = std::make_shared<QmlTag>("MouseArea");
        upIndicatorTag->Property("id", Formatter() << inputId << "_up_indicator_area");
        upIndicatorTag->Property("width", "parent.width");
        upIndicatorTag->Property("height", "parent.height/2");
        upIndicatorTag->Property("anchors.top", "parent.top");

        auto downIndicatorTag = std::make_shared<QmlTag>("MouseArea");
        downIndicatorTag->Property("id", Formatter() << inputId << "_down_indicator_area");
        downIndicatorTag->Property("width", "parent.width");
        downIndicatorTag->Property("height", "parent.height/2");
        downIndicatorTag->Property("anchors.top", Formatter() << upIndicatorTag->GetId() << ".bottom");

        auto clearIcon = GetClearIconButton(context);
        clearIcon->Property("id", Formatter() << inputId << "_clear_icon");
        clearIcon->Property("visible", Formatter() << contentItemTag->GetId() << ".length !== 0");
        clearIcon->Property("onClicked", Formatter() << "{nextItemInFocusChain().forceActiveFocus();" << inputId << ".value = " << inputId << ".from;" << contentItemTag->GetId() << ".clear();}");

        if (input->GetValue() != std::nullopt)
        {
            uiNumberInput->Property("readonly property bool hasDefaultValue", "true");
            uiNumberInput->Property("readonly property int defaultValue", Formatter() << input->GetValue());
        }
        else if (input->GetMin() == std::nullopt)
        {
            input->SetValue(0);
            uiNumberInput->Property("readonly property bool hasDefaultValue", "true");
            uiNumberInput->Property("readonly property int defaultValue", std::to_string(0));
        }
        else
        {
            uiNumberInput->Property("readonly property bool hasDefaultValue", "false");
        }

        if (input->GetMin() == std::nullopt)
        {
            input->SetMin(INT_MIN);
        }
        if (input->GetMax() == std::nullopt)
        {
            input->SetMax(INT_MAX);
        }

        if ((input->GetMin() == input->GetMax() && input->GetMin() == 0) || input->GetMin() > input->GetMax())
        {
            input->SetMin(INT_MIN);
            input->SetMax(INT_MAX);
        }
        if (input->GetValue() < input->GetMin())
        {
            input->SetValue(input->GetMin());
            uiNumberInput->Property("readonly property int defaultValue", Formatter() << input->GetMin());
        }
        if (input->GetValue() > input->GetMax())
        {
            input->SetValue(input->GetMax());
            uiNumberInput->Property("readonly property int defaultValue", Formatter() << input->GetMax());
        }

        uiNumberInput->Property("from", Formatter() << input->GetMin());
        uiNumberInput->Property("to", Formatter() << input->GetMax());
        uiNumberInput->Property("value", Formatter() << input->GetValue());

        //TODO: Add stretch property

        if (!input->GetIsVisible())
        {
            uiNumberInput->Property("visible", "false");
        }

        auto uiSplitterRactangle = std::make_shared<QmlTag>("Rectangle");
        uiSplitterRactangle->Property("id", Formatter() << uiNumberInput->GetId() << "_icon_set");
        uiSplitterRactangle->Property("width", Formatter() << numberConfig.upDownButtonWidth);
        uiSplitterRactangle->Property("radius", Formatter() << numberConfig.borderRadius);
        uiSplitterRactangle->Property("height", "parent.height");
        uiSplitterRactangle->Property("border.color", Formatter() << "activeFocus ? " << context->GetHexColor(numberConfig.borderColorOnFocus) << " : " << context->GetHexColor(numberConfig.borderColorNormal));
        uiSplitterRactangle->Property("activeFocusOnTab", "true");
        uiSplitterRactangle->Property("color", Formatter() << "(" << upDownIcon->GetId() << ".pressed || activeFocus) ? " << context->GetHexColor(numberConfig.backgroundColorOnPressed) << " : " << upDownIcon->GetId() << ".hovered ? " << context->GetHexColor(numberConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(numberConfig.backgroundColorNormal));
        uiSplitterRactangle->Property("Keys.onPressed", Formatter() << "{\n"
            "if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)\n"
            "{" << uiNumberInput->GetId() << ".changeValue(event.key);event.accepted = true;}}\n"
        );

        uiNumberInput->Property("contentItem", contentItemTag->ToString());
        uiNumberInput->Property("background", backgroundTag->ToString());
        uiNumberInput->Property("up.indicator", upDummyTag->ToString());
        uiNumberInput->Property("down.indicator", downDummyTag->ToString());
        uiNumberInput->Property("validator", doubleValidatorTag->ToString());
        uiNumberInput->Property("valueFromText", "function(text, locale){\nreturn Number(text)\n}");
        uiNumberInput->AddFunctions(Formatter() << "function changeValue(keyPressed) {"
            "if ((keyPressed === Qt.Key_Up || keyPressed === Qt.Key_Down) && " << contentItemTag->GetId() << ".text.length === 0)\n"
            "{value = (from < 0) ? 0 : from;" << contentItemTag->GetId() << ".text = value;}\n"
            "else if (keyPressed === Qt.Key_Up)\n"
            "{" << inputId << ".increase();" << contentItemTag->GetId() << ".text = value;}\n"
            "else if (keyPressed === Qt.Key_Down)\n"
            "{" << inputId << ".decrease();" << contentItemTag->GetId() << ".text = value;}}\n");
        uiNumberInput->Property("Keys.onPressed", Formatter() << "{\n"
            "if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)\n"
            "{ " << inputId << ".changeValue(event.key);event.accepted = true}\n"
            "}\n");

        numberInputRectangle->Property("width", Formatter() << "parent.width - " << uiSplitterRactangle->GetId() << ".width");
        numberInputRectangle->AddFunctions(Formatter() << "function colorChange(isPressed){\n"
            "if (isPressed) color = " << context->GetHexColor(numberConfig.backgroundColorOnPressed) << ";\n"
            "else color = " << contentItemTag->GetId() << ".activeFocus ? " << context->GetHexColor(numberConfig.backgroundColorOnPressed) << " : " << contentItemTag->GetId() << ".hovered ? " << context->GetHexColor(numberConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(numberConfig.backgroundColorNormal) << "}"
        );

        numberInputRectangle->AddChild(uiNumberInput);
        numberInputRectangle->AddChild(clearIcon);
        numberInputRow->AddChild(numberInputRectangle);
        numberInputRow->AddChild(uiSplitterRactangle);

        upIndicatorTag->Property("onReleased", Formatter() << "{ " << inputId << ".changeValue(Qt.Key_Up); " << uiSplitterRactangle->GetId() << ".forceActiveFocus(); }");
        downIndicatorTag->Property("onReleased", Formatter() << "{ " << inputId << ".changeValue(Qt.Key_Down); " << uiSplitterRactangle->GetId() << ".forceActiveFocus(); }");
        uiSplitterRactangle->AddChild(upDownIcon);
        uiSplitterRactangle->AddChild(upIndicatorTag);
        uiSplitterRactangle->AddChild(downIndicatorTag);

        context->addToInputElementList(origionalElementId, (inputId + ".value"));

        return numberInputRow;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::RichTextBlockRender(std::shared_ptr<AdaptiveCards::RichTextBlock> richTextBlock, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto uiTextBlock = std::make_shared<QmlTag>("Text");
		std::string textType = richTextBlock->GetElementTypeString();
		std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(richTextBlock->GetHorizontalAlignment());

		if (!richTextBlock->GetId().empty())
		{
			richTextBlock->SetId(context->ConvertToValidId(richTextBlock->GetId()));
			uiTextBlock->Property("id", richTextBlock->GetId());
		}

		uiTextBlock->Property("textFormat", "Text.RichText");
		uiTextBlock->Property("wrapMode", "Text.Wrap");
		uiTextBlock->Property("width", "parent.width");

		uiTextBlock->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));
		std::string textrun_all = "";

		if (!richTextBlock->GetIsVisible())
		{
			uiTextBlock->Property("visible", "false");
		}

        std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>> selectActionList;

		for (const auto& inlineRun : richTextBlock->GetInlines())
		{
			if (Utils::IsInstanceOfSmart<AdaptiveCards::TextRun>(inlineRun))
			{
                std::string selectActionId = "";
				auto textRun = std::dynamic_pointer_cast<AdaptiveCards::TextRun>(inlineRun);

                if (textRun->GetSelectAction() != nullptr)
                {
                    selectActionId = Formatter() << "selectaction_" << context->getSelectActionCounter();
                    selectActionList[selectActionId] = textRun->GetSelectAction();
                }

				textrun_all.append(TextRunRender(textRun, context, selectActionId));
			}
		}
		uiTextBlock->Property("text", textrun_all, true);

		//MouseArea to Change Cursor on Hovering Links
		auto MouseAreaTag = GetTextBlockMouseArea();
		uiTextBlock->AddChild(MouseAreaTag);

        context->addToTextRunSelectActionList(uiTextBlock, selectActionList);

		return uiTextBlock;
	}

	std::string AdaptiveCardQmlRenderer::TextRunRender(const std::shared_ptr<AdaptiveCards::TextRun>& textRun, const std::shared_ptr<AdaptiveRenderContext>& context, const std::string& selectaction)
	{
		const std::string fontFamily = context->GetConfig()->GetFontFamily(textRun->GetFontType());
		const int fontSize = context->GetConfig()->GetFontSize(textRun->GetFontType(), textRun->GetTextSize());
		const int weight = context->GetConfig()->GetFontWeight(textRun->GetFontType(), textRun->GetTextWeight());

		std::string uiTextRun = "<span style='";
		std::string textType = textRun->GetInlineTypeString();

		uiTextRun.append(Formatter() << "font-family:" << std::string("\\\"") << fontFamily << std::string("\\\"") << ";");

		std::string color = context->GetColor(textRun->GetTextColor(), textRun->GetIsSubtle(), false, false);
		uiTextRun.append(Formatter() << "color:" << color << ";");

		uiTextRun.append(Formatter() << "font-size:" << std::to_string(fontSize) << "px" << ";");

		uiTextRun.append(Formatter() << "font-weight:" << std::to_string(weight) << ";");

		if (textRun->GetHighlight())
		{
			uiTextRun.append(Formatter() << "background-color:" << context->GetColor(textRun->GetTextColor(), textRun->GetIsSubtle(), true, false) << ";");
		}

		if (textRun->GetItalic())
		{
			uiTextRun.append(Formatter() << "font-style:" << std::string("italic") << ";");
		}

		if (textRun->GetStrikethrough())
		{
			uiTextRun.append(Formatter() << "text-decoration:" << std::string("line-through") << ";");
		}

		uiTextRun.append("'>");

        if (textRun->GetSelectAction() != nullptr)
        {
			const std::string linkColor = context->GetColor(AdaptiveCards::ForegroundColor::Accent, false, false);
			//CSS Property for underline, striketrhough,etc
			std::string textDecoration = "none";
			const std::string styleString = Formatter() << "style=\\\"color:" << linkColor << ";" << "text-decoration:" << textDecoration << ";\\\"";

            uiTextRun.append(Formatter() << "<a href='" << selectaction << "'" << styleString << " >");
            std::string text = TextUtils::ApplyTextFunctions(textRun->GetText(), context->GetLang());
            text = Utils::HandleEscapeSequences(text);
            uiTextRun.append(text);
            uiTextRun.append("</a>");
        }
        else
        {
            std::string text = TextUtils::ApplyTextFunctions(textRun->GetText(), context->GetLang());
            text = Utils::HandleEscapeSequences(text);
            uiTextRun.append(text);
        }
		uiTextRun.append("</span>");

		return uiTextRun;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ToggleInputRender(std::shared_ptr<AdaptiveCards::ToggleInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto toggleButtonConfig = context->GetRenderConfig()->getToggleButtonConfig();
        const std::string origionalElementId = input->GetId();
        input->SetId(context->ConvertToValidId(input->GetId()));

        const auto valueOn = !input->GetValueOn().empty() ? input->GetValueOn() : "true";
        const auto valueOff = !input->GetValueOff().empty() ? input->GetValueOff() : "false";
        const bool isChecked = input->GetValue().compare(valueOn) == 0 ? true : false;

        //TODO: Add Height
        const auto checkbox = GetCheckBox(RendererQml::Checkbox(input->GetId(),
            CheckBoxType::Toggle,
            input->GetTitle(),
            input->GetValue(),
            valueOn,
            valueOff,
            input->GetWrap(),
            input->GetIsVisible(),
            isChecked), context);


        checkbox->AddFunctions(Formatter() << "function colorChange(item,isPressed){\n"
            "if (isPressed) item.indicator.color = item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnCheckedAndPressed) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUncheckedAndPressed) << ";\n"
            "else  item.indicator.color = (item.hovered || item.activeFocus) ? (item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnCheckedAndHovered) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUncheckedAndHovered) << ") : (item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnChecked) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUnchecked) << ")\n"
            "if (isPressed) item.indicator.border.color = item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnCheckedAndPressed) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUncheckedAndPressed) << ";\n"
            "else  item.indicator.border.color = (item.hovered || item.activeFocus) ? (item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnCheckedAndHovered) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUncheckedAndHovered) << ") : (item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnChecked) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUnchecked) << ")\n"
            "}\n"
        );
        checkbox->Property("onPressed", Formatter() << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", true)");
        checkbox->Property("onReleased", Formatter() << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", false)");
        checkbox->Property("onHoveredChanged", Formatter() << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", false)");
        checkbox->Property("onActiveFocusChanged", Formatter() << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", false)");
        checkbox->Property("onCheckedChanged", Formatter() << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", false)");

        checkbox->Property("Component.onCompleted", Formatter() << "{\n"
            << checkbox->GetId() << ".colorChange(" << checkbox->GetId() << ", false);}\n"
        );

        context->addToInputElementList(origionalElementId, (checkbox->GetId() + ".value"));
        return checkbox;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ChoiceSetRender(std::shared_ptr<AdaptiveCards::ChoiceSetInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
        const std::string origionalElementId = input->GetId();
        input->SetId(context->ConvertToValidId(input->GetId()));

		int ButtonNumber = 0;
		RendererQml::Checkboxes choices;
		const std::string id = input->GetId();
		enum CheckBoxType type = !input->GetIsMultiSelect() && input->GetChoiceSetStyle() == AdaptiveCards::ChoiceSetStyle::Compact ? ComboBox : input->GetIsMultiSelect() ? CheckBox : RadioButton;
		const bool isWrap = input->GetWrap();
		const bool isVisible = input->GetIsVisible();
		bool isChecked;

        std::shared_ptr<QmlTag> uiChoiceSet;
        const std::vector<std::string> parsedValues = Utils::splitString(input->GetValue(), ',');

		for (const auto& choice : input->GetChoices())
		{
			isChecked = (std::find(parsedValues.begin(), parsedValues.end(), choice->GetValue()) != parsedValues.end() && (input->GetIsMultiSelect() || parsedValues.size() == 1)) ? true : false;
			choices.emplace_back(RendererQml::Checkbox(GenerateChoiceSetButtonId(id, type, ButtonNumber++),
				type,
				choice->GetTitle(),
				choice->GetValue(),
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

		if (type == CheckBoxType::ComboBox)
		{
            uiChoiceSet = GetComboBox(choiceSet,context);
            context->addToInputElementList(origionalElementId, (uiChoiceSet->GetId() + ".currentValue"));
		}
		else
		{
            uiChoiceSet = GetButtonGroup(choiceSet, context);
            context->addToInputElementList(origionalElementId, (uiChoiceSet->GetId() + ".getSelectedValues()"));
		}

		return uiChoiceSet;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetComboBox(ChoiceSet choiceset, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto choiceSetConfig = context->GetRenderConfig()->getInputChoiceSetDropDownConfig();

        auto uiComboBox = std::make_shared<QmlTag>("ComboBox");
        const auto fontFamily = context->GetConfig()->GetFontFamily(AdaptiveCards::FontType::Default);

        uiComboBox->Property("id", choiceset.id);
        uiComboBox->Property("textRole", "'text'");
        uiComboBox->Property("valueRole", "'value'");
        uiComboBox->Property("width", "parent.width");
        uiComboBox->Property("height", Formatter() << choiceSetConfig.height);
        uiComboBox->Property("Keys.onReturnPressed", Formatter() << choiceset.id << ".popup.open()");
        uiComboBox->Property("onAccepted", Formatter() << choiceset.id << ".popup.close()");
        uiComboBox->AddFunctions(Formatter() << "function colorChange(isPressed){\n"
            "if (isPressed) background.color = " << context->GetHexColor(choiceSetConfig.backgroundColorOnPressed) << ";\n"
            "else background.color = (activeFocus || popup.visible) ? " << context->GetHexColor(choiceSetConfig.backgroundColorOnPressed) << " : hovered ? " << context->GetHexColor(choiceSetConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(choiceSetConfig.backgroundColorNormal) << "}\n"
        );
        uiComboBox->Property("onPressedChanged", Formatter() << "{\n"
            "if (pressed) colorChange(true);\n"
            "else colorChange(false);}\n"
        );
        uiComboBox->Property("onActiveFocusChanged", "colorChange(false)");
        uiComboBox->Property("onHoveredChanged", "colorChange(false)");

        const std::string iconId = choiceset.id + "_icon";
        auto iconTag = GetIconTag(context);
        iconTag->RemoveProperty("anchors.margins");
        iconTag->Property("id", iconId);
        iconTag->Property("horizontalPadding", "0");
        iconTag->Property("verticalPadding", "0");
        iconTag->Property("icon.source", Formatter() << choiceset.id << ".popup.visible ? " << "\"" << RendererQml::vector_up << "\"" << ":" << "\"" << RendererQml::vector_down << "\"");
        iconTag->Property("enabled", "false");
        iconTag->Property("width", "35");
        iconTag->Property("horizontalPadding", Formatter() << choiceSetConfig.arrowIconHorizontalPadding);
        iconTag->Property("verticalPadding", Formatter() << choiceSetConfig.arrowIconVerticalPadding);
        iconTag->Property("icon.color", context->GetHexColor(choiceSetConfig.arrowIconColor));
        iconTag->Property("icon.height", Formatter() << choiceSetConfig.arrowIconHeight);
        iconTag->Property("icon.width", Formatter() << choiceSetConfig.arrowIconWidth);

        auto iconBackground = std::make_shared<QmlTag>("Rectangle");
        iconBackground->Property("color", "'transparent'");
        iconBackground->Property("width", "parent.width");
        iconBackground->Property("height", "parent.height");

        iconTag->Property("background", iconBackground->ToString());

        uiComboBox->Property("indicator", iconTag->ToString());
        uiComboBox->Property("model", GetModel(choiceset.choices));

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        backgroundTag->Property("radius", Formatter() << choiceSetConfig.borderRadius);
        //TODO: These color styling should come from css
        backgroundTag->Property("color", context->GetHexColor(choiceSetConfig.backgroundColorNormal));
        backgroundTag->Property("border.color", Formatter() << "(" << choiceset.id << ".activeFocus || " << choiceset.id << ".popup.visible) ? " << context->GetHexColor(choiceSetConfig.borderColorOnFocus) << " : " << context->GetHexColor(choiceSetConfig.borderColorNormal));
        backgroundTag->Property("border.width", Formatter() << choiceSetConfig.borderWidth);
        uiComboBox->Property("background", backgroundTag->ToString());

        if (!choiceset.placeholder.empty())
        {
            uiComboBox->Property("currentIndex", "-1");
            uiComboBox->Property("displayText", "currentIndex === -1 ? '" + choiceset.placeholder + "' : currentText");
        }
        else if (choiceset.values.size() == 1)
        {
            const std::string target = choiceset.values[0];
            auto index = std::find_if(choiceset.choices.begin(), choiceset.choices.end(), [target](const Checkbox& options) {
                return options.value == target;
                }) - choiceset.choices.begin();
                //Assign index as 0 in case target does not exist
                index = (index > (signed int)(choiceset.choices.size() - 1) ? 0 : index);
                uiComboBox->Property("currentIndex", std::to_string(index));
                uiComboBox->Property("displayText", "currentText");
        }

        auto itemDelegateId = choiceset.id + "_itemDelegate";
        auto uiItemDelegate = std::make_shared<QmlTag>("ItemDelegate");
        uiItemDelegate->Property("id", itemDelegateId);
        uiItemDelegate->Property("width", "parent.width");
        uiItemDelegate->Property("height", Formatter() << choiceSetConfig.dropDownElementHeight);
        uiItemDelegate->Property("verticalPadding", Formatter() << choiceSetConfig.dropDownElementVerticalPadding);
        uiItemDelegate->Property("horizontalPadding", Formatter() << choiceSetConfig.dropDownElementHorizontalPadding);
        uiItemDelegate->Property("highlighted", "ListView.isCurrentItem");

        auto backgroundTagDelegate = std::make_shared<QmlTag>("Rectangle");
        //TODO: These color styling should come from css
        backgroundTagDelegate->Property("color", Formatter() << itemDelegateId << ".pressed ? " << context->GetHexColor(choiceSetConfig.dropDownElementColorPressed) << " : " << itemDelegateId << ".highlighted? " << context->GetHexColor(choiceSetConfig.dropDownElementColorHovered) << " : " << context->GetHexColor(choiceSetConfig.dropDownElementColorNormal));
        backgroundTagDelegate->Property("radius", Formatter() << choiceSetConfig.dropDownElementRadius);
        uiItemDelegate->Property("background", backgroundTagDelegate->ToString());

        auto uiItemDelegate_Text = std::make_shared<QmlTag>("Text");
        uiItemDelegate_Text->Property("text", "modelData.text");
        uiItemDelegate_Text->Property("font.family", fontFamily, true);
        uiItemDelegate_Text->Property("font.pixelSize", Formatter() << choiceSetConfig.pixelSize);
        uiItemDelegate_Text->Property("textFormat", "Text.RichText");
        uiItemDelegate_Text->Property("color", context->GetHexColor(choiceSetConfig.textColor));

        if (choiceset.choices[0].isWrap)
        {
            uiItemDelegate_Text->Property("wrapMode", "Text.Wrap");
        }
        else
        {
            uiItemDelegate_Text->Property("elide", "Text.ElideRight");
        }

        auto uiContentItem_Text = std::make_shared<QmlTag>("Text");
        uiContentItem_Text->Property("text", "parent.displayText");
        uiItemDelegate_Text->Property("font.family", fontFamily, true);
        uiContentItem_Text->Property("font.pixelSize", Formatter() << choiceSetConfig.pixelSize);
        uiContentItem_Text->Property("verticalAlignment", "Text.AlignVCenter");
        uiContentItem_Text->Property("padding", Formatter() << choiceSetConfig.textHorizontalPadding);
        uiContentItem_Text->Property("leftPadding", Formatter() << choiceSetConfig.textHorizontalPadding);
        uiContentItem_Text->Property("elide", "Text.ElideRight");
        uiContentItem_Text->Property("color", context->GetHexColor(choiceSetConfig.textColor));

        uiComboBox->Property("contentItem", uiContentItem_Text->ToString());

        uiItemDelegate->Property("contentItem", uiItemDelegate_Text->ToString());

        uiComboBox->Property("delegate", uiItemDelegate->ToString());

        auto contentListViewId = choiceset.id + "_listView";
        auto contentListViewTag = std::make_shared<QmlTag>("ListView");
        contentListViewTag->Property("id", contentListViewId);
        contentListViewTag->Property("clip", "true");
        contentListViewTag->Property("model", Formatter() << choiceset.id << ".delegateModel");
        contentListViewTag->Property("currentIndex", Formatter() << choiceset.id << ".highlightedIndex");
        contentListViewTag->Property("onCurrentIndexChanged", Formatter() << "{if(currentIndex !== -1){" << choiceset.id << ".currentIndex = currentIndex}}");
        contentListViewTag->Property("Keys.onReturnPressed", Formatter() << choiceset.id << ".accepted()");

        auto scrollBarTag = std::make_shared<QmlTag>("ScrollBar");
        scrollBarTag->Property("width", "10");
        scrollBarTag->Property("policy", Formatter() << contentListViewId << ".contentHeight > " << choiceSetConfig.dropDownHeight << "?" << "ScrollBar.AlwaysOn : ScrollBar.AsNeeded");

        contentListViewTag->Property("ScrollBar.vertical", scrollBarTag->ToString());

        auto popupBackgroundTag = std::make_shared<QmlTag>("Rectangle");
        popupBackgroundTag->Property("anchors.fill", "parent");
        popupBackgroundTag->Property("color", context->GetHexColor(choiceSetConfig.dropDownBackgroundColor));
        popupBackgroundTag->Property("border.color", context->GetHexColor(choiceSetConfig.dropDownBorderColor));
        popupBackgroundTag->Property("radius", Formatter() << choiceSetConfig.dropDownRadius);

        auto popupTag = std::make_shared<QmlTag>("Popup");
        popupTag->Property("y", Formatter() << choiceset.id << ".height + 5");
        popupTag->Property("width", Formatter() << choiceset.id << ".width");
        popupTag->Property("padding", Formatter() << choiceSetConfig.dropDownPadding);
        popupTag->Property("height", Formatter() << contentListViewId << ".contentHeight + (2 * " << choiceSetConfig.dropDownPadding << ")" << " > " << choiceSetConfig.dropDownHeight << " ? " << choiceSetConfig.dropDownHeight << " :" << contentListViewId << ".contentHeight + ( 2 * " << choiceSetConfig.dropDownPadding << ")"); // Get from config
        popupTag->Property("onOpened", Formatter() << contentListViewId << ".forceActiveFocus()");
        popupTag->Property("onClosed", Formatter() << uiComboBox->GetId() << ".forceActiveFocus()");

        popupTag->Property("background", popupBackgroundTag->ToString());
        popupTag->Property("contentItem", contentListViewTag->ToString());

        uiComboBox->Property("popup", popupTag->ToString());

        return uiComboBox;
	}

	std::string AdaptiveCardQmlRenderer::GetModel(std::vector<Checkbox>& Choices)
	{
		std::ostringstream model;
		std::string choice_Text;
		std::string choice_Value;

		model << "[";
		for (const auto& choice : Choices)
		{
			choice_Text = choice.text;
			choice_Value = choice.value;
			model << "{ value: '" << Utils::HandleEscapeSequences(choice_Value) << "', text: '" << Utils::HandleEscapeSequences(choice_Text) << "'},\n";
		}
		model << "]";
		return model.str();
	}

	std::string AdaptiveCardQmlRenderer::GenerateChoiceSetButtonId(const std::string& parentId, enum CheckBoxType ButtonType, const int& ButtonNumber)
	{

		return parentId + "_" + std::to_string(ButtonType) + "_" + std::to_string(ButtonNumber);
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetButtonGroup(ChoiceSet choiceset, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto toggleButtonConfig = context->GetRenderConfig()->getToggleButtonConfig();
        auto uiColumn = std::make_shared<QmlTag>("Column");
        uiColumn->Property("id", choiceset.id);

        auto uiButtonGroup = std::make_shared<QmlTag>("ButtonGroup");
        uiButtonGroup->Property("id", choiceset.id + "_btngrp");

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
            auto button = GetCheckBox(choice, context);
            button->Property("onPressed", Formatter() << choiceset.id << ".colorChange(" << button->GetId() << ", true)");
            button->Property("onReleased", Formatter() << choiceset.id << ".colorChange(" << button->GetId() << ", false)");
            button->Property("onHoveredChanged", Formatter() << choiceset.id << ".colorChange(" << button->GetId() << ", false)");
            button->Property("onActiveFocusChanged", Formatter() << choiceset.id << ".colorChange(" << button->GetId() << ", false)");
            button->Property("onCheckedChanged", Formatter() << choiceset.id << ".colorChange(" << button->GetId() << ", false)");
            button->Property("Component.onCompleted", Formatter() << "{\n"
                << choiceset.id << ".colorChange(" << button->GetId() << ", false);}\n"
            );
            uiInnerColumn->AddChild(button);
        }

        uiColumn->AddFunctions(Formatter() << "function colorChange(item,isPressed){\n"
            "if (isPressed) item.indicator.color = item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnCheckedAndPressed) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUncheckedAndPressed) << ";\n"
            "else  item.indicator.color = (item.hovered || item.activeFocus) ? (item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnCheckedAndHovered) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUncheckedAndHovered) << ") : (item.checked ? " << context->GetHexColor(toggleButtonConfig.colorOnChecked) << " : " << context->GetHexColor(toggleButtonConfig.colorOnUnchecked) << ")\n"
            "if (isPressed) item.indicator.border.color = item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnCheckedAndPressed) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUncheckedAndPressed) << ";\n"
            "else  item.indicator.border.color = (item.hovered || item.activeFocus) ? (item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnCheckedAndHovered) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUncheckedAndHovered) << ") : (item.checked ? " << context->GetHexColor(toggleButtonConfig.borderColorOnChecked) << " : " << context->GetHexColor(toggleButtonConfig.borderColorOnUnchecked) << ")\n"
            "}\n"
        );

        uiColumn->AddChild(uiInnerColumn);
        uiColumn->AddFunctions(getChoiceSetSelectedValuesFunc(uiButtonGroup, choiceset.isMultiSelect));
        return uiColumn;
	}

    const std::string AdaptiveCardQmlRenderer::getChoiceSetSelectedValuesFunc(const std::shared_ptr<QmlTag>& btnGroup, const bool isMultiselect)
    {
        std::ostringstream function;
        function << "function getSelectedValues(isMultiselect){\n";
        function << "var values = \"\";\n";
        if (isMultiselect)
        {
            function << "for (var i = 0; i < " << btnGroup->GetId() << ".buttons.length; ++i) {\n";
            function << "if(i !== 0 && " << btnGroup->GetId() << ".buttons[i].value !== \"\" && values !== \"\"){\n";
            function << "values += \",\";\n";
            function << "}\n";
            function << "values += " << btnGroup->GetId() << ".buttons[i].value;\n";
            function << "}\n";
        }
        else
        {
            function << "for (var i = 0; i < " << btnGroup->GetId() << ".buttons.length; ++i) {\n";
            function << "if(" << btnGroup->GetId() << ".buttons[i].value !== \"\"){\n";
            function << "values += " << btnGroup->GetId() << ".buttons[i].value;\n";
            function << "break;\n";
            function << "}\n}\n";
        }
        function << "return values;\n";
        function << "}\n";
        return function.str();
    }

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetCheckBox(Checkbox checkbox, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto toggleButtonConfig = context->GetRenderConfig()->getToggleButtonConfig();

        std::shared_ptr<QmlTag> uiButton;

        if (checkbox.type == CheckBoxType::RadioButton)
        {
            uiButton = std::make_shared<QmlTag>("RadioButton");
        }
        else
        {
            uiButton = std::make_shared<QmlTag>("CheckBox");
        }

        uiButton->Property("id", checkbox.id);

        if (checkbox.type == CheckBoxType::Toggle)
        {
            uiButton->Property("readonly property string valueOn", checkbox.valueOn, true);
            uiButton->Property("readonly property string valueOff", checkbox.valueOff, true);
            uiButton->Property("property string value", "checked ? valueOn : valueOff");
            uiButton->Property("width", "parent.width");
        }
        else
        {
            uiButton->Property("property string value", Formatter() << "checked ? \"" << checkbox.value << "\" : \"\"");
            uiButton->Property("Layout.maximumWidth", "parent.parent.parent.width");
        }

        uiButton->Property("text", checkbox.text, true);
        uiButton->Property("font.pixelSize", Formatter() << toggleButtonConfig.pixelSize);

        if (!checkbox.isVisible)
        {
            uiButton->Property("visible", "false");
        }

        if (checkbox.isChecked)
        {
            uiButton->Property("checked", "true");
        }

        auto uiOuterRectangle = std::make_shared<QmlTag>("Rectangle");
        uiOuterRectangle->Property("width", Formatter() << toggleButtonConfig.radioButtonOuterCircleSize);
        uiOuterRectangle->Property("height", Formatter() << toggleButtonConfig.radioButtonOuterCircleSize);
        uiOuterRectangle->Property("y", "parent.topPadding + (parent.availableHeight - height) / 2");
        if (checkbox.type == CheckBoxType::RadioButton)
        {
            uiOuterRectangle->Property("radius", "height/2");
        }
        else
        {
            uiOuterRectangle->Property("radius", Formatter() << toggleButtonConfig.checkBoxBorderRadius);
        }

        std::shared_ptr<QmlTag> uiInnerSegment;

        if (checkbox.type == CheckBoxType::RadioButton)
        {
            uiInnerSegment = std::make_shared<QmlTag>("Rectangle");
            uiInnerSegment->Property("width", Formatter() << toggleButtonConfig.radioButtonInnerCircleSize);
            uiInnerSegment->Property("height", Formatter() << toggleButtonConfig.radioButtonInnerCircleSize);
            uiInnerSegment->Property("x", "(parent.width - width)/2");
            uiInnerSegment->Property("y", "(parent.height - height)/2");
            uiInnerSegment->Property("radius", "height/2");
            uiInnerSegment->Property("color", Formatter() << checkbox.id << ".checked ? " << context->GetHexColor(toggleButtonConfig.radioButtonInnerCircleColorOnChecked) << " : 'transparent'");
            uiInnerSegment->Property("visible", checkbox.id + ".checked");
            uiButton->Property("Keys.onReturnPressed", "{if(!checked){checked = !checked;}}");
        }
        else
        {
            uiInnerSegment = std::make_shared<QmlTag>("Image");
            uiInnerSegment->Property("anchors.centerIn", "parent");
            uiInnerSegment->Property("width", "parent.width - 3");
            uiInnerSegment->Property("height", "parent.height - 3");
            uiInnerSegment->Property("visible", checkbox.id + ".checked");
            uiInnerSegment->Property("source", RendererQml::check_icon_12, true);
            uiButton->Property("Keys.onReturnPressed", "{checked = !checked;}");
        }

        uiOuterRectangle->AddChild(uiInnerSegment);
        uiOuterRectangle->Property("border.width", Formatter() << "parent.checked ? 0 : " << toggleButtonConfig.borderWidth);

        uiButton->Property("indicator", uiOuterRectangle->ToString());

        auto uiText = std::make_shared<QmlTag>("Text");
        uiText->Property("text", "parent.text");
        uiText->Property("font", "parent.font");
        uiText->Property("horizontalAlignment", "Text.AlignLeft");
        uiText->Property("verticalAlignment", "Text.AlignVCenter");
        uiText->Property("leftPadding", "parent.indicator.width + parent.spacing");
        uiText->Property("color", context->GetHexColor(toggleButtonConfig.textColor));

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
        auto dateInputConfig = context->GetRenderConfig()->getInputDateConfig();
        const std::string origionalElementId = input->GetId();
        input->SetId(context->ConvertToValidId(input->GetId()));

        auto uiTextFieldId = input->GetId();
        auto uiTextField = std::make_shared<QmlTag>("TextField");
        uiTextField->Property("id", uiTextFieldId);
        uiTextField->Property("width", "parent.width");
        uiTextField->Property("height", "parent.height");
        uiTextField->Property("font.family", context->GetConfig()->GetFontFamily(AdaptiveCards::FontType::Default), true);
        uiTextField->Property("font.pixelSize", Formatter() << dateInputConfig.pixelSize);
        uiTextField->Property("selectByMouse", "true");
        uiTextField->Property("selectedTextColor", "'white'");
        uiTextField->Property("color", context->GetHexColor(dateInputConfig.textColor));
        uiTextField->Property("property string selectedDate", input->GetValue(), true);
        uiTextField->AddFunctions(Formatter() << "signal " << "textChanged" << uiTextField->GetId() << "(var dateText)");

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        backgroundTag->Property("color", "'transparent'");
        uiTextField->Property("background", backgroundTag->ToString());

        //TODO: Add stretch property

        if (!input->GetIsVisible())
        {
            uiTextField->Property("visible", "false");
        }

        const std::string calendar_box_id = Formatter() << input->GetId() << "_calendarBox";
		
		std::string minimumDate = "";
		std::string maximumDate = "";

        if (!input->GetMin().empty() && Utils::isValidDate(input->GetMin()))
        {
            minimumDate = Utils::GetDate(input->GetMin());
        }

        if (!input->GetMax().empty() && Utils::isValidDate(input->GetMax()))
        {
            maximumDate = Utils::GetDate(input->GetMax());
        }

        auto EnumDateFormat = Utils::GetSystemDateFormat();

        const auto dateSeparator = "\\/";
        const auto day_Regex = "([-0123]-|0\\d|[12]\\d|3[01])";
        const auto month_Regex = "(---|[JFMASOND]--|Ja-|Jan|Fe-|Feb|Ma-|Mar|Ap-|Apr|May|Ju-|Jun|Jul|Au-|Aug|Se-|Sep|Oc-|Oct|No-|Nov|De-|Dec)";
        const auto year_Regex = "(-{4}|\\d-{3}|\\d{2}-{2}|\\d{3}-|\\d{4})";

        //Default date format: MMM-dd-yyyy
        auto month_Text = "getText(0,3)";
        auto day_Text = "getText(4,6)";
        auto year_Text = "getText(7,11)";
        std::string DateRegex = Formatter() << "/^" << month_Regex << dateSeparator << day_Regex << dateSeparator << year_Regex << "$/";
        std::string StringDateFormat = Formatter() << "MMM" << dateSeparator << "dd" << dateSeparator << "yyyy";
        std::string inputMask = Formatter() << ">x<xx" << dateSeparator << "xx" << dateSeparator << "xxxx;-";

        switch (EnumDateFormat)
        {
            case RendererQml::DateFormat::ddmmyy:
            {
                StringDateFormat = Formatter() << "dd" << dateSeparator << "MMM" << dateSeparator << "yyyy";
                inputMask = Formatter() << "xx" << dateSeparator << ">x<xx" << dateSeparator << "xxxx;-";
                DateRegex = Formatter() << "/^" << day_Regex << dateSeparator << month_Regex << dateSeparator << year_Regex << "$/";

                day_Text = "getText(0,2)";
                month_Text = "getText(3,6)";
                year_Text = "getText(7,11)";
                break;
            }
            case RendererQml::DateFormat::yymmdd:
            {
                StringDateFormat = Formatter() << "yyyy" << dateSeparator << "MMM" << dateSeparator << "dd";
                inputMask = Formatter() << "xxxx" << dateSeparator << ">x<xx" << dateSeparator << "xx;-";
                DateRegex = Formatter() << "/^" << year_Regex << dateSeparator << month_Regex << dateSeparator << day_Regex << "$/";

                day_Text = "getText(9,11)";
                month_Text = "getText(5,8)";
                year_Text = "getText(0,4)";
                break;
            }
            case RendererQml::DateFormat::yyddmm:
            {
                StringDateFormat = Formatter() << "yyyy" << dateSeparator << "dd" << dateSeparator << "MMM";
                inputMask = Formatter() << "xxxx" << dateSeparator << "xx" << dateSeparator << ">x<xx;-";
                DateRegex = Formatter() << "/^" << year_Regex << dateSeparator << day_Regex << dateSeparator << month_Regex << "$/";

                day_Text = "getText(5,7)";
                month_Text = "getText(8,11)";
                year_Text = "getText(0,4)";
                break;
            }
            //Default case: mm-dd-yyyy
            default:
            {
                break;
            }
        }

        uiTextField->AddFunctions(Formatter() << "function setValidDate(dateString)"
            << "{"
            << "var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};"
            << "var d=new Date(" << year_Text << ","
            << "Months[" << month_Text << "]," << day_Text << ");"
            << "if( d.getFullYear().toString() === " << year_Text << "&& d.getMonth()===Months[" << month_Text << "] && d.getDate().toString()===" << day_Text << ")"
            << "{"
            << "selectedDate = d.toLocaleString(Qt.locale(\"en_US\"),\"yyyy-MM-dd\");"
            << "}"
            << "else { selectedDate = '' };"
            << "}");

        uiTextField->Property("onTextChanged", Formatter() << "{" << "textChanged" << uiTextField->GetId() << "(text);"
            << "setValidDate(text);"
            << "}");

        if (!input->GetValue().empty() && Utils::isValidDate(input->GetValue()))
        {
            uiTextField->Property("text", Formatter() << Utils::GetDate(input->GetValue()) << ".toLocaleString(Qt.locale(\"en_US\"),"
                << "\"" << StringDateFormat << "\""
                << ")");
        }

        uiTextField->Property("validator", Formatter() << "RegExpValidator { regExp: " << DateRegex << "}");
        uiTextField->Property("onFocusChanged", Formatter() << "{"
            << "if(focus===true) inputMask=\"" << inputMask << "\";"
            << "if(focus === false){ "
            << "if(text === \"" << std::string(dateSeparator) + std::string(dateSeparator) << "\"){ inputMask = \"\" ; } "
            << "}} ");

		auto dateFormat = StringDateFormat;
		uiTextField->Property("placeholderText", Formatter() << (!input->GetPlaceholder().empty() ? input->GetPlaceholder() : "Select date") << " in " << Utils::ToLower(dateFormat), true);
        uiTextField->Property("placeholderTextColor", context->GetHexColor(dateInputConfig.placeHolderColor));

        auto uiDateInputWrapper = std::make_shared<QmlTag>("Rectangle");
        auto uiDateInputRow = std::make_shared<QmlTag>("RowLayout");
        auto uiDateInputCombobox = std::make_shared<QmlTag>("ComboBox");
        auto popUp = GetCalendar(context, uiTextFieldId, calendar_box_id, StringDateFormat, minimumDate, maximumDate);

        popUp->Property("onClosed", Formatter() << uiTextField->GetId() << ".forceActiveFocus()");
        uiDateInputCombobox->Property("id", Formatter() << input->GetId() << "_combobox");
        uiDateInputCombobox->Property("Layout.fillWidth", "true");
        uiDateInputCombobox->Property("popup", popUp->ToString());
        uiDateInputCombobox->Property("indicator", "Rectangle{}");
        uiDateInputCombobox->Property("focusPolicy", "Qt.NoFocus");
        uiDateInputCombobox->Property("Keys.onReturnPressed", "this.popup.open()");

        uiDateInputWrapper->Property("id", Formatter() << input->GetId() << "_wrapper");
        uiDateInputWrapper->Property("width", "parent.width");
        uiDateInputWrapper->Property("height", Formatter() << dateInputConfig.height);
        uiDateInputWrapper->Property("radius", Formatter() << dateInputConfig.borderRadius);
        uiDateInputWrapper->Property("color", context->GetHexColor(dateInputConfig.backgroundColorNormal));
        uiDateInputWrapper->Property("border.color", Formatter() << input->GetId() << ".activeFocus? " << context->GetHexColor(dateInputConfig.borderColorOnFocus) << " : " << context->GetHexColor(dateInputConfig.borderColorNormal));
        uiDateInputWrapper->Property("border.width", Formatter() << dateInputConfig.borderWidth);
        uiDateInputWrapper->AddFunctions(Formatter() << "function colorChange(isPressed){\n"
            "if (isPressed)  color = " << context->GetHexColor(dateInputConfig.backgroundColorOnPressed) << ";\n"
            "else color = " << input->GetId() << ".activeFocus ? " << context->GetHexColor(dateInputConfig.backgroundColorOnPressed) << " : " << input->GetId() << ".hovered ? " << context->GetHexColor(dateInputConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(dateInputConfig.backgroundColorNormal) << "}"
        );

        uiTextField->Property("onPressed", Formatter() << uiDateInputWrapper->GetId() << ".colorChange(true)");
        uiTextField->Property("onReleased", Formatter() << uiDateInputWrapper->GetId() << ".colorChange(false)");
        uiTextField->Property("onHoveredChanged", Formatter() << uiDateInputWrapper->GetId() << ".colorChange(false)");
        uiDateInputCombobox->Property("onActiveFocusChanged", Formatter() << uiDateInputWrapper->GetId() << ".colorChange(false)");
        uiDateInputCombobox->Property("background", uiTextField->ToString());

        uiDateInputRow->Property("width", "parent.width");
        uiDateInputRow->Property("height", "parent.height");
        uiDateInputRow->Property("spacing", "0");

        auto dateIcon = GetClearIconButton(context);
        auto clearIcon = GetClearIconButton(context);

        dateIcon->RemoveProperty("anchors.right");
        dateIcon->RemoveProperty("anchors.margins");
        dateIcon->RemoveProperty("anchors.verticalCenter");
        dateIcon->Property("id", Formatter() << input->GetId() << "_icon");
        dateIcon->Property("Layout.leftMargin", Formatter() << dateInputConfig.dateIconHorizontalPadding);
        dateIcon->Property("focusPolicy", "Qt.NoFocus");
        dateIcon->Property("width", "18");
        dateIcon->Property("height", "18");
        dateIcon->Property("icon.color", Formatter() << input->GetId() << ".activeFocus ? " << context->GetHexColor(dateInputConfig.dateIconColorOnFocus) << " : " << context->GetHexColor(dateInputConfig.dateIconColorNormal));
        dateIcon->Property("icon.source", RendererQml::calendar_icon, true);
        std::string onClicked_value = "{ " + uiTextFieldId + ".forceActiveFocus(); " + calendar_box_id + ".open();}";
        dateIcon->Property("onClicked", onClicked_value);

        clearIcon->RemoveProperty("anchors.right");
        clearIcon->RemoveProperty("anchors.margins");
        clearIcon->RemoveProperty("anchors.verticalCenter");
        clearIcon->Property("id", Formatter() << input->GetId() << "_clear_icon");
        clearIcon->Property("Layout.rightMargin", Formatter() << dateInputConfig.clearIconHorizontalPadding);
        std::string clearIcon_visible_value = Formatter() << "(!" << uiTextFieldId << ".focus && " << uiTextFieldId << ".text !==\"\") || (" << uiTextFieldId << ".focus && " << uiTextFieldId << ".text !== " << "\"\\/\\/\")";
        clearIcon->Property("visible", clearIcon_visible_value);
        std::string clearIcon_OnClicked_value = Formatter() << " {"
            << "nextItemInFocusChain().forceActiveFocus();\n"
            << uiTextFieldId << ".clear();\n" << "}";
        clearIcon->Property("onClicked", clearIcon_OnClicked_value);
				
        context->addToInputElementList(origionalElementId, (uiTextField->GetId() + ".selectedDate"));

        uiDateInputRow->AddChild(dateIcon);
        uiDateInputRow->AddChild(uiDateInputCombobox);
        uiDateInputRow->AddChild(clearIcon);

        uiDateInputWrapper->AddChild(uiDateInputRow);

        return uiDateInputWrapper;
    }

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetCalendar(std::shared_ptr<AdaptiveRenderContext> context, const std::string textFieldId, const std::string calendarBoxId, const std::string stringDateFormat, const std::string minimumDate, const std::string maximumDate)
	{
        auto dateInputConfig = context->GetRenderConfig()->getInputDateConfig();
		//yyyy,mm,dd
		const std::vector<int>upperDateLimit{ 3000,0,1 };
		const std::vector<int>lowerDateLimit{ 0,0,1 };

		auto popupTag = std::make_shared<QmlTag>("Popup");
		popupTag->Property("id", calendarBoxId);
		popupTag->Property("y", Formatter() << textFieldId << ".height + 2");
        popupTag->Property("x", Formatter() << "-" << dateInputConfig.clearIconSize << "-" << dateInputConfig.dateIconHorizontalPadding);
		popupTag->Property("width", Formatter() << dateInputConfig.calendarWidth);
		popupTag->Property("height", Formatter() << dateInputConfig.calendarHeight);
		popupTag->Property("bottomInset", "0");
		popupTag->Property("topInset", "0");
		popupTag->Property("rightInset", "0");
		popupTag->Property("leftInset", "0");
		
		auto backgroundRectangle = std::make_shared<QmlTag>("Rectangle");
		backgroundRectangle->Property("radius", Formatter() << dateInputConfig.calendarBorderRadius);
		backgroundRectangle->Property("border.color", context->GetHexColor(dateInputConfig.calendarBorderColor));
		backgroundRectangle->Property("color", context->GetHexColor(dateInputConfig.calendarBackgroundColor));
				
		popupTag->Property("background", backgroundRectangle->ToString());

		auto listviewCalendar = std::make_shared<QmlTag>("ListView");
		listviewCalendar->Property("property int curCalendarYear", "0");
		listviewCalendar->Property("property int curCalendarMonth", "0");
		listviewCalendar->Property("property date minimumDate", minimumDate != "" ? minimumDate : Formatter() << "new Date(" << std::to_string(lowerDateLimit.at(0)) << "," << std::to_string(lowerDateLimit.at(1)) << "," << std::to_string(lowerDateLimit.at(2)) << ")");
		listviewCalendar->Property("property date maximumDate", maximumDate != "" ? maximumDate : Formatter() << "new Date(" << std::to_string(upperDateLimit.at(0)) << "," << std::to_string(upperDateLimit.at(1)) << "," << std::to_string(upperDateLimit.at(2)) << ")");
		listviewCalendar->Property("property date selectedDate", "new Date()");

		listviewCalendar->Property("id", Formatter() << textFieldId << "_calendarRoot");

		listviewCalendar->Property("anchors.fill", "parent");
		listviewCalendar->AddFunctions("signal clicked(date clickedDate)");

		listviewCalendar->AddFunctions(Formatter() << "function setDate(clickedDate)" << "{"
			<< "selectedDate = clickedDate;"
			<< "curCalendarYear = selectedDate.getFullYear();"
			<< "curCalendarMonth = selectedDate.getMonth();"
            << "var curIndex = (selectedDate.getFullYear()) * 12 + selectedDate.getMonth();"
            << "currentIndex = curIndex;"
			<< "positionViewAtIndex(curIndex, ListView.Center);" << " }");

		listviewCalendar->AddFunctions(Formatter() << "function setCalendarDateFromString(dateString)\n"
			<< "{\n"
			<< "var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};\n"
			<< "var y=dateString.match(/[0-9]{4}/);\n"
			<< "dateString=dateString.replace(y,\"\");\n"
			<< "var m=dateString.match(/[a-zA-Z]{3}/);\n"
			<< "var d=dateString.match(/[0-9]{2}/);\n"
			<< "if (d!==null && m!==null && y!==null){selectedDate=new Date(y[0],Months[m[0]],d[0]) }\n"
			<< "setDate(selectedDate)\n"
			<< "}");

        listviewCalendar->Property("Keys.onPressed", Formatter() << "{"
            << "var date = new Date(selectedDate)\n"
            << "if (event.key === Qt.Key_Right)\n"
            << "date.setDate(date.getDate() + 1)\n"
            << "else if (event.key === Qt.Key_Left)\n"
            << "date.setDate(date.getDate() - 1)\n"
            << "else if (event.key === Qt.Key_Up)\n"
            << "date.setDate(date.getDate() - 7)\n"
            << "else if (event.key === Qt.Key_Down)\n"
            << "date.setDate(date.getDate() + 7)\n"
            << "else if (event.key === Qt.Key_Return)\n"
            << "{\n"
            << popupTag->GetId() << ".close();\n"
            << textFieldId << ".text = selectedDate.toLocaleString(Qt.locale(\"en_US\"), \"dd\\/MMM\\/yyyy\")\n"
            << "}\n"
            << "if (date >= minimumDate && date <= maximumDate)\n"
            << "{\n"
            << "selectedDate = new Date(date)\n"
            << "currentIndex = (selectedDate.getFullYear()) * 12 + selectedDate.getMonth()\n"
            << "}"
            << "event.accepted = true\n"
        "}\n");

		listviewCalendar->Property("Component.onCompleted", Formatter() << "{"
			<< textFieldId << "." << "textChanged" << textFieldId << ".connect(setCalendarDateFromString);"
			<< textFieldId << "." << "textChanged" << textFieldId << "( " << textFieldId << ".text)"
			<< "}");

		listviewCalendar->Property("snapMode", "ListView.SnapOneItem");
		listviewCalendar->Property("orientation", "Qt.Horizontal");
		listviewCalendar->Property("clip", "true");
		listviewCalendar->Property("model", std::to_string((upperDateLimit.at(0)-lowerDateLimit.at(0)) * 12));
		listviewCalendar->Property("onClicked", Formatter() << "{" << "setDate(clickedDate)" << "}");

        popupTag->Property("onOpened", Formatter() << listviewCalendar->GetId() << ".forceActiveFocus()");

		auto listViewDelegate = std::make_shared<QmlTag>("Item");
		listViewDelegate->Property("id", Formatter() << textFieldId << "listViewDelegate");
		listViewDelegate->Property("property int year", "Math.floor(index/12)");
		listViewDelegate->Property("property int month", "index%12");
		listViewDelegate->Property("property int firstDay", "(new Date(year, month, 1).getDay()-1 < 0 ? 6 : new Date(year, month, 1).getDay() - 1)");
		listViewDelegate->Property("width", Formatter() << listviewCalendar->GetId() << ".width");
		listViewDelegate->Property("height", Formatter() << listviewCalendar->GetId() << ".height");

		auto headerText = std::make_shared<QmlTag>("Text");
		headerText->Property("id", Formatter() << textFieldId << "headerText");
		headerText->Property("anchors.left", "parent.left");
		headerText->Property("color", context->GetHexColor(dateInputConfig.textColor));
		headerText->Property("text", Formatter() << "['January', 'February', 'March', 'April', 'May', 'June','July', 'August', 'September', 'October', 'November', 'December'][" << listViewDelegate->GetId() << ".month] + ' ' + " << listViewDelegate->GetId() << ".year");
		headerText->Property("font.pixelSize", Formatter() << dateInputConfig.calendarHeaderTextSize);
		listViewDelegate->AddChild(headerText);

		auto monthGrid = std::make_shared<QmlTag>("Grid");
		const std::string monthGridId = Formatter() << textFieldId << "gridId";
		monthGrid->Property("id", monthGridId);
		monthGrid->Property("anchors.top", Formatter() << headerText->GetId() << ".bottom");
		monthGrid->Property("anchors.right", "parent.right");
		monthGrid->Property("anchors.left", "parent.left");
		monthGrid->Property("anchors.bottom", "parent.bottom");
		monthGrid->Property("anchors.topMargin", Formatter() << dateInputConfig.dateGridTopMargin);
		monthGrid->Property("clip", "true");
		monthGrid->Property("columns", "7");
		monthGrid->Property("rows", "7");
		listViewDelegate->AddChild(monthGrid);

		auto repeaterTag = std::make_shared<QmlTag>("Repeater");
		repeaterTag->Property("model", Formatter() << monthGridId << ".columns * " << monthGridId << ".rows");

		auto delegateRectangle = std::make_shared<QmlTag>("Rectangle");
		delegateRectangle->Property("id", Formatter() << textFieldId << "delegateRectangle");

		auto delegateMouseArea = std::make_shared<QmlTag>("MouseArea");
		delegateMouseArea->Property("id", Formatter() << textFieldId << "delegateMouseArea");

		auto delegateText = std::make_shared<QmlTag>("Text");
		delegateText->Property("id", Formatter() << textFieldId << "delegateText");
		delegateText->Property("anchors.centerIn", "parent");
		delegateText->Property("font.pixelSize", Formatter() << "day < 0 ? " << dateInputConfig.calendarDayTextSize << " : " << dateInputConfig.calendarDateTextSize);
		delegateText->Property("color", Formatter() << "{\n"
			<< "if (" << delegateRectangle->GetId() << ".cellDate.toDateString() === " << listviewCalendar->GetId() << ".selectedDate.toDateString() && " << delegateMouseArea->GetId() << ".enabled)\n"
			<< "\"white\"\n"
			<< "else if (" << delegateRectangle->GetId() << ".cellDate.getMonth() === " << listViewDelegate->GetId() << ".month && " << delegateMouseArea->GetId() << ".enabled)\n"
			<< context->GetHexColor(dateInputConfig.textColor) << "\n"
			<< "else\n"
			<< context->GetHexColor(dateInputConfig.notAvailabledateElementTextColor) << "\n"
			<< "}");
		delegateText->Property("text", Formatter() << "{" << "if (day < 0)"
			<< delegateRectangle->GetId() << ".dayArray[index]" << "\n"
			<< "else if (new Date(year, month, date).getMonth() == month)" << "\n"
			<< "date" << "\n"
			<< "else" << "\n"
			<< "cellDate.getDate()" << "}");

		delegateMouseArea->Property("anchors.fill", "parent");
		delegateMouseArea->Property("enabled", Formatter() << delegateText->GetId() << ".text &&  day >= 0 && (new Date(year,month,date) >= " << listviewCalendar->GetId() << ".minimumDate ) && (new Date(year,month,date) <= " << listviewCalendar->GetId() << ".maximumDate )");
		delegateMouseArea->Property("hoverEnabled", "true");
		delegateMouseArea->Property("onClicked", Formatter() << "{"
			<< "var selectedDate = new Date(year, month, date);"
			<< listviewCalendar->GetId() << ".clicked(selectedDate)" << "}");
		delegateMouseArea->Property("onReleased", Formatter() << "{\n"
			<< popupTag->GetId() << ".close();\n"
			<< listviewCalendar->GetId() << ".selectedDate = " << delegateRectangle->GetId() << ".cellDate\n"
			<< textFieldId << ".text = " << listviewCalendar->GetId() << ".selectedDate.toLocaleString(Qt.locale(\"en_US\"),\"" << stringDateFormat << "\")\n"
			<< "}");

		delegateRectangle->Property("property int day", "index - 7");
		delegateRectangle->Property("property int date", Formatter() <<"day - " << listViewDelegate->GetId() << ".firstDay + 1");
		delegateRectangle->Property("width", Formatter() << dateInputConfig.dateElementSize);
		delegateRectangle->Property("height", Formatter() << dateInputConfig.dateElementSize);
		delegateRectangle->Property("property variant dayArray", "['M', 'T', 'W', 'T', 'F', 'S', 'S']");
		delegateRectangle->Property("color", Formatter() << "new Date(year,month,date).toDateString() == " << listviewCalendar->GetId() << ".selectedDate.toDateString() && " << delegateMouseArea->GetId() << ".enabled" << "? " << context->GetHexColor(dateInputConfig.dateElementColorOnFocus) << " : " << delegateMouseArea->GetId() << ".containsMouse? " << context->GetHexColor(dateInputConfig.dateElementColorOnHover) << " :" << context->GetHexColor(dateInputConfig.dateElementColorNormal));
		delegateRectangle->Property("radius", "0.5 * width");
		delegateRectangle->Property("property date cellDate", "new Date(year,month,date)");

		delegateRectangle->AddChild(delegateText);
		delegateRectangle->AddChild(delegateMouseArea);
		repeaterTag->Property("delegate",delegateRectangle->ToString());

		monthGrid->AddChild(repeaterTag);

		listviewCalendar->Property("delegate",listViewDelegate->ToString());
		auto contentItemRectangle = std::make_shared<QmlTag>("Rectangle");
		contentItemRectangle->Property("radius", Formatter() << dateInputConfig.calendarBorderRadius);
		contentItemRectangle->Property("color", context->GetHexColor(dateInputConfig.calendarBackgroundColor));
		contentItemRectangle->AddChild(listviewCalendar);

        auto iconBackground = std::make_shared<QmlTag>("Rectangle");
        iconBackground->Property("color", context->GetHexColor(dateInputConfig.calendarBackgroundColor));

		auto rightArrowButton = GetIconTag(context);
		rightArrowButton->Property("id", Formatter() << textFieldId << "_rightArrow");
		rightArrowButton->RemoveProperty("anchors.bottom");
		rightArrowButton->Property("width","icon.width");
		rightArrowButton->Property("height","icon.height");
		rightArrowButton->Property("icon.width", Formatter() << dateInputConfig.arrowIconSize);
		rightArrowButton->Property("icon.height", Formatter() << dateInputConfig.arrowIconSize);
		rightArrowButton->Property("horizontalPadding", "0");
		rightArrowButton->Property("verticalPadding", "0");
		rightArrowButton->Property("anchors.margins", "0");
		rightArrowButton->Property("icon.source", RendererQml::right_arrow_28, true);
        rightArrowButton->Property("background", iconBackground->ToString());

		std::string rightArrowOnClicked = Formatter() << "{\n"
			<< listviewCalendar->GetId() << ".curCalendarYear = " << listviewCalendar->GetId() << ".curCalendarMonth ==11? " << listviewCalendar->GetId() << ".curCalendarYear + 1 : " << listviewCalendar->GetId() << ".curCalendarYear;\n"
			<< listviewCalendar->GetId() << ".curCalendarMonth = (" << listviewCalendar->GetId() << ".curCalendarMonth + 1)%12;\n"
			<< listviewCalendar->GetId() << ".positionViewAtIndex((" << listviewCalendar->GetId() << ".curCalendarYear) * 12 + (" << listviewCalendar->GetId() << ".curCalendarMonth), ListView.Center);\n"
			<< "}\n";
		rightArrowButton->Property("onClicked", rightArrowOnClicked);

		auto leftArrowButton = GetIconTag(context);
		leftArrowButton->Property("id", Formatter() << textFieldId << "_leftArrow");
		leftArrowButton->RemoveProperty("anchors.bottom");
		leftArrowButton->Property("width", "icon.width");
		leftArrowButton->Property("height", "icon.height");
		leftArrowButton->Property("horizontalPadding", "0");
		leftArrowButton->Property("verticalPadding", "0");
		leftArrowButton->Property("anchors.margins", "0");
		leftArrowButton->Property("icon.width", Formatter() << dateInputConfig.arrowIconSize);
		leftArrowButton->Property("icon.height", Formatter() << dateInputConfig.arrowIconSize);
		leftArrowButton->Property("anchors.right", Formatter() << rightArrowButton->GetId() << ".left");
		leftArrowButton->Property("icon.source", RendererQml::left_arrow_28, true);
        leftArrowButton->Property("background", iconBackground->ToString());

		std::string leftArrowOnClicked = Formatter() << "{\n"
			<< listviewCalendar->GetId() << ".curCalendarYear = " << listviewCalendar->GetId() << ".curCalendarMonth - 1 < 0 ? " << listviewCalendar->GetId() << ".curCalendarYear - 1 : " << listviewCalendar->GetId() << ".curCalendarYear;\n"
			<< listviewCalendar->GetId() << ".curCalendarMonth = " << listviewCalendar->GetId() << ".curCalendarMonth - 1 < 0 ? 11 : " << listviewCalendar->GetId() << ".curCalendarMonth - 1;\n"
			<< listviewCalendar->GetId() << ".positionViewAtIndex((" << listviewCalendar->GetId() << ".curCalendarYear) * 12 + (" << listviewCalendar->GetId() << ".curCalendarMonth), ListView.Center);\n"
			<< "}\n";
		leftArrowButton->Property("onClicked", leftArrowOnClicked);

		popupTag->AddChild(rightArrowButton);
		popupTag->AddChild(leftArrowButton);
		popupTag->Property("contentItem",contentItemRectangle->ToString());
		return popupTag;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::FactSetRender(std::shared_ptr<AdaptiveCards::FactSet> factSet, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto uiFactSet = std::make_shared<QmlTag>("GridLayout");

		if (!factSet->GetId().empty())
		{
			factSet->SetId(context->ConvertToValidId(factSet->GetId()));
			uiFactSet->Property("id", factSet->GetId());
		}

		uiFactSet->Property("columns", "2");
		uiFactSet->Property("rows", std::to_string(factSet->GetFacts().size()));
		uiFactSet->Property("property int titleWidth", "0");
		uiFactSet->Property("property int minWidth", Formatter() << context->getCardRootId() << ".getMinWidthFactSet(children, columnSpacing)");
		uiFactSet->AddFunctions("function setTitleWidth(item){	if (item.width > titleWidth){ titleWidth = item.width }}");

		if (!factSet->GetIsVisible())
		{
			uiFactSet->Property("visible", "false");
		}

		for (const auto fact : factSet->GetFacts())
		{
			auto factTitle = std::make_shared<AdaptiveCards::TextBlock>();

			factTitle->SetText(fact->GetTitle());
			factTitle->SetTextSize(context->GetConfig()->GetFactSet().title.size);
			factTitle->SetTextColor(context->GetConfig()->GetFactSet().title.color);
			factTitle->SetTextWeight(context->GetConfig()->GetFactSet().title.weight);
			factTitle->SetIsSubtle(context->GetConfig()->GetFactSet().title.isSubtle);
			factTitle->SetWrap(context->GetConfig()->GetFactSet().title.wrap);

			//TODO: cpp Object Model does not support max width.
			//factTitle->SetMaxWidth(context->GetConfig()->GetFactSet().title.maxWidth);

			auto uiTitle = context->Render(factTitle);
			uiTitle->Property("Layout.maximumWidth", std::to_string(context->GetConfig()->GetFactSet().title.maxWidth));
			uiTitle->Property("Component.onCompleted", "parent.setTitleWidth(this)");

			//uiTitle->Property("spacing", std::to_string(context->GetConfig()->GetFactSet().spacing));

			auto factValue = std::make_shared<AdaptiveCards::TextBlock>();

			factValue->SetText(fact->GetValue());
			factValue->SetTextSize(context->GetConfig()->GetFactSet().value.size);
			factValue->SetTextColor(context->GetConfig()->GetFactSet().value.color);
			factValue->SetTextWeight(context->GetConfig()->GetFactSet().value.weight);
			factValue->SetIsSubtle(context->GetConfig()->GetFactSet().value.isSubtle);
			factValue->SetWrap(context->GetConfig()->GetFactSet().value.wrap);
			// MaxWidth is not supported on the Value of FactSet. Do not set it.

			auto uiValue = context->Render(factValue);
			uiValue->Property("Layout.preferredWidth", "parent.parent.width - parent.titleWidth");

			uiFactSet->AddChild(uiTitle);
			uiFactSet->AddChild(uiValue);
		}

		return uiFactSet;
    }

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ImageRender(std::shared_ptr<AdaptiveCards::Image> image, std::shared_ptr<AdaptiveRenderContext> context)
	{
		//TODO: Height(Stretch/Automatic)

		std::shared_ptr<QmlTag> maskTag;
		std::shared_ptr<QmlTag> maskSourceTag;
		auto uiRectangle = std::make_shared<QmlTag>("Rectangle");
		auto uiImage = std::make_shared<QmlTag>("Image");

		if (image->GetId().empty())
		{
			image->SetId(Formatter() << "image_auto_" << context->getImageCounter());
		}
        else
        {
            image->SetId(context->ConvertToValidId(image->GetId()));
        }

		uiRectangle->Property("id", image->GetId());
		uiRectangle->Property("implicitHeight", "height");
        uiRectangle->Property("readonly property string bgColor", "'transparent'");
		uiImage->Property("id", Formatter() << image->GetId() << "_img");
		uiImage->Property("readonly property bool isImage", "true");
        uiImage->Property("cache", "false");
		uiImage->Property("source", image->GetUrl(), true);
		uiImage->Property("anchors.fill", "parent");
		uiImage->Property("visible", "parent.visible");

		if (!image->GetIsVisible())
		{
			uiRectangle->Property("visible", "false");
		}

		if (image->GetHeight() == AdaptiveCards::HeightType::Stretch && image->GetPixelHeight() == 0)
		{
			uiRectangle->Property("readonly property bool stretch", "true");
		}

		if (image->GetPixelWidth() != 0 || image->GetPixelHeight() != 0)
		{
			if (image->GetPixelWidth() != 0)
			{
				uiRectangle->Property("width", Formatter() << "parent.width != 0 ? Math.min(" << image->GetPixelWidth() << ", parent.width) : " << image->GetPixelWidth());

				if (image->GetPixelHeight() == 0)
				{
					uiRectangle->Property("height", Formatter() << image->GetId() << "_img.implicitHeight / " << image->GetId() << "_img.implicitWidth * width");
				}
			}
			if (image->GetPixelHeight() != 0)
			{
				uiRectangle->Property("height", Formatter() << image->GetPixelHeight());

				if (image->GetPixelWidth() == 0)
				{
					uiRectangle->Property("readonly property int aspectWidth", Formatter() << image->GetId() << "_img.implicitWidth / " << image->GetId() << "_img.implicitHeight * height");
					uiRectangle->Property("width", Formatter() << "parent.width != 0 ? Math.min(aspectWidth, parent.width) : aspectWidth");
				}
			}

			if (image->GetPixelWidth() != 0)
			{
				uiRectangle->Property("implicitWidth", std::to_string(image->GetPixelWidth()));
			}
			else
			{
				uiRectangle->Property("implicitWidth", "aspectWidth");
			}
		}
		else
		{
			switch (image->GetImageSize())
			{
			case AdaptiveCards::ImageSize::None:
			case AdaptiveCards::ImageSize::Auto:
				uiRectangle->Property("width", "parent.width");
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
				break;
			}

			uiRectangle->Property("height", Formatter() << image->GetId() << "_img.implicitHeight / " << image->GetId() << "_img.implicitWidth * width");

			if (image->GetImageSize() == AdaptiveCards::ImageSize::None)
			{
				uiRectangle->Property("implicitWidth", Formatter() << image->GetId() << "_img.implicitWidth");
			}
			else
			{
				uiRectangle->Property("implicitWidth", "width");
			}

		}

		if (!image->GetBackgroundColor().empty())
		{
            uiRectangle->Property("readonly property string bgColor", context->GetRGBColor(image->GetBackgroundColor()));
		}
        uiRectangle->Property("color", "bgColor");

		switch (image->GetHorizontalAlignment())
		{
		case AdaptiveCards::HorizontalAlignment::Center:
			uiRectangle->Property("anchors.horizontalCenter", "parent.horizontalCenter");
			break;
		case AdaptiveCards::HorizontalAlignment::Right:
			uiRectangle->Property("anchors.right", "parent.right");
			break;
		default:
			break;
		}

		switch (image->GetImageStyle())
		{
		case AdaptiveCards::ImageStyle::Default:
			break;
		case AdaptiveCards::ImageStyle::Person:
			uiRectangle->Property("radius", "width/2");
			break;
		}

		uiRectangle->AddChild(uiImage);

        addSelectAction(uiRectangle, uiRectangle->GetId(), image->GetSelectAction(), context);

		return uiRectangle;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::TimeInputRender(std::shared_ptr<AdaptiveCards::TimeInput> input, std::shared_ptr<AdaptiveRenderContext> context)
	{
        auto timeConfig = context->GetRenderConfig()->getInputTimeConfig();

        const std::string origionalElementId = input->GetId();
        const bool is12hour = Utils::isSystemTime12Hour();

        input->SetId(context->ConvertToValidId(input->GetId()));

        auto uiTimeInputWrapper = std::make_shared<QmlTag>("Rectangle");
        auto uiTimeInputRow = std::make_shared<QmlTag>("RowLayout");
        auto uiTimeComboBox = std::make_shared<QmlTag>("ComboBox");
        uiTimeComboBox->Property("id", Formatter() << input->GetId() << "_combobox");

        auto uiTimeInput = std::make_shared<QmlTag>("TextField");
        const std::string id = input->GetId();
        const std::string value = input->GetValue();
        const int fontSize = context->GetConfig()->GetFontSize(AdaptiveCards::FontType::Default, AdaptiveCards::TextSize::Default);

        uiTimeInputWrapper->Property("id", Formatter() << input->GetId() << "_wrapper");
        uiTimeInputWrapper->Property("width", "parent.width");
        uiTimeInputWrapper->Property("height", Formatter() << timeConfig.height);
        uiTimeInputWrapper->Property("radius", Formatter() << timeConfig.borderRadius);
        uiTimeInputWrapper->Property("color", context->GetHexColor(timeConfig.backgroundColorNormal));
        uiTimeInputWrapper->Property("border.color", Formatter() << input->GetId() << ".activeFocus? " << context->GetHexColor(timeConfig.borderColorOnFocus) << " : " << context->GetHexColor(timeConfig.borderColorNormal));
        uiTimeInputWrapper->Property("border.width", Formatter() << timeConfig.borderWidth);
        uiTimeInputWrapper->AddFunctions(Formatter() << "function colorChange(isPressed){\n"
            "if (isPressed)  color = " << context->GetHexColor(timeConfig.backgroundColorOnPressed) << ";\n"
            "else color = " << uiTimeComboBox->GetId() << ".activeFocus ? " << context->GetHexColor(timeConfig.backgroundColorOnPressed) << " : " << id << ".hovered ? " << context->GetHexColor(timeConfig.backgroundColorOnHovered) << " : " << context->GetHexColor(timeConfig.backgroundColorNormal) << "}"
        );

        uiTimeInputRow->Property("width", "parent.width");
        uiTimeInputRow->Property("height", Formatter() << id << ".implicitHeight");
        uiTimeInputRow->Property("spacing", "0");

        uiTimeInput->Property("id", id);
        uiTimeInput->Property("font.family", context->GetConfig()->GetFontFamily(AdaptiveCards::FontType::Default), true);
        uiTimeInput->Property("font.pixelSize", Formatter() << timeConfig.pixelSize);
        uiTimeInput->Property("selectByMouse", "true");
        uiTimeInput->Property("selectedTextColor", "'white'");
        uiTimeInput->Property("property string selectedTime", "", true);
        uiTimeInput->Property("width", "parent.width");
        uiTimeInput->Property("placeholderTextColor", context->GetHexColor(timeConfig.placeHolderColor));
        uiTimeInput->Property("placeholderText", !input->GetPlaceholder().empty() ? input->GetPlaceholder() : "Select time", true);
        uiTimeInput->Property("color", context->GetHexColor(timeConfig.textColor));
        uiTimeInput->Property("onPressed", Formatter() << uiTimeInputWrapper->GetId() << ".colorChange(true)");
        uiTimeInput->Property("onReleased", Formatter() << uiTimeInputWrapper->GetId() << ".colorChange(false)");
        uiTimeInput->Property("onHoveredChanged", Formatter() << uiTimeInputWrapper->GetId() << ".colorChange(false)");

        uiTimeInput->Property("validator", "RegExpValidator { regExp: /^(--|[01][0-9|-]|2[0-3|-]):(--|[0-5][0-9|-])$/}");

        if (!input->GetValue().empty() && Utils::isValidTime(value))
        {
            std::string defaultTime = value;
            std::string defaultSelectedTime = value;
            if (is12hour == true)
            {
                defaultTime = Utils::defaultTimeto12hour(defaultTime);
                defaultSelectedTime = Utils::defaultTimeto24hour(defaultSelectedTime);
            }
            else
            {
                defaultTime = defaultSelectedTime = Utils::defaultTimeto24hour(defaultTime);
            }
            uiTimeInput->Property("text", defaultTime, true);
            uiTimeInput->Property("property string selectedTime", defaultSelectedTime, true);
        }

        if (!input->GetIsVisible())
        {
            uiTimeInput->Property("visible", "false");
        }

        //TODO: Height Property
        // Time Format: hh:mm tt -> 03:30 AM or hh:mm -> 15:30
        std::string listViewHours_id = id + "_hours";
        std::string listViewMin_id = id + "_min";
        std::string listViewtt_id = id + "_tt";
        std::string timePopup_id = id + "_timeBox";

        uiTimeInput->Property("onFocusChanged", Formatter() << "{ if (focus===true) inputMask=\"xx:xx;-\";"
            << " if(focus===false){ " << "if(text===\":\") { inputMask=\"\" }" << "}}");

        uiTimeInput->Property("onTextChanged", Formatter() << "{" << listViewHours_id << ".currentIndex=parseInt(getText(0,2));" << listViewMin_id << ".currentIndex=parseInt(getText(3,5));" << "if(getText(0,2) === '--' || getText(3,5) === '--'){" << id << ".selectedTime ='';} else{" << id << ".selectedTime =" << id << ".text;}}");

        uiTimeInput->Property("onActiveFocusChanged",
            Formatter() << "{"
            << "if(activeFocus){\n"
            << "onTextChanged()\n"
            << "}\n}");

        uiTimeInput->Property("activeFocusOnTab", "true");

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        //TODO: These color styling should come from css
        //TODO: Add hover effect
        backgroundTag->Property("color", "'transparent'");
        uiTimeInput->Property("background", backgroundTag->ToString());

        // Icons
        auto timeIcon = GetClearIconButton(context);
        auto clearIcon = GetClearIconButton(context);

        timeIcon->RemoveProperty("anchors.right");
        timeIcon->RemoveProperty("anchors.margins");
        timeIcon->RemoveProperty("anchors.verticalCenter");
        timeIcon->Property("id", Formatter() << id << "_icon");
        timeIcon->Property("Layout.leftMargin", Formatter() << timeConfig.timeIconHorizontalPadding);
        timeIcon->Property("focusPolicy", "Qt.NoFocus");
        timeIcon->Property("width", "18");
        timeIcon->Property("height", "18");
        timeIcon->Property("icon.color", Formatter() << uiTimeComboBox->GetId() << ".activeFocus ? " << context->GetHexColor(timeConfig.timeIconColorOnFocus) << " : " << context->GetHexColor(timeConfig.timeIconColorNormal));
        timeIcon->Property("icon.source", RendererQml::clock_icon, true);
        timeIcon->Property("onClicked", Formatter() << "{" << id << ".forceActiveFocus();\n" << timePopup_id << ".open();\n" << listViewHours_id << ".currentIndex=parseInt(" << id << ".getText(0,2));\n" << listViewMin_id << ".currentIndex=parseInt(" << id << ".getText(3,5));\n" << "}");

        clearIcon->RemoveProperty("anchors.right");
        clearIcon->RemoveProperty("anchors.margins");
        clearIcon->RemoveProperty("anchors.verticalCenter");
        clearIcon->Property("id", Formatter() << id << "_clear_icon");
        clearIcon->Property("Layout.rightMargin", Formatter() << timeConfig.clearIconHorizontalPadding);
        std::string clearIcon_visible_value = Formatter() << "(!" << id << ".focus && " << id << ".text !==\"\") || (" << id << ".focus && " << id << ".text !== " << (is12hour ? "\": \"" : "\":\"") << ")";
        clearIcon->Property("visible", clearIcon_visible_value);

        std::string clearIcon_OnClicked_value = Formatter() << " { "
            << "nextItemInFocusChain().forceActiveFocus();\n"
            << id << ".clear();\n"
            << timePopup_id << ".close();\n"
            << "}";
        clearIcon->Property("onClicked", clearIcon_OnClicked_value);

        //Popup that contains the hours and min ListViews
        auto PopupBgrTag = std::make_shared<QmlTag>("Rectangle");
        PopupBgrTag->Property("anchors.fill", "parent");
        //TODO: Finalize color for popup
        PopupBgrTag->Property("border.color", context->GetHexColor(timeConfig.timePickerBorderColor));
        PopupBgrTag->Property("radius", Formatter() << timeConfig.timePickerBorderRadius);
        PopupBgrTag->Property("color", context->GetHexColor(timeConfig.timePickerBackgroundColor));

        auto timePopupTag = std::make_shared<QmlTag>("Popup");
        timePopupTag->Property("id", timePopup_id);
        timePopupTag->Property("width", Formatter() << timeConfig.timePickerWidth24Hour);
        timePopupTag->Property("height", Formatter() << timeConfig.timePickerHeight);
        timePopupTag->Property("y", Formatter() << id << ".height + 2");
        timePopupTag->Property("x", Formatter() << "-" << timeIcon->GetId() << ".width - " << timeConfig.clearIconHorizontalPadding);
        timePopupTag->Property("background", PopupBgrTag->ToString());
        timePopupTag->Property("onOpened", Formatter() << listViewHours_id << ".forceActiveFocus()");
        timePopupTag->Property("onClosed", Formatter() << "{\n"
            << "var x = String(" << listViewHours_id << ".currentIndex).padStart(2, '0');\n"
            << "var y = String(" << listViewMin_id << ".currentIndex).padStart(2, '0');\n"
            << id << ".insert(0, x);\n"
            << id << ".insert(2, y);\n"
            << id << ".forceActiveFocus();\n"
            << "}");

        auto timeBoxTag = std::make_shared<QmlTag>("Rectangle");
        timeBoxTag->Property("anchors.fill", "parent");
        timeBoxTag->Property("color", "'transparent'");

        auto timeBoxRow = std::make_shared<QmlTag>("RowLayout");
        timeBoxRow->Property("width", "parent.width");
        timeBoxRow->Property("height", "parent.height");
        timeBoxRow->Property("spacing", Formatter() << timeConfig.timePickerColumnSpacing);

        //ListView for DropDown Selection
        std::map<std::string, std::map<std::string, std::string>> ListViewHoursProperties;
        std::map<std::string, std::map<std::string, std::string>> ListViewMinProperties;
        std::map<std::string, std::map<std::string, std::string>> ListViewttProperties;
        std::shared_ptr<QmlTag> listViewttTag;
        int hoursRange = 24;

        if (is12hour == true)
        {
            timePopupTag->Property("width", Formatter() << timeConfig.timePickerWidth12Hour);
            uiTimeInput->Property("validator", "RegExpValidator { regExp: /^(--|[01]-|0\\d|1[0-2]):(--|[0-5]-|[0-5]\\d)\\s(--|A-|AM|P-|PM)$/}");
            uiTimeInput->Property("onFocusChanged", Formatter() << "{ if (focus===true) inputMask=\"xx:xx >xx;-\";" <<
                " if(focus===false){ " << "if(text===\": \" ) { inputMask=\"\" }" << "}}");
            uiTimeInput->Property("onTextChanged", Formatter() << "{" << listViewHours_id << ".currentIndex=parseInt(getText(0,2))-1;" << listViewMin_id << ".currentIndex=parseInt(getText(3,5));"
                << "var tt_index=-1;var hh = getText(0,2);" << "switch(getText(6,8)){ case 'PM':tt_index = 1; if(parseInt(getText(0,2))!==12){hh=parseInt(getText(0,2))+12;} break;case 'AM':tt_index = 0; if(parseInt(getText(0,2))===12){hh=parseInt(getText(0,2))-12;} break;}" << listViewtt_id << ".currentIndex=tt_index;" << "if(getText(0,2) === '--' || getText(3,5) === '--' || getText(6,8) === '--'){" << id << ".selectedTime ='';} else{" << id << ".selectedTime = (hh === 0 ? '00' : hh) + ':' + getText(3,5);}}");
            timeIcon->Property("onClicked", Formatter() << "{" << id << ".forceActiveFocus();\n" << timePopup_id << ".open();\n" << listViewHours_id << ".currentIndex=parseInt(" << id << ".getText(0,2))-1;\n" << listViewMin_id << ".currentIndex=parseInt(" << id << ".getText(3,5));\n"
                << "var tt_index=-1;" << "switch(" << id << ".getText(6,8)){ case 'PM':tt_index = 1; break;case 'AM':tt_index = 0; break;}" << listViewtt_id << ".currentIndex=tt_index;" << "}");


            ListViewHoursProperties["Text"].insert(std::pair<std::string, std::string>("text", "String(index+1).padStart(2, '0')"));
            ListViewHoursProperties["MouseArea"].insert(std::pair<std::string, std::string>("onClicked", Formatter() << "{ forceActiveFocus();" << listViewHours_id << ".currentIndex=index;" << "var x=String(index+1).padStart(2, '0') ;" << id << ".insert(0,x);" << "}"));

            hoursRange = 12;

            ListViewttProperties["ListView"].insert(std::pair<std::string, std::string>("model", "ListModel{ListElement { name: \"AM\"} ListElement { name: \"PM\"}}"));
            ListViewttProperties["Text"].insert(std::pair<std::string, std::string>("text", "model.name"));
            ListViewttProperties["MouseArea"].insert(std::pair<std::string, std::string>("onClicked", Formatter() << "{ forceActiveFocus(); " << listViewtt_id << ".currentIndex=index;" << id << ".insert(6,model.name);" << "}"));
            ListViewttProperties["Text"].insert(std::pair<std::string, std::string>("KeyNavigation.left", listViewMin_id));
            ListViewttProperties["ListView"].insert(std::pair<std::string, std::string>("Keys.onReturnPressed", Formatter() << timePopup_id << ".close()"));
            ListViewttProperties["ListView"].insert(std::pair<std::string, std::string>("Layout.rightMargin", Formatter() << timeConfig.timePickerColumnSpacing));

            listViewttTag = AdaptiveCardQmlRenderer::ListViewTagforTimeInput(id, listViewtt_id, ListViewttProperties, true, context);

            ListViewMinProperties["ListView"].insert(std::pair<std::string, std::string>("KeyNavigation.right", listViewtt_id));
            timePopupTag->Property("onClosed", Formatter() << "{\n"
                << "var x = String(" << listViewHours_id << ".currentIndex + 1).padStart(2, '0');\n"
                << "var y = String(" << listViewMin_id << ".currentIndex).padStart(2, '0');\n"
                << "var z = (" << listViewtt_id << ".currentIndex === -1) ? '--' :  " << listViewtt_id << ".currentIndex === 0 ? 'AM' : 'PM';\n"
                << id << ".insert(0, x);\n"
                << id << ".insert(2, y);\n"
                << id << ".insert(6, z);\n"
                << id << ".forceActiveFocus();\n"
                << "}");
        }
        ListViewHoursProperties["ListView"].insert(std::pair<std::string, std::string>("Layout.leftMargin", Formatter() << timeConfig.timePickerColumnSpacing));
        ListViewHoursProperties["ListView"].insert(std::pair<std::string, std::string>("model", std::to_string(hoursRange)));
        ListViewHoursProperties["MouseArea"].insert(std::pair<std::string, std::string>("onClicked", Formatter() << "{ forceActiveFocus();" << listViewHours_id << ".currentIndex=index;" << "var x=String(index).padStart(2, '0') ;" << id << ".insert(0,x);" << "}"));
        ListViewHoursProperties["ListView"].insert(std::pair<std::string, std::string>("KeyNavigation.right", listViewMin_id));
        ListViewHoursProperties["ListView"].insert(std::pair<std::string, std::string>("Keys.onReturnPressed", Formatter() << timePopup_id << ".close()"));

        auto ListViewHoursTag = AdaptiveCardQmlRenderer::ListViewTagforTimeInput(id, listViewHours_id, ListViewHoursProperties, false, context);

        ListViewMinProperties["ListView"].insert(std::pair<std::string, std::string>("model", "60"));
        ListViewMinProperties["MouseArea"].insert(std::pair<std::string, std::string>("onClicked", Formatter() << "{ forceActiveFocus();" << listViewMin_id << ".currentIndex=index;" << "var x=String(index).padStart(2, '0') ;" << id << ".insert(2,x);" << "}"));
        ListViewMinProperties["ListView"].insert(std::pair<std::string, std::string>("KeyNavigation.left", listViewHours_id));
        ListViewMinProperties["ListView"].insert(std::pair<std::string, std::string>("Keys.onReturnPressed", Formatter() << timePopup_id << ".close()"));
        if (is12hour == false)
        {
            ListViewMinProperties["ListView"].insert(std::pair<std::string, std::string>("Layout.rightMargin", Formatter() << timeConfig.timePickerColumnSpacing));
        }

        auto ListViewMinTag = AdaptiveCardQmlRenderer::ListViewTagforTimeInput(id, listViewMin_id, ListViewMinProperties, false, context);

        uiTimeComboBox->Property("Layout.fillWidth", "true");
        uiTimeComboBox->Property("Keys.onReturnPressed", Formatter() << timePopup_id << ".open()");
        uiTimeComboBox->Property("focusPolicy", "Qt.NoFocus");
        uiTimeComboBox->Property("onActiveFocusChanged", Formatter() << uiTimeInputWrapper->GetId() << ".colorChange(false)");

        timeBoxTag->AddChild(timeBoxRow);

        timeBoxRow->AddChild(ListViewHoursTag);
        timeBoxRow->AddChild(ListViewMinTag);
        if (is12hour)
        {
            timeBoxRow->AddChild(listViewttTag);
        }
        timePopupTag->Property("contentItem", timeBoxTag->ToString());
        uiTimeComboBox->Property("indicator", "Rectangle{}");
        uiTimeComboBox->Property("popup", timePopupTag->ToString());
        uiTimeComboBox->Property("background", uiTimeInput->ToString());
        uiTimeInputRow->AddChild(timeIcon);
        uiTimeInputRow->AddChild(uiTimeComboBox);
        uiTimeInputRow->AddChild(clearIcon);
        uiTimeInputWrapper->AddChild(uiTimeInputRow);

        context->addToInputElementList(origionalElementId, (uiTimeInput->GetId() + ".selectedTime"));

        return uiTimeInputWrapper;
	}

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ListViewTagforTimeInput(const std::string& parent_id, const std::string& listView_id, std::map<std::string, std::map<std::string, std::string>>& properties, bool isThirdTag, std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto timeConfig = context->GetRenderConfig()->getInputTimeConfig();
        auto ListViewTag = std::make_shared<QmlTag>("ListView");
        ListViewTag->Property("id", listView_id);

        //TODO:Avoid fixed values inside ListView
        ListViewTag->Property("width", Formatter() << timeConfig.timePickerHoursAndMinutesTagWidth);
        ListViewTag->Property("height", Formatter() << "parent.height-" << timeConfig.timePickerMargins);
        ListViewTag->Property("spacing", Formatter() << timeConfig.timePickerSpacing);
        ListViewTag->Property("flickableDirection", "Flickable.VerticalFlick");
        ListViewTag->Property("boundsBehavior", "Flickable.StopAtBounds");
        ListViewTag->Property("clip", "true");


        //Elements inside delegate: Rectangle{ Text{} MouseArea{} }
        std::string MouseArea_id = listView_id + "mouseArea";
        auto MouseAreaTag = std::make_shared<QmlTag>("MouseArea");
        MouseAreaTag->Property("id", MouseArea_id);
        MouseAreaTag->Property("anchors.fill", "parent");
        MouseAreaTag->Property("enabled", "true");
        MouseAreaTag->Property("hoverEnabled", "true");
        MouseAreaTag->Property("onClicked", Formatter() << "{" << listView_id << ".currentIndex=index;" << "var x=String(index).padStart(2, '0') ;" << parent_id << ".insert(0,x);" << "}");

        auto TextTag = std::make_shared<QmlTag>("Text");
        TextTag->Property("text", "String(index).padStart(2, '0')");
        TextTag->Property("anchors.fill", "parent");
        TextTag->Property("horizontalAlignment", "Text.AlignHCenter");
        TextTag->Property("verticalAlignment", "Text.AlignVCenter");
        TextTag->Property("font.pixelSize", Formatter() << timeConfig.pixelSize);
        TextTag->Property("color", Formatter() << listView_id << ".currentIndex==index ? " << context->GetHexColor(timeConfig.timePickerElementTextColorOnHighlighted) << " : " << context->GetHexColor(timeConfig.timePickerElementTextColorNormal));

        auto delegateRectTag = std::make_shared<QmlTag>("Rectangle");
        delegateRectTag->Property("width", Formatter() << timeConfig.timePickerHoursAndMinutesTagWidth);
        delegateRectTag->Property("height", Formatter() << timeConfig.timePickerElementHeight);
        delegateRectTag->Property("radius", Formatter() << timeConfig.timePickerElementRadius);
        delegateRectTag->Property("color", Formatter() << listView_id << ".currentIndex==index ? " << context->GetHexColor(timeConfig.timePickerElementColorOnFocus) << " : " << MouseArea_id << ".containsMouse? " << context->GetHexColor(timeConfig.timePickerElementColorOnHover) << " : " << context->GetHexColor(timeConfig.timePickerElementColorNormal));

        if (isThirdTag)
        {
            delegateRectTag->Property("width", Formatter() << timeConfig.timePickerAMPMTagWidth);
            ListViewTag->Property("width", Formatter() << timeConfig.timePickerAMPMTagWidth);
        }

        std::map<std::string, std::map<std::string, std::string>>::iterator outer_iterator;
        std::map<std::string, std::string>::iterator inner_iterator;

        for (outer_iterator = properties.begin(); outer_iterator != properties.end(); outer_iterator++)
        {
            std::shared_ptr<QmlTag> propertyTag;

            if (outer_iterator->first.compare("ListView") == 0)
            {
                propertyTag = ListViewTag;
            }

            else if (outer_iterator->first.compare("MouseArea") == 0)
            {
                propertyTag = MouseAreaTag;
            }

            else if (outer_iterator->first.compare("Text") == 0)
            {
                propertyTag = TextTag;
            }

            for (inner_iterator = outer_iterator->second.begin(); inner_iterator != outer_iterator->second.end(); inner_iterator++)
            {
                propertyTag->Property(inner_iterator->first, inner_iterator->second);
            }
        }

        delegateRectTag->AddChild(MouseAreaTag);
        delegateRectTag->AddChild(TextTag);

        ListViewTag->Property("delegate", delegateRectTag->ToString());

        return ListViewTag;
    }

	std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::ImageSetRender(std::shared_ptr<AdaptiveCards::ImageSet> imageSet, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto uiFlow = std::make_shared<QmlTag>("Flow");

		uiFlow->Property("width", "parent.width");
		uiFlow->Property("spacing", "10");

		if (!imageSet->GetId().empty())
		{
			imageSet->SetId(context->ConvertToValidId(imageSet->GetId()));
			uiFlow->Property("id", imageSet->GetId());
		}

		if (!imageSet->GetIsVisible())
		{
			uiFlow->Property("visible", "false");
		}

		for (auto& image : imageSet->GetImages())
		{
			if (imageSet->GetImageSize() != AdaptiveCards::ImageSize::None)
			{
				image->SetImageSize(imageSet->GetImageSize());
			}
			else if (image->GetImageSize() != AdaptiveCards::ImageSize::None)
			{
				image->SetImageSize(image->GetImageSize());
			}

			uiFlow->AddChild(context->Render(image));
		}

		return uiFlow;
	}

	void AdaptiveCardQmlRenderer::AddSeparator(std::shared_ptr<QmlTag> uiContainer, std::shared_ptr<AdaptiveCards::BaseCardElement> adaptiveElement, std::shared_ptr<AdaptiveRenderContext> context, const bool isShowCard, const std::string loaderId)
	{
		//Returns only when seperator=false and spacing=none
		if (!adaptiveElement->GetSeparator() && adaptiveElement->GetSpacing() == AdaptiveCards::Spacing::None)
		{
			return;
		}

		int spacing = Utils::GetSpacing(context->GetConfig()->GetSpacing(), adaptiveElement->GetSpacing());

		AdaptiveCards::SeparatorConfig separator = context->GetConfig()->GetSeparator();

		auto uiSep = std::make_shared<QmlTag>("Rectangle");
		uiSep->Property("readonly property bool seperator","true");
		if (adaptiveElement->GetElementTypeString() == "Column")
		{
			uiSep->Property("width", std::to_string(spacing == 0 ? separator.lineThickness : spacing));
			uiSep->Property("height", "parent.height");
		}
		else
		{
			uiSep->Property("width", "parent.width");
			uiSep->Property("height", std::to_string(spacing == 0 ? separator.lineThickness : spacing));
		}

		uiSep->Property("color", "\"transparent\"");
		uiSep->Property("visible", adaptiveElement->GetIsVisible() ? "true" : "false");

		if (isShowCard)
		{
			uiSep->Property("visible", Formatter() << loaderId << ".visible" );
		}

		if (adaptiveElement->GetSeparator() && adaptiveElement->GetIsVisible())
		{
			auto uiLine = std::make_shared<QmlTag>("Rectangle");

			if (adaptiveElement->GetElementTypeString() == "Column")
			{
				uiLine->Property("width", std::to_string(separator.lineThickness));
				uiLine->Property("height", "parent.height");
			}
			else
			{
				uiLine->Property("width", "parent.width");
				uiLine->Property("height", std::to_string(separator.lineThickness));
			}

			uiLine->Property("anchors.centerIn", "parent");
			uiLine->Property("color", separator.lineColor, true);

			uiSep->AddChild(uiLine);
		}

		uiContainer->AddChild(uiSep);
	}

	std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::ColumnSetRender(std::shared_ptr<AdaptiveCards::ColumnSet> columnSet, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const int margin = context->GetConfig()->GetSpacing().paddingSpacing;
		const int spacing = Utils::GetSpacing(context->GetConfig()->GetSpacing(), columnSet->GetSpacing());

		int marginReleased = 2*margin;

		const auto bleedLeft = int(AdaptiveCards::ContainerBleedDirection::BleedLeft);
		const auto bleedRight = int(AdaptiveCards::ContainerBleedDirection::BleedRight);

		if (columnSet->GetId().empty())
		{
			columnSet->SetId(Formatter() << "columnSet_auto_" << context->getColumnSetCounter());
		}
		else
		{
			columnSet->SetId(context->ConvertToValidId(columnSet->GetId()));
		}

		const auto id = columnSet->GetId();

		std::shared_ptr<QmlTag> uiFrame;
		std::shared_ptr<QmlTag> uiRowLayout;
		std::shared_ptr<QmlTag> uiRow;

		uiFrame = std::make_shared<QmlTag>("Frame");
		uiRowLayout = std::make_shared<QmlTag>("RowLayout");
		uiRow = std::make_shared<QmlTag>("Row");

		uiFrame->AddChild(uiRowLayout);
		uiRowLayout->AddChild(uiRow);

		if (columnSet->GetPadding())
		{
			uiRow->Property("Layout.topMargin", std::to_string(margin));
			uiRow->Property("Layout.bottomMargin", std::to_string(margin));
			uiRow->Property("Layout.leftMargin", std::to_string(margin));
			uiRow->Property("Layout.rightMargin", std::to_string(margin));
		}
		else
		{
			marginReleased -= (2 * margin);
		}

		switch (columnSet->GetHorizontalAlignment())
		{
			case AdaptiveCards::HorizontalAlignment::Right:
				uiRow->Property("Layout.alignment", "Qt.AlignRight");
				break;
			case AdaptiveCards::HorizontalAlignment::Center:
				uiRow->Property("Layout.alignment", "Qt.AlignHCenter");
				break;
			default:
				uiRow->Property("Layout.alignment", "Qt.AlignLeft");
				break;
		}

		uiFrame->Property("property int minHeight", std::to_string(columnSet->GetMinHeight()));
        uiFrame->Property("readonly property string bgColor", "'transparent'");

		uiFrame->Property("id", id);

		if (!columnSet->GetIsVisible())
		{
			uiFrame->Property("visible", "false");
		}

		uiRowLayout->Property("id", "rlayout_" + id);
		uiRow->Property("id", "row_" + id);

		uiRowLayout->Property("width", "parent.width");

		uiFrame->Property("implicitHeight", "getColumnSetHeight()");

		uiFrame->Property("padding", "0");

        auto backgroundRect = std::make_shared<QmlTag>("Rectangle");
        backgroundRect->Property("id", Formatter() << id << "_bgRect");

		if (columnSet->GetStyle() != AdaptiveCards::ContainerStyle::None)
		{
			const auto color = context->GetConfig()->GetBackgroundColor(columnSet->GetStyle());
            uiFrame->Property("readonly property string bgColor", color, true);
            backgroundRect->Property("border.width", "0");
		}
		else
		{
            backgroundRect->Property("border.width", "0");
		}
        backgroundRect->Property("color", "parent.bgColor");

        addSelectAction(uiFrame, backgroundRect->GetId(), columnSet->GetSelectAction(), context);
        uiFrame->Property("background", backgroundRect->ToString());

		uiFrame = addColumnSetElements(columnSet, uiFrame, context);

		for (int i = 0; i < uiRow->GetChildren().size(); i++)
		{
			auto uiElement = uiRow->GetChildren()[i];

			if (uiElement->HasProperty("readonly property int bleed"))
			{
				int bleedDirection = std::stoi(uiElement->GetProperty("readonly property int bleed"));

				if ((bleedDirection & bleedLeft) == bleedLeft)
				{
					marginReleased -= margin;
				}

				if ((bleedDirection & bleedRight) == bleedRight)
				{
					marginReleased -= margin;
				}
			}
		}

		if (columnSet->GetBleed() && columnSet->GetCanBleed() ||  uiFrame->HasProperty("readonly property int bleed"))
		{
			uiFrame = applyHorizontalBleed(columnSet, uiFrame, context);

			int bleedDirection = int(columnSet->GetBleedDirection());

			if ((bleedDirection & bleedLeft) == bleedLeft)
			{
				marginReleased -=  margin;
			}

			if ((bleedDirection & bleedRight) == bleedRight)
			{
				marginReleased -= margin;
			}
		}
		else
		{
			uiFrame->Property("width", "parent.width");
		}

		uiFrame->Property("onWidthChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchWidth( row_" << id << ".children, parent.width - (" << marginReleased << "))}");

		return uiFrame;
	}

	std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::ColumnRender(std::shared_ptr<AdaptiveCards::Column> column, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const auto margin = context->GetConfig()->GetSpacing().paddingSpacing;
		const auto width = column->GetWidth();

		if (column->GetId().empty())
		{
			column->SetId(Formatter() << "column_auto_" << context->getColumnCounter());
		}
		else
		{
			column->SetId(context->ConvertToValidId(column->GetId()));
		}

		std::shared_ptr<QmlTag> uiContainer = GetNewContainer(column, context);

		if (!column->GetWidth().empty())
		{
			uiContainer->Property("property string widthProperty", Formatter() << "'" << column->GetWidth() << "'");
		}
		else
		{
			uiContainer->Property("property string widthProperty", "'stretch'");
		}

		if (!column->GetIsVisible())
		{
			uiContainer->Property("visible", "false");
		}

		return uiContainer;
	}

    std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::ContainerRender(std::shared_ptr<AdaptiveCards::Container> container, std::shared_ptr<AdaptiveRenderContext> context)
    {
        const auto margin = context->GetConfig()->GetSpacing().paddingSpacing;

        if (container->GetId().empty())
        {
            container->SetId(Formatter() << "container_auto_" << context->getContainerCounter());
        }
        else
        {
            container->SetId(context->ConvertToValidId(container->GetId()));
        }

        std::shared_ptr<QmlTag> uiContainer = GetNewContainer(container, context);

		uiContainer->Property("id", container->GetId());

		if (!container->GetIsVisible())
		{
			uiContainer->Property("visible", "false");
		}

        if (container->GetBleed() && container->GetCanBleed() || uiContainer->HasProperty("readonly property int bleed"))
        {
			uiContainer = applyHorizontalBleed(container, uiContainer,context);
        }
        else
        {
            uiContainer->Property("width", "parent.width");
        }

        return uiContainer;
    }

    template<typename CardElement>
    std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::GetNewColumn(CardElement cardElement, std::shared_ptr<AdaptiveRenderContext> context)
    {
        const auto spacing = Utils::GetSpacing(context->GetConfig()->GetSpacing(), cardElement->GetSpacing());

        std::shared_ptr<QmlTag> uiColumn = std::make_shared<QmlTag>("Column");

        uiColumn->Property("Layout.fillWidth", "true");
		uiColumn->Property("Layout.minimumHeight", "1");

        if (cardElement->GetVerticalContentAlignment() == AdaptiveCards::VerticalContentAlignment::Top)
        {
            uiColumn->Property("Layout.alignment", "Qt.AlignTop");
        }
        else if (cardElement->GetVerticalContentAlignment() == AdaptiveCards::VerticalContentAlignment::Bottom)
        {
            uiColumn->Property("Layout.alignment", "Qt.AlignBottom");
        }

        return uiColumn;
    }

    template<typename CardElement>
    inline std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::GetNewContainer(CardElement cardElement, std::shared_ptr<AdaptiveRenderContext> context)
    {
        const auto id = cardElement->GetId();
        const auto margin = context->GetConfig()->GetSpacing().paddingSpacing;
		const auto bodySize = cardElement->GetItems().size();

        std::shared_ptr<QmlTag> uiContainer;
        std::shared_ptr<QmlTag> uiColumnLayout;
        std::shared_ptr<QmlTag> uiColumn = GetNewColumn(cardElement, context);

        uiContainer = std::make_shared<QmlTag>("Frame");
        uiColumnLayout = std::make_shared<QmlTag>("ColumnLayout");
        uiContainer->AddChild(uiColumnLayout);

        uiContainer->Property("id", id);
        uiColumnLayout->Property("id", "clayout_" + id);
        uiColumn->Property("id", "column_" + id);

        uiColumnLayout->Property("anchors.fill", "parent");

        uiContainer->Property("padding", "0");
        uiContainer->Property("property int minHeight", Formatter() << cardElement->GetMinHeight());
        uiContainer->Property("implicitHeight", Formatter() << "Math.max(" << cardElement->GetMinHeight() << ", clayout_" << cardElement->GetId() << ".implicitHeight)");
        uiContainer->Property("readonly property string bgColor", "'transparent'");

        AddContainerElements(uiColumn, cardElement->GetItems(), context);

        uiColumnLayout->AddChild(uiColumn);

        auto backgroundRect = std::make_shared<QmlTag>("Rectangle");
        backgroundRect->Property("id", Formatter() << id << "_bgRect");
		backgroundRect->Property("clip", "true");

        const auto hasBackgroundImage = cardElement->GetBackgroundImage() != nullptr;
        if (hasBackgroundImage)
        {
            uiContainer->Property("readonly property bool hasBackgroundImage", "true");
            uiContainer->Property("property var imgSource", cardElement->GetBackgroundImage()->GetUrl(), true);
			auto backgroundImg = AdaptiveCardQmlRenderer::GetBackgroundImage(cardElement->GetBackgroundImage(), context, id + ".imgSource");
            backgroundRect->AddChild(backgroundImg);
        }
        else if (cardElement->GetStyle() != AdaptiveCards::ContainerStyle::None)
        {
            const auto color = context->GetConfig()->GetBackgroundColor(cardElement->GetStyle());
            uiContainer->Property("readonly property string bgColor", color, true);
            backgroundRect->Property("border.width", "0");
        }
        else
        {
            backgroundRect->Property("border.width", "0");
        }
        backgroundRect->Property("color", "parent.bgColor");

        addSelectAction(uiContainer, backgroundRect->GetId(), cardElement->GetSelectAction(), context, hasBackgroundImage);
        uiContainer->Property("background", backgroundRect->ToString());

        int tempMargin = 0;
		int tempWidth = 0;
        bool inheritsStyleFromParent = (cardElement->GetStyle() == AdaptiveCards::ContainerStyle::None);
        if (cardElement->GetPadding() && !inheritsStyleFromParent)
        {
			uiColumn->Property("Layout.topMargin", std::to_string(margin));
			uiColumn->Property("Layout.bottomMargin", std::to_string(margin));
			uiColumn->Property("Layout.leftMargin", std::to_string(margin));
			uiColumn->Property("Layout.rightMargin", std::to_string(margin));
            tempWidth = margin;
        }

		uiColumn = applyVerticalBleed(uiColumn, uiColumn);

		if (uiColumn->HasProperty("readonly property int bleed"))
		{
			const auto bleedProperty = uiColumn->GetProperty("readonly property int bleed");
			uiContainer->Property("readonly property int bleed", bleedProperty);
			uiColumn->RemoveProperty("readonly property int bleed");
		}

		if (uiColumn->HasProperty("Layout.topMargin"))
		{
			tempMargin += margin;
		}

		if (uiColumn->HasProperty("Layout.bottomMargin"))
		{
			tempMargin += margin;
		}

		std::string stretchHeight = "";

		if (cardElement->GetElementTypeString() == "Container")
		{
			stretchHeight = Formatter() << "minHeight - " << tempMargin;
			uiContainer->Property("onMinHeightChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight( column_" << id << ".children," << stretchHeight << " )}");
		}
		else if (cardElement->GetElementTypeString() == "Column")
		{
			stretchHeight = Formatter() << "stretchMinHeight - " << tempMargin;
			uiContainer->Property("onStretchMinHeightChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight( column_" << id << ".children," << stretchHeight << " )}");
		}

		uiColumn->Property("onImplicitHeightChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight(children, " << id << "." << stretchHeight << " )}");

		uiColumn->Property("onImplicitWidthChanged", Formatter() << "{" << context->getCardRootId() << ".generateStretchHeight(children, " << id << "." << stretchHeight << " )}");

		uiContainer->Property("property int minWidth", Formatter() << "{" << context->getCardRootId() << ".getMinWidth( column_" << cardElement->GetId() << ".children) + " << 2 * tempWidth << "}");

		if (cardElement->GetElementTypeString() == "Column")
		{
			uiContainer->Property("implicitWidth", "minWidth");
		}

        return uiContainer;
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::MediaRender(std::shared_ptr<AdaptiveCards::Media> media, std::shared_ptr<AdaptiveRenderContext> context)
    {
        return std::make_shared<QmlTag>("Rectangle");
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::ActionSetRender(std::shared_ptr<AdaptiveCards::ActionSet> actionSet, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto outerContainer = std::make_shared<QmlTag>("Column");

		if (actionSet->GetId().empty())
		{
			actionSet->SetId(Formatter() << "actionSet_auto_" << std::to_string(context->GetActionSetCounter()));
		}

		outerContainer->Property("id", actionSet->GetId());
		outerContainer->Property("width", "parent.width");

		if (!actionSet->GetIsVisible())
		{
			outerContainer->Property("visible", "false");
		}

		outerContainer->Property("property int minWidth", Formatter() << "{" << context->getCardRootId() << ".getMinWidthActionSet( children[1].children," << context->GetConfig()->GetActions().buttonSpacing << ")}");

		auto actionsConfig = context->GetConfig()->GetActions();
		const auto oldActionAlignment = context->GetConfig()->GetActions().actionAlignment;

		actionsConfig.actionAlignment = (AdaptiveCards::ActionAlignment) actionSet->GetHorizontalAlignment();
		context->GetConfig()->SetActions(actionsConfig);

		auto isLastActionSet = (context->getLastActionSetInternalId() == actionSet->GetInternalId());
		auto isShowCardInAction = context->isShowCardInAction();
		auto removeBottomMargin = (!isShowCardInAction && isLastActionSet);
		AddActions(outerContainer, actionSet->GetActions(), context, removeBottomMargin);

		actionsConfig.actionAlignment = oldActionAlignment;
		context->GetConfig()->SetActions(actionsConfig);

		return outerContainer;
	}

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::AdaptiveActionRender(std::shared_ptr<AdaptiveCards::BaseActionElement> action, std::shared_ptr<AdaptiveRenderContext> context)
    {
        if (context->GetConfig()->GetSupportsInteractivity())
        {
            const auto config = context->GetConfig();
            const auto actionsConfig = config->GetActions();
            const std::string buttonId = Formatter() << "button_auto_" << context->getButtonCounter();
            const auto fontSize = config->GetFontSize(AdaptiveSharedNamespace::FontType::Default, AdaptiveSharedNamespace::TextSize::Default);
            const bool isShowCardButton = Utils::IsInstanceOfSmart<AdaptiveCards::ShowCardAction>(action);
            const bool isIconLeftOfTitle = actionsConfig.iconPlacement == AdaptiveCards::IconPlacement::LeftOfTitle;

            auto buttonElement = std::make_shared<QmlTag>("Button");
            buttonElement->Property("id", buttonId);
            buttonElement->Property("Keys.onPressed", "{if(event.key === Qt.Key_Return){down=true;event.accepted=true;}}");
            buttonElement->Property("Keys.onReleased", Formatter() << "{if(event.key === Qt.Key_Return){down=false;" << buttonId << ".onReleased();event.accepted=true;}}");

            if (isShowCardButton)
            {
                buttonElement->Property("property bool showCard", "false");
            }

            //Add button background
            auto bgRectangle = std::make_shared<QmlTag>("Rectangle");
			const std::string bgRectangleId = Formatter() << buttonId << "_bg";
            bgRectangle->Property("id", bgRectangleId);
            bgRectangle->Property("anchors.fill", "parent");
            bgRectangle->Property("radius", Formatter() << buttonId << ".height / 2");

            //Add button content item
            auto contentItem = std::make_shared<QmlTag>("Item");
            auto contentLayout = std::make_shared<QmlTag>(isIconLeftOfTitle ? "Row" : "Column");
            contentLayout->Property("id", Formatter() << buttonId << (isIconLeftOfTitle ? "_row" : "_col"));
            contentLayout->Property("spacing", "5");
            contentLayout->Property("leftPadding", "5");
            contentLayout->Property("rightPadding", "5");

            contentItem->AddChild(contentLayout);
            contentItem->Property("implicitHeight", Formatter() << contentLayout->GetId() << ".implicitHeight");
            contentItem->Property("implicitWidth", Formatter() << contentLayout->GetId() << ".implicitWidth");

            //Add button icon
            if (!action->GetIconUrl().empty())
            {
				buttonElement->Property("readonly property bool hasIconUrl", "true");
                buttonElement->Property("property var imgSource", action->GetIconUrl(), true);

                auto contentImage = std::make_shared<QmlTag>("Image");
                contentImage->Property("id", Formatter() << buttonId << "_img");
                contentImage->Property("cache", "false");
                contentImage->Property("height", Formatter() << fontSize);
                contentImage->Property("width", Formatter() << fontSize);
                contentImage->Property("fillMode", "Image.PreserveAspectFit");

                if (isIconLeftOfTitle)
                {
                    contentImage->Property("anchors.verticalCenter", "parent.verticalCenter");
                }
                else
                {
                    contentImage->Property("anchors.horizontalCenter", "parent.horizontalCenter");
                }

                contentImage->Property("source", Formatter() << buttonId << ".imgSource");

                contentLayout->AddChild(contentImage);
            }

            //Add content Text
            auto textLayout = std::make_shared<QmlTag>("Row");
            textLayout->Property("spacing", "5");

			const std::string contentTextId = buttonId + "_contentText";
            auto contentText = std::make_shared<QmlTag>("Text");
			contentText->Property("id", contentTextId);
            if (!action->GetTitle().empty())
            {
                contentText->Property("text", action->GetTitle(), true);
            }
            contentText->Property("font.pixelSize", Formatter() << fontSize);

            ActionButtonColorConfig colorConfig;

            //TODO: Add border color and style: default/positive/destructive
            if (!Utils::IsNullOrWhitespace(action->GetStyle()) && !Utils::CaseInsensitiveCompare(action->GetStyle(), "default"))
            {
                if (Utils::CaseInsensitiveCompare(action->GetStyle(), "positive"))
                {
                    colorConfig = context->GetRenderConfig()->getActionButtonsConfig().positiveColorConfig;
                }
                else if (Utils::CaseInsensitiveCompare(action->GetStyle(), "destructive"))
                {
                    colorConfig = context->GetRenderConfig()->getActionButtonsConfig().destructiveColorConfig;
                }
                else
                {
                    colorConfig = context->GetRenderConfig()->getActionButtonsConfig().primaryColorConfig;
                }
            }
            else
            {
                colorConfig = context->GetRenderConfig()->getActionButtonsConfig().primaryColorConfig;
            }

            bgRectangle->Property("border.width", Formatter() << buttonId << ".activeFocus ? 2 : 1");

            if (isShowCardButton)
            {
                bgRectangle->Property("border.color", Formatter() << buttonId << ".activeFocus ? " << context->GetHexColor(colorConfig.borderColorFocussed) << " : " << context->GetHexColor(colorConfig.borderColorNormal));
                bgRectangle->Property("color", Formatter() << "(" << buttonId << ".showCard || " << buttonId << ".down )? " << context->GetHexColor(colorConfig.buttonColorPressed) << " : (" << buttonId << ".hovered ) ? " << context->GetHexColor(colorConfig.buttonColorHovered) << " : " << context->GetHexColor(colorConfig.buttonColorNormal));
                contentText->Property("color", Formatter() << "( " << buttonId << ".showCard || " << buttonId << ".hovered || " << buttonId << ".down) ? " << context->GetHexColor(colorConfig.textColorHovered) << " : " << context->GetHexColor(colorConfig.textColorNormal));
            }
            else
            {
                bgRectangle->Property("border.color", Formatter() << buttonId << ".activeFocus ? " << context->GetHexColor(colorConfig.borderColorFocussed) << " : " << context->GetHexColor(colorConfig.borderColorNormal));
                bgRectangle->Property("color", Formatter() << buttonId << ".down ? " << context->GetHexColor(colorConfig.buttonColorPressed) << " : (" << buttonId << ".hovered ) ? " << context->GetHexColor(colorConfig.buttonColorHovered) << " : " << context->GetHexColor(colorConfig.buttonColorNormal));
                contentText->Property("color", Formatter() << "( " << buttonId << ".hovered || " << buttonId << ".down )? " << context->GetHexColor(colorConfig.textColorHovered) << " : " << context->GetHexColor(colorConfig.textColorNormal));
            }

            textLayout->AddChild(contentText);
            buttonElement->Property("background", bgRectangle->ToString());

            if (isShowCardButton)
            {
                auto showCardIconBackground = std::make_shared<QmlTag>("Rectangle");
				showCardIconBackground->Property("anchors.fill", "parent");
				showCardIconBackground->Property("color", "'transparent'");

                const std::string iconId = Formatter() << buttonId << "_icon";
				auto showCardIcon = GetIconTag(context);
                showCardIcon->Property("id", iconId);
				showCardIcon->RemoveProperty("anchors.right");
                showCardIcon->RemoveProperty("anchors.top");
				showCardIcon->RemoveProperty("anchors.bottom");
				showCardIcon->Property("width", Formatter() << contentTextId << ".font.pixelSize");
				showCardIcon->Property("height", Formatter() << contentTextId << ".font.pixelSize");
				showCardIcon->Property("anchors.verticalCenter", Formatter() << contentTextId << ".verticalCenter");
				showCardIcon->Property("horizontalPadding", "0");
				showCardIcon->Property("verticalPadding", "0");
				showCardIcon->Property("icon.color", Formatter() << contentTextId << ".color");
				showCardIcon->Property("icon.width", "12");
				showCardIcon->Property("icon.height", "12");
				showCardIcon->Property("icon.source", RendererQml::arrow_down_12, true);
				showCardIcon->Property("background", showCardIconBackground->ToString());
                showCardIcon->Property("onReleased", Formatter() << "{" << buttonId << ".released();" << buttonId << ".forceActiveFocus()}");
                textLayout->AddChild(showCardIcon);
            }

            contentLayout->AddChild(textLayout);
            buttonElement->Property("contentItem", contentItem->ToString());

            std::string onReleasedFunction;
            if (action->GetElementTypeString() == "Action.OpenUrl")
            {
                onReleasedFunction = getActionOpenUrlClickFunc(std::dynamic_pointer_cast<AdaptiveCards::OpenUrlAction>(action), context);
            }
            else if (action->GetElementTypeString() == "Action.ShowCard")
            {
                context->addToShowCardButtonList(buttonElement, std::dynamic_pointer_cast<AdaptiveCards::ShowCardAction>(action));
            }
            else if (action->GetElementTypeString() == "Action.ToggleVisibility")
            {
                onReleasedFunction = getActionToggleVisibilityClickFunc(std::dynamic_pointer_cast<AdaptiveCards::ToggleVisibilityAction>(action), context);
            }
            else if (action->GetElementTypeString() == "Action.Submit")
            {
                context->addToSubmitActionButtonList(buttonElement, std::dynamic_pointer_cast<AdaptiveCards::SubmitAction>(action));
            }
            else
            {
                onReleasedFunction = "";
            }

            buttonElement->Property("onReleased", Formatter() << "{\n" << onReleasedFunction << "}\n");
            return buttonElement;
        }

        return nullptr;
    }

    void AdaptiveCardQmlRenderer::addSubmitActionButtonClickFunc(const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        for (auto& element : context->getSubmitActionButtonList())
        {
            std::string onReleasedFunction;
            const auto buttonElement = element.first;
            const auto action = element.second;

            onReleasedFunction = getActionSubmitClickFunc(action, context);
            buttonElement->Property("onReleased", Formatter() << "{\n" << onReleasedFunction << "}\n");
        }
    }

    void AdaptiveCardQmlRenderer::addShowCardButtonClickFunc(const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        for (auto& element : context->getShowCardButtonList())
        {
            std::string onReleasedFunction;
            const auto buttonElement = element.first;
            const auto action = element.second;

            onReleasedFunction = getActionShowCardClickFunc(buttonElement, context);
            buttonElement->Property("onReleased", Formatter() << "{\n" << onReleasedFunction << "}\n");
        }

        context->clearShowCardButtonList();
    }

    void AdaptiveCardQmlRenderer::addShowCardLoaderComponents(const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        for (const auto& componentElement : context->getShowCardLoaderComponentList())
        {
            auto subContext = std::make_shared<AdaptiveRenderContext>(context->GetConfig(), context->GetElementRenderers(), context->GetRenderConfig());

            // Add parent input input elements to the child card
            for (const auto& inputElement : context->getInputElementList())
            {
                subContext->addToInputElementList(inputElement.first, inputElement.second);
            }

            auto uiCard = subContext->Render(componentElement.second->GetCard(), &AdaptiveCardRender, true);
            if (uiCard != nullptr)
            {
                //TODO: Remove these hardcoded colors once config settings are finalised
                const auto containerColor = context->GetRGBColor(context->GetConfig()->GetBackgroundColor(context->GetConfig()->GetActions().showCard.style));

                uiCard->Property("color", containerColor);

                // Add show card component to root element
                const auto showCardComponent = GetComponent(componentElement.first, uiCard);
                context->getCardRootElement()->AddChild(showCardComponent);
            }
        }
    }

    const std::string AdaptiveCardQmlRenderer::getActionOpenUrlClickFunc(const std::shared_ptr<AdaptiveCards::OpenUrlAction>& action, const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        // Sample signal to emit on click
        //adaptiveCard.buttonClick(var title, var type, var data);
        //adaptiveCard.buttonClick("title", "Action.OpenUrl", "https://adaptivecards.io");
        std::ostringstream function;
        function << context->getCardRootId() << ".buttonClicked(\"" << action->GetTitle() << "\", \"" << action->GetElementTypeString() << "\", \"" << action->GetUrl() << "\");";
        function << "\nconsole.log(\"" << action->GetUrl() << "\");\n";

        return function.str();
    }

	const std::string AdaptiveCardQmlRenderer::getActionShowCardClickFunc(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveRenderContext>& context)
	{
		std::ostringstream function;
		for (auto& element : context->getShowCardButtonList())
		{
			const auto button = element.first;
			const auto action = element.second;

			if (buttonElement->GetId() != button->GetId())
			{
				function << "if(" << button->GetId() << ".showCard)\n{\n";
				function << button->GetId() << ".released()\n}\n";
			}
		}

		function << "\n" << buttonElement->GetId() << ".showCard = !" << buttonElement->GetId() << ".showCard";
		function << "\n" << buttonElement->GetId() << "_loader.visible = " << buttonElement->GetId() << ".showCard";
		function << "\n" << buttonElement->GetId() << "_icon.icon.source = " << buttonElement->GetId() << ".showCard ? " << "\"" << RendererQml::arrow_up_12 << "\"" << ":" << "\"" << RendererQml::arrow_down_12 << "\"";
		return function.str();
	}

	const std::string AdaptiveCardQmlRenderer::getActionSubmitClickFunc(const std::shared_ptr<AdaptiveCards::SubmitAction>& action, const std::shared_ptr<AdaptiveRenderContext>& context)
    {
        // Sample signal to emit on click
        //adaptiveCard.buttonClick(var title, var type, var data);
        //adaptiveCard.buttonClick("title", "Action.Submit", "{"x":13,"firstName":"text1","lastName":"text2"}");
        std::ostringstream function;

        std::string submitDataJson = action->GetDataJson();
        submitDataJson = Utils::Trim(submitDataJson);

        function << "var paramJson = {};\n";

        if (!submitDataJson.empty() && submitDataJson != "null")
        {
            submitDataJson = Utils::Replace(submitDataJson, "\"", "\\\"");
            function << "var parmStr = \"" << submitDataJson << "\";\n";
            function << "paramJson = JSON.parse(parmStr);\n";
        }

        for(const auto& element : context->getInputElementList())
        {
            function << "paramJson[\"" << element.first << "\"] = " << element.second << ";\n";
        }

        function << "var paramslist = JSON.stringify(paramJson);\n";
        function << context->getCardRootId() << ".buttonClicked(\"" << action->GetTitle() << "\", \"" << action->GetElementTypeString() << "\", paramslist);\nconsole.log(paramslist);\n";

        return function.str();
    }

	const std::string AdaptiveCardQmlRenderer::getActionToggleVisibilityClickFunc(const std::shared_ptr<AdaptiveCards::ToggleVisibilityAction>& action, const std::shared_ptr<AdaptiveRenderContext>& context)
	{
		std::ostringstream function;

		for (const auto& targetElement : action->GetTargetElements())
		{
			std::string targetElementId;

			if (targetElement != nullptr)
			{
				targetElementId = context->ConvertToValidId(targetElement->GetElementId());

				switch (targetElement->GetIsVisible())
				{
				case AdaptiveCards::IsVisible::IsVisibleTrue:
					function << targetElementId << ".visible = true";
					break;
				case AdaptiveCards::IsVisible::IsVisibleFalse:
					function << targetElementId << ".visible = false";
					break;
				default:
					function << targetElementId << ".visible = !" << targetElementId << ".visible ";
				}
			}
			function << "\n";
		}

		return function.str();
  }

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetBackgroundImage(std::shared_ptr<AdaptiveCards::BackgroundImage> backgroundImage, std::shared_ptr<AdaptiveRenderContext> context, const std::string& imgSource)
	{
		auto uiImage = std::make_shared<QmlTag>("Image");
        uiImage->Property("cache", "false");
		uiImage->Property("source", imgSource);

		std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(backgroundImage->GetHorizontalAlignment());
		std::string verticalAlignment = AdaptiveCards::EnumHelpers::getVerticalAlignmentEnum().toString(backgroundImage->GetVerticalAlignment());

		switch (backgroundImage->GetFillMode())
		{
		case AdaptiveCards::ImageFillMode::Repeat:
			uiImage->Property("fillMode", "Image.Tile");
			uiImage->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));
			uiImage->Property("verticalAlignment", Utils::GetVerticalAlignment(verticalAlignment));
			uiImage->Property("anchors.fill", "parent");
			break;
		case AdaptiveCards::ImageFillMode::RepeatHorizontally:
			uiImage->Property("width", "parent.width");
			uiImage->Property("height", "implicitHeight");
			uiImage->Property("fillMode", "Image.TileHorizontally");
			uiImage->Property("horizontalAlignment", "Qt.AlignLeft");
			uiImage->Property("anchors." + Utils::GetVerticalAnchors(verticalAlignment), "parent." + Utils::GetVerticalAnchors(verticalAlignment));
			break;
		case AdaptiveCards::ImageFillMode::RepeatVertically:
			uiImage->Property("width", "implicitWidth");
			uiImage->Property("height", "parent.height");
			uiImage->Property("fillMode", "Image.TileVertically");
			uiImage->Property("anchors." + Utils::GetHorizontalAnchors(horizontalAlignment), "parent." + Utils::GetHorizontalAnchors(horizontalAlignment));
			uiImage->Property("verticalAlignment", "Qt.AlignTop");
			break;
		case AdaptiveCards::ImageFillMode::Cover:
		default:
			uiImage->Property("fillMode", "Image.PreserveAspectCrop");
			uiImage->Property("verticalAlignment", Utils::GetVerticalAlignment(verticalAlignment));
			uiImage->Property("anchors.fill", "parent");
			break;
		}

		return uiImage;
	}

	template<typename CardElement>
	const std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::applyHorizontalBleed(CardElement cardElement, std::shared_ptr<QmlTag> uiContainer, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const int margin = context->GetConfig()->GetSpacing().paddingSpacing;
		const auto bleedLeft = int(AdaptiveCards::ContainerBleedDirection::BleedLeft);
		const auto bleedRight = int(AdaptiveCards::ContainerBleedDirection::BleedRight);
		const auto bleedUp = int(AdaptiveCards::ContainerBleedDirection::BleedUp);
		const auto bleedDown = int(AdaptiveCards::ContainerBleedDirection::BleedDown);

		int bleedDirection = int(cardElement->GetBleedDirection());

		if (uiContainer->HasProperty("readonly property int bleed"))
		{
			bleedDirection |= std::stoi(uiContainer->GetProperty("readonly property int bleed"));
		}

		if ((bleedDirection & bleedUp) == bleedUp)
		{
			bleedDirection |= bleedUp;
			uiContainer->Property("readonly property int bleed", std::to_string(bleedDirection));
		}

		if ((bleedDirection & bleedDown) == bleedDown)
		{
			bleedDirection |= bleedDown;
			uiContainer->Property("readonly property int bleed", std::to_string(bleedDirection));
		}

		int marginsAdded = 0;
		if ((bleedDirection & bleedLeft) == bleedLeft)
		{
			marginsAdded += margin;
			uiContainer->Property("x", Formatter() << "-" << std::to_string(margin));
		}

		if ((bleedDirection & bleedRight) == bleedRight)
		{
			marginsAdded += margin;
		}

		uiContainer->Property("width", "parent.width + " + std::to_string(marginsAdded));

		return uiContainer;
	}

	const std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::applyVerticalBleed(std::shared_ptr<QmlTag> elementsParent, std::shared_ptr<QmlTag> source)
	{
		const auto bodySize = elementsParent->GetChildren().size();
		const auto bleedUp = int(AdaptiveCards::ContainerBleedDirection::BleedUp);
		const auto bleedDown = int(AdaptiveCards::ContainerBleedDirection::BleedDown);

		if (bodySize > 0)
		{
			int parentBleed = 0;
			for (int i = 0; i < bodySize; i++)
			{
				if (elementsParent->GetChildren()[i]->HasProperty("readonly property int bleed"))
				{
					const auto bleedDirection = std::stoi(elementsParent->GetChildren()[i]->GetProperty("readonly property int bleed"));

					if ((bleedDirection & bleedUp) == bleedUp && i == 0)
					{
						if (source->HasProperty("Layout.topMargin"))
						{
							source->RemoveProperty("Layout.topMargin");
						}
						else
						{
							parentBleed |= bleedUp;
						}
					}

					if ((bleedDirection & bleedDown) == bleedDown && i == bodySize - 1)
					{
						if (source->HasProperty("Layout.bottomMargin"))
						{
							source->RemoveProperty("Layout.bottomMargin");
						}
						else
						{
							parentBleed |= bleedDown;
						}
					}
				}
			}
			if (parentBleed != 0)
			{
				source->Property("readonly property int bleed", std::to_string(parentBleed));
			}
		}
		return source;
	}

	const std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::addColumnSetElements(std::shared_ptr<AdaptiveCards::ColumnSet> columnSet, std::shared_ptr<QmlTag> uiFrame, std::shared_ptr<AdaptiveRenderContext> context)
	{
		const int margin = context->GetConfig()->GetSpacing().paddingSpacing;
		const int no_of_columns = int(columnSet->GetColumns().size());
		auto columns = columnSet->GetColumns();
		std::string heightString = "";
		int bleedUpCount = 0;
		int bleedDownCount = 0;
		int bleedMargin = 0;
		int tempMargin = 0;
		int maxBleedMargin = 0;
		int minHeight = 0;

		const auto bleedLeft = int(AdaptiveCards::ContainerBleedDirection::BleedLeft);
		const auto bleedRight = int(AdaptiveCards::ContainerBleedDirection::BleedRight);
		const auto bleedUp = int(AdaptiveCards::ContainerBleedDirection::BleedUp);
		const auto bleedDown = int(AdaptiveCards::ContainerBleedDirection::BleedDown);

		std::shared_ptr<QmlTag> uiRowLayout = uiFrame->GetChildren()[0];
		std::shared_ptr<QmlTag> uiRow = uiRowLayout->GetChildren()[0];

		if (columnSet->GetPadding())
		{
			tempMargin = 2 * margin;
		}

		for (int i = 0; i < no_of_columns; i++)
		{
			auto cardElement = columns[i];

			auto uiElement = context->Render(cardElement);

			if (uiElement != nullptr)
			{
				if (!uiRow->GetChildren().empty())
				{
					AddSeparator(uiRow, cardElement, context);
				}

				uiRow->AddChild(uiElement);

				if (cardElement->GetBleed() && cardElement->GetCanBleed() || uiElement->HasProperty("readonly property int bleed"))
				{
					int bleedDirection = 0;

					if (uiElement->HasProperty("readonly property int bleed"))
					{
						bleedDirection |= std::stoi(uiElement->GetProperty("readonly property int bleed"));
					}

					if (cardElement->GetBleed() && cardElement->GetCanBleed())
					{
						bleedDirection |= int(cardElement->GetBleedDirection());
					}

					if ((bleedDirection & bleedLeft) == bleedLeft)
					{
						uiRow->RemoveProperty("Layout.leftMargin");
						if (!columnSet->GetPadding())
						{
							uiRowLayout->Property("x", Formatter() << "-" << margin);
						}
					}

					if ((bleedDirection & bleedRight) == bleedRight)
					{
						uiRow->RemoveProperty("Layout.rightMargin");
					}

					if ((bleedDirection & bleedUp) == bleedUp)
					{
						bleedUpCount++;
					}

					if ((bleedDirection & bleedDown) == bleedDown)
					{
						bleedDownCount++;
					}

					if (bleedDirection != 0)
					{
						uiElement->Property("readonly property int bleed", std::to_string(bleedDirection));
					}
				}

			}
		}

		int parentBleedDirection = 0;

		if (bleedUpCount == no_of_columns)
		{
			if (columnSet->GetPadding())
			{
				uiRow->RemoveProperty("Layout.topMargin");
				tempMargin -= margin;
			}
			else
			{
				parentBleedDirection |= bleedUp;
			}
		}

		if (bleedDownCount == no_of_columns)
		{
			if (columnSet->GetPadding())
			{
				uiRow->RemoveProperty("Layout.bottomMargin");
				tempMargin -= margin;
			}
			else
			{
				parentBleedDirection |= bleedDown;
			}
		}

		minHeight = std::max(minHeight, int(columnSet->GetMinHeight()) - tempMargin);

		auto uiElements = uiRow->GetChildren();

		for (int i = 0; i < uiElements.size(); i++)
		{
			if (!uiElements[i]->HasProperty("readonly property bool seperator"))
			{
				int bleedMargin = 0;
				if (uiElements[i]->HasProperty("readonly property int bleed"))
				{
					int bleedDirection = std::stoi(uiElements[i]->GetProperty("readonly property int bleed"));

					if ((bleedDirection & bleedUp) == bleedUp && bleedUpCount != no_of_columns)
					{
						uiElements[i]->Property("y", Formatter() << "-" << margin);
						bleedMargin += margin;

					}

					if ((bleedDirection & bleedDown) == bleedDown && bleedDownCount != no_of_columns)
					{
						bleedMargin += margin;
					}
				}

				minHeight = std::max(minHeight, std::stoi(uiElements[i]->GetProperty("property int minHeight")) + bleedMargin);

				uiElements[i]->Property("property int stretchMinHeight", Formatter() << "Math.max(" << uiFrame->GetId() << ".stretchMinHeight, implicitHeight - 1)");

				maxBleedMargin = std::max(bleedMargin, maxBleedMargin);
				uiElements[i]->Property("implicitHeight", Formatter() << columnSet->GetId() << ".getColumnHeight( " << uiElements[i]->HasProperty("readonly property int bleed") << " ) + " << bleedMargin);
				heightString += ("clayout_" + uiElements[i]->GetProperty("id") + ".implicitHeight - " + std::to_string(bleedMargin) + "," + uiElements[i]->GetProperty("id") + ".minHeight, ");
			}
			else
			{
				uiElements[i]->Property("height", Formatter() << columnSet->GetId() << ".getColumnHeight(false)");
			}
		}

		if (parentBleedDirection != 0)
		{
			uiFrame->Property("readonly property int bleed", std::to_string(parentBleedDirection));
		}

		uiFrame->Property("property int stretchMinHeight", std::to_string(minHeight));
		uiFrame->Property("onMinHeightChanged", Formatter() << "{ stretchMinHeight = Math.max(minHeight - " << tempMargin << ", stretchMinHeight)}");

		uiFrame->AddFunctions(Formatter() << "function getColumnSetHeight(){ var calculatedHeight = getColumnHeight(true);if(calculatedHeight >= minHeight - (" << (tempMargin) << ")){return calculatedHeight + (" << (tempMargin) << ")}else{return minHeight;}}");

		uiFrame->AddFunctions(Formatter() << "function getColumnHeight(bleed){var calculatedHeight =  Math.max(" << heightString.substr(0, heightString.size() - 2) << "); if(calculatedHeight < minHeight - (" << (tempMargin) << ")){return minHeight - (" << (tempMargin) << ")}else{if(calculatedHeight === 0 && !bleed){return calculatedHeight + " << maxBleedMargin << " }else{return calculatedHeight}}}");

		return uiFrame;
	}

	const std::string RendererQml::AdaptiveCardQmlRenderer::getStretchHeight()
	{
		std::string stretchHeightFunction =  R"(function generateStretchHeight(childrens,minHeight){
			var n = childrens.length
			var implicitHt = 0;
			var stretchCount = 0;
			var stretchMinHeight = 0;
			for(var i=0;i<childrens.length;i++)
			{
				if(typeof childrens[i].seperator !== 'undefined')
				{
					implicitHt += childrens[i].height;
					stretchMinHeight += childrens[i].height;
				}
				else
				{
					implicitHt += childrens[i].implicitHeight;
					if(typeof childrens[i].stretch !== 'undefined')
					{
						stretchCount++;
					}
					else
					{
						stretchMinHeight += childrens[i].implicitHeight;
					}
				}
			}
			stretchMinHeight = (minHeight - stretchMinHeight)/stretchCount
			for(i=0;(i<childrens.length);i++)
			{
				if(typeof childrens[i].seperator === 'undefined')
				{
					if(typeof childrens[i].stretch !== 'undefined' && typeof childrens[i].minHeight !== 'undefined')
					{
						childrens[i].minHeight = Math.max(childrens[i].minHeight,stretchMinHeight)
					}
				}
			}
			if(stretchCount > 0 && implicitHt < minHeight)
			{
				var stretctHeight = (minHeight - implicitHt)/stretchCount
				for(i=0;i<childrens.length;i++)
				{
					if(typeof childrens[i].seperator === 'undefined')
					{
						if(typeof childrens[i].stretch !== 'undefined')
						{
							childrens[i].height = childrens[i].implicitHeight + stretctHeight
						}
					}
				}
			}
			else
			{
				for(i=0;i<childrens.length;i++)
				{
					if(typeof childrens[i].seperator === 'undefined')
					{
						if(typeof childrens[i].stretch !== 'undefined')
						{
							childrens[i].height = childrens[i].implicitHeight
						}
					}
				}
			}
		})";

		stretchHeightFunction.erase(std::remove(stretchHeightFunction.begin(), stretchHeightFunction.end(), '\t'), stretchHeightFunction.end());

		return stretchHeightFunction;
	}

	const std::string RendererQml::AdaptiveCardQmlRenderer::getStretchWidth()
	{
		std::string stretchWidthFunction =  R"(function generateStretchWidth(childrens,width){
			var implicitWid = 0
			var autoWid = 0
			var autoCount = 0
			var weightSum = 0
			var stretchCount = 0
			var weightPresent = 0
			for(var i=0;i<childrens.length;i++)
			{
				if(typeof childrens[i].seperator !== 'undefined')
				{
					implicitWid += childrens[i].width
				}
				else
				{
					if(childrens[i].widthProperty.endsWith("px"))
					{
						childrens[i].width = parseInt(childrens[i].widthProperty.slice(0,-2))
						implicitWid += childrens[i].width
					}
					else
					{
						if(childrens[i].widthProperty === "auto")
						{
							autoCount++
						}
						else if(childrens[i].widthProperty === "stretch")
						{
							stretchCount++
							implicitWid += 50;
						}
						else
						{
							weightPresent = 1
							weightSum += parseInt(childrens[i].widthProperty)
						}
					}
				}
			}
			autoWid = (width - implicitWid)/(weightPresent + autoCount)
			var flags = new Array(childrens.length).fill(0)
			for(i=0;i<childrens.length;i++)
			{
				if(typeof childrens[i].seperator === 'undefined')
				{
					if(childrens[i].widthProperty === "auto")
					{
						if(childrens[i].minWidth < autoWid)
						{
							childrens[i].width = childrens[i].minWidth
							implicitWid += childrens[i].width
							flags[i] = 1;
							autoCount--;
							autoWid = (width - implicitWid)/(weightPresent + autoCount)
						}
					}
				}
			}
			for(i=0;i<childrens.length;i++)
			{
				if(typeof childrens[i].seperator === 'undefined')
				{
					if(childrens[i].widthProperty === "auto")
					{
						if(flags[i] === 0)
						{
							childrens[i].width = autoWid
							implicitWid += childrens[i].width
						}
					}
					else if(childrens[i].widthProperty !== "stretch" && !childrens[i].widthProperty.endsWith("px"))
					{
						if(weightSum !== 0)
						{
							childrens[i].width = ((parseInt(childrens[i].widthProperty)/weightSum) * autoWid)
							implicitWid += childrens[i].width
						}
					}
				}
			}
			var stretchWidth = (width - implicitWid)/stretchCount
			for(i=0;i<childrens.length;i++)
			{
				if(typeof childrens[i].seperator === 'undefined')
				{
					if(childrens[i].widthProperty === 'stretch')
					{
						childrens[i].width = 50+stretchWidth
					}
				}
			}
		})";

		stretchWidthFunction.erase(std::remove(stretchWidthFunction.begin(), stretchWidthFunction.end(), '\t'), stretchWidthFunction.end());

		return stretchWidthFunction;
	}

	const std::string RendererQml::AdaptiveCardQmlRenderer::getMinWidth()
	{
		std::string minWidthFunction =  R"(function getMinWidth(childrens){
			var min = 0
			for(var j =0;j<childrens.length;j++)
			{
				if(typeof childrens[j].minWidth === 'undefined')
				{
					min = Math.max(min,Math.ceil(childrens[j].implicitWidth))
				}
				else
				{
					min = Math.max(min,Math.ceil(childrens[j].minWidth))
				}
			}
			return min
		})";

		minWidthFunction.erase(std::remove(minWidthFunction.begin(), minWidthFunction.end(), '\t'), minWidthFunction.end());

		return minWidthFunction;
	}

	const std::string RendererQml::AdaptiveCardQmlRenderer::getMinWidthActionSet()
	{
		std::string minWidthActionSet =  R"(function getMinWidthActionSet(childrens,spacing){
			var min = 0
			for(var j =0;j<childrens.length;j++)
			{
				min += Math.ceil(childrens[j].implicitWidth)
			}
			min += ((childrens.length - 1)*spacing)
			return min
		})";

		minWidthActionSet.erase(std::remove(minWidthActionSet.begin(), minWidthActionSet.end(), '\t'), minWidthActionSet.end());

		return minWidthActionSet;
	}

	const std::string RendererQml::AdaptiveCardQmlRenderer::getMinWidthFactSet()
	{
		std::string minWidthFactSet =  R"(function getMinWidthFactSet(childrens, spacing){
			var min = 0
			for(var j=0;j<childrens.length;j+=2)
			{
				min = Math.max(min,childrens[j].implicitWidth + childrens[j+1].implicitWidth + spacing)
			}
			return min;
		})";

		minWidthFactSet.erase(std::remove(minWidthFactSet.begin(), minWidthFactSet.end(), '\t'), minWidthFactSet.end());

		return minWidthFactSet;
	}

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetIconTag(std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto iconBackgroundTag = std::make_shared<QmlTag>("Rectangle");
        iconBackgroundTag->Property("color", context->GetRGBColor(context->GetConfig()->GetContainerStyles().defaultPalette.backgroundColor));
        iconBackgroundTag->Property("width", "parent.width");
        iconBackgroundTag->Property("height", "parent.height");

        auto iconTag = std::make_shared<QmlTag>("Button");
        iconTag->Property("background", iconBackgroundTag->ToString());
        iconTag->Property("width", "30");
        iconTag->Property("anchors.top", "parent.top");
        iconTag->Property("anchors.bottom", "parent.bottom");
        iconTag->Property("anchors.right", "parent.right");
        iconTag->Property("anchors.margins", "2");
        iconTag->Property("horizontalPadding", "4");
        iconTag->Property("verticalPadding", "4");
        iconTag->Property("icon.width", "18");
        iconTag->Property("icon.height", "18");
        iconTag->Property("focusPolicy", "Qt.NoFocus");
        iconTag->Property("icon.color", context->GetColor(AdaptiveCards::ForegroundColor::Default, false, false));
        return iconTag;
    }

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::GetTextBlockMouseArea()
	{
		auto MouseAreaTag = std::make_shared<QmlTag>("MouseArea");
		MouseAreaTag->Property("anchors.fill", "parent");
		MouseAreaTag->Property("cursorShape", "parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor");
		MouseAreaTag->Property("acceptedButtons", "Qt.NoButton");

		return MouseAreaTag;
	}

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::getDummyElementforNumberInput(bool isTop)
	{
		auto DummyTag = std::make_shared<QmlTag>("Rectangle");
		DummyTag->Property("width", "2");
		DummyTag->Property("height", "2");
		DummyTag->Property("anchors.right", "parent.right");

		if (isTop)
		{
			DummyTag->Property("anchors.top", "parent.top");
		}
		else
		{
			DummyTag->Property("anchors.bottom", "parent.bottom");
		}
		DummyTag->Property("anchors.margins", "5");
		DummyTag->Property("color", "'transparent'");
		DummyTag->Property("z", "-1");

		return DummyTag;
	}

	void AdaptiveCardQmlRenderer::ValidateLastBodyElementIsShowCard(const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& bodyElements, std::shared_ptr<AdaptiveRenderContext> context)
	{
		if (bodyElements.empty())
		{
			return;
		}
		auto cardElement = bodyElements.back();

		auto cardElementType = cardElement->GetElementType();

		if (cardElementType == AdaptiveSharedNamespace::CardElementType::ActionSet)
		{
			auto ActionSetPtr = std::dynamic_pointer_cast<AdaptiveCards::ActionSet> (cardElement);
			auto listOfActions = ActionSetPtr->GetActions();

			for (const auto& action : listOfActions)
			{
				if (Utils::IsInstanceOfSmart<AdaptiveCards::ShowCardAction>(action))
				{
					context->setLastActionSetInternalId(ActionSetPtr->GetInternalId());
					context->setIsShowCardLastBodyElement(true);
					return;
				}
			}
		}
	}

	void AdaptiveCardQmlRenderer::ValidateShowCardInActions(const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions, std::shared_ptr<AdaptiveRenderContext> context)
	{
		for (const auto& action : actions)
		{
			if (Utils::IsInstanceOfSmart<AdaptiveCards::ShowCardAction>(action))
			{
				context->setIsShowCardInAction(true);
				return;
			}
		}
	}

	const std::string AdaptiveCardQmlRenderer::RemoveBottomMarginValue(std::vector<std::string> showCardsList)
	{
		std::string value = "";

		for (auto id : showCardsList)
		{
			value.append(Formatter() << "(" << id << ".visible && " << id << ".removeBottomMargin) || ");
		}

		if (value == "")
		{
			value = "false";
		}
		else
		{
			value.erase(value.length() - 3);
		}

		return value;
	}

    std::shared_ptr<QmlTag> RendererQml::AdaptiveCardQmlRenderer::GetClearIconButton(std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto iconConfig = context->GetRenderConfig()->getInputTextConfig();

        auto backgroundTag = std::make_shared<QmlTag>("Rectangle");
        backgroundTag->Property("color", "'transparent'");

        auto clearIcon = GetIconTag(context);

        clearIcon->RemoveProperty("anchors.bottom");
        clearIcon->RemoveProperty("anchors.top");
        clearIcon->RemoveProperty("anchors.left");
        clearIcon->RemoveProperty("focusPolicy");
        clearIcon->Property("anchors.verticalCenter", "parent.verticalCenter");
        clearIcon->Property("anchors.margins", Formatter() << iconConfig.clearIconHorizontalPadding);
        clearIcon->Property("width", Formatter() << iconConfig.clearIconSize);
        clearIcon->Property("horizontalPadding", "0");
        clearIcon->Property("verticalPadding", "0");
        clearIcon->Property("icon.width", Formatter() << iconConfig.clearIconSize);
        clearIcon->Property("icon.height", Formatter() << iconConfig.clearIconSize);
        clearIcon->Property("icon.color", Formatter() << "activeFocus ? " << context->GetHexColor(iconConfig.clearIconColorOnFocus) << " : " << context->GetHexColor(iconConfig.clearIconColorNormal));
        clearIcon->Property("icon.source", RendererQml::cancel_icon_10, true);
        clearIcon->Property("background", backgroundTag->ToString());
        clearIcon->Property("Keys.onReturnPressed", "onClicked()");

        return clearIcon;
    }
}
