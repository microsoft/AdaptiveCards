#pragma once
#include "pch.h"

#include "AdaptiveCardsRendererBase.h"
#include "RenderedQmlAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

#include "TextBlock.h"
#include "RichTextBlock.h"
#include "Inline.h"
#include "TextRun.h"
#include "Image.h"
#include "Media.h"
#include "Container.h"
#include "Column.h"
#include "ColumnSet.h"
#include "FactSet.h"
#include "ImageSet.h"
#include "ActionSet.h"
#include "ChoiceSetInput.h"
#include "CollectionTypeElement.h"
#include "TextInput.h"
#include "NumberInput.h"
#include "DateInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"
#include "SubmitAction.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "ToggleVisibilityAction.h"

namespace RendererQml
{
    class AdaptiveCardQmlRenderer : public AdaptiveCardsRendererBase<QmlTag, AdaptiveRenderContext>
    {
    public:
        AdaptiveCardQmlRenderer();
        AdaptiveCardQmlRenderer(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig);

        std::shared_ptr<RenderedQmlAdaptiveCard> RenderCard(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, AdaptiveCardDependency::OnClickFunction onClick);

    protected:
        static std::shared_ptr<QmlTag> AdaptiveCardRender(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::shared_ptr<AdaptiveRenderContext> context);

        /*static std::shared_ptr<QmlTag> TextBlockRender(std::shared_ptr<AdaptiveCards::TextBlock> textBlock, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> RichTextBlockRender(std::shared_ptr<AdaptiveCards::RichTextBlock> richTextBlock, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> TextRunRender(std::shared_ptr<AdaptiveCards::TextRun> textRun, std::shared_ptr<AdaptiveRenderContext> context);

        static std::shared_ptr<QmlTag> ImageRender(std::shared_ptr<AdaptiveCards::Image> image, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> MediaRender(std::shared_ptr<AdaptiveCards::Media> media, std::shared_ptr<AdaptiveRenderContext> context);

        static std::shared_ptr<QmlTag> ContainerRender(std::shared_ptr<AdaptiveCards::Container> container, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> ColumnRender(std::shared_ptr<AdaptiveCards::Column> column, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> ColumnSetRender(std::shared_ptr<AdaptiveCards::ColumnSet> columnSet, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> FactSetRender(std::shared_ptr<AdaptiveCards::FactSet> factSet, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> ImageSetRender(std::shared_ptr<AdaptiveCards::ImageSet> imageSet, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> ActionSetRender(std::shared_ptr<AdaptiveCards::ActionSet> actionSet, std::shared_ptr<AdaptiveRenderContext> context);

        static std::shared_ptr<QmlTag> ChoiceSetRender(std::shared_ptr<AdaptiveCards::ChoiceSetInput> choiceSet, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> TextInputRender(std::shared_ptr<AdaptiveCards::TextInput> input, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> NumberInputRender(std::shared_ptr<AdaptiveCards::NumberInput> input, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> DateInputRender(std::shared_ptr<AdaptiveCards::DateInput> input, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> TimeInputRender(std::shared_ptr<AdaptiveCards::TimeInput> input, std::shared_ptr<AdaptiveRenderContext> context);
        static std::shared_ptr<QmlTag> ToggleInputRender(std::shared_ptr<AdaptiveCards::ToggleInput> input, std::shared_ptr<AdaptiveRenderContext> context);

        static std::shared_ptr<QmlTag> AdaptiveActionRender(std::shared_ptr<AdaptiveCards::BaseActionElement> adaptiveAction, std::shared_ptr<AdaptiveRenderContext> context);*/

    private:
        void SetObjectTypes();
    };
}
