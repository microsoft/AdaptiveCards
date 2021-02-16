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

	std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::AdaptiveCardRender(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::shared_ptr<AdaptiveRenderContext> context)
	{
		auto uiCard = std::make_shared<QmlTag>("Item");
		uiCard->AddImports("import QtQuick 2.15");
		uiCard->AddImports("import QtQuick.Layouts 1.3");
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

	void AdaptiveCardQmlRenderer::AddContainerElements(std::shared_ptr<QmlTag> uiContainer, const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& elements, std::shared_ptr<AdaptiveRenderContext> context)
	{
		if (elements.size() == 1)
		{
			auto cardElement = elements.at(0);
			auto uiElement= context->Render(cardElement);
			if (uiElement != nullptr)
			{
				uiContainer->AddChild(uiElement);
			}
		}

		else if (elements.size() > 1)
		{
			auto columnElement = std::make_shared<QmlTag>("Column");
			columnElement->Property("anchors.fill", "parent");
			uiContainer->AddChild(columnElement);
			for (const auto& cardElement : elements)
			{
				auto uiElement = context->Render(cardElement);
				if (uiElement != nullptr)
				{
					columnElement->AddChild(uiElement);
				}
			}
		}
	}

	void AdaptiveCardQmlRenderer::SetObjectTypes()
	{
		(*GetElementRenderers()).Set<AdaptiveCards::TextBlock>(AdaptiveCardQmlRenderer::TextBlockRender);
		/*(*GetElementRenderers()).Set<AdaptiveCards::RichTextBlock>(AdaptiveCardQmlRenderer::RichTextBlockRender);
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
		(*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
		(*GetElementRenderers()).Set<AdaptiveCards::OpenUrlAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
		(*GetElementRenderers()).Set<AdaptiveCards::ShowCardAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
		(*GetElementRenderers()).Set<AdaptiveCards::ToggleVisibilityAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
		(*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);*/
	}

}
