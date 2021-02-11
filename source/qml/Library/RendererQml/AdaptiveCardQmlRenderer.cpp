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
        catch (const std::exception& e)
        {
            context->AddWarning(AdaptiveWarning(Code::RenderException, e.what()));
        }

        return output;
    }

    std::shared_ptr<QmlTag> AdaptiveCardQmlRenderer::AdaptiveCardRender(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::shared_ptr<AdaptiveRenderContext> context)
    {
        auto uiCard = std::make_shared<QmlTag>("Item", "adaptiveCard");
        uiCard->AddImports("import QtQuick 2.15");
        uiCard->AddImports("import QtQuick.Layouts 1.3");
        uiCard->Property("id", "adaptiveCard");
        uiCard->Property("anchors.fill", "parent");

        auto columnLayout = std::make_shared<QmlTag>("ColumnLayout");
        columnLayout->Property("anchors.fill", "parent");
        uiCard->AddChild(columnLayout);

        auto rectangle = std::make_shared<QmlTag>("Rectangle");
        rectangle->Property("color", context->GetRGBColor(context->GetConfig()->GetContainerStyles().defaultPalette.backgroundColor));
        rectangle->Property("Layout.margins", std::to_string(context->GetConfig()->GetSpacing().paddingSpacing));
        rectangle->Property("Layout.fillWidth", "true");
        rectangle->Property("Layout.preferredHeight", "40");

        if (card->GetMinHeight() > 0)
        {
            rectangle->Property("Layout.minimumHeight", std::to_string(card->GetMinHeight()));
        }
        columnLayout->AddChild(rectangle);

        return uiCard;
    }

    void AdaptiveCardQmlRenderer::SetObjectTypes()
    {
        /*(*GetElementRenderers()).Set<AdaptiveCards::TextBlock>(AdaptiveCardQmlRenderer::TextBlockRender);
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

        (*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::OpenUrlAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ShowCardAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);
        (*GetElementRenderers()).Set<AdaptiveCards::ToggleVisibilityAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);

        (*GetElementRenderers()).Set<AdaptiveCards::SubmitAction>(AdaptiveCardQmlRenderer::AdaptiveActionRender);*/
    }
}
