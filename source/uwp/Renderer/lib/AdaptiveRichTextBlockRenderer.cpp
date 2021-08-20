// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveRenderContext.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveRichTextBlockRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlockRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                                  _In_ IAdaptiveRenderContext* renderContext,
                                                  _In_ IAdaptiveRenderArgs* renderArgs,
                                                  _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        // Create the top level rich text block and set it's properties
        ComPtr<IRichTextBlock> xamlRichTextBlock =
            XamlHelpers::CreateABIClass<IRichTextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock));

        ComPtr<IAdaptiveCardElement> localAdaptiveCardElement(cardElement);
        ComPtr<IAdaptiveRichTextBlock> adaptiveRichTextBlock;
        RETURN_IF_FAILED(localAdaptiveCardElement.As(&adaptiveRichTextBlock));

        // Set the horizontal Alingment
        RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveRichTextBlock.Get(), renderContext, xamlRichTextBlock.Get()));

        // Get the highlighters
        ComPtr<IRichTextBlock5> xamlRichTextBlock5;
        RETURN_IF_FAILED(xamlRichTextBlock.As(&xamlRichTextBlock5));

        ComPtr<IVector<TextHighlighter*>> textHighlighters;
        RETURN_IF_FAILED(xamlRichTextBlock5->get_TextHighlighters(&textHighlighters));

        // Add a paragraph for the inlines
        ComPtr<IVector<Block*>> xamlBlocks;
        RETURN_IF_FAILED(xamlRichTextBlock->get_Blocks(&xamlBlocks));

        ComPtr<IParagraph> xamlParagraph =
            XamlHelpers::CreateABIClass<IParagraph>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Paragraph));

        ComPtr<IBlock> paragraphAsBlock;
        RETURN_IF_FAILED(xamlParagraph.As(&paragraphAsBlock));
        RETURN_IF_FAILED(xamlBlocks->Append(paragraphAsBlock.Get()));

        // Add the Inlines
        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines;
        RETURN_IF_FAILED(xamlParagraph->get_Inlines(&xamlInlines));

        ComPtr<IVector<IAdaptiveInline*>> adaptiveInlines;
        RETURN_IF_FAILED(adaptiveRichTextBlock->get_Inlines(&adaptiveInlines));

        UINT currentOffset = 0;
        IterateOverVector<IAdaptiveInline>(adaptiveInlines.Get(), [&](IAdaptiveInline* adaptiveInline) {
            // We only support TextRun inlines for now
            ComPtr<IAdaptiveInline> localInline(adaptiveInline);
            ComPtr<IAdaptiveTextRun> adaptiveTextRun;
            RETURN_IF_FAILED(localInline.As(&adaptiveTextRun));

            ComPtr<IAdaptiveActionElement> selectAction;
            RETURN_IF_FAILED(adaptiveTextRun->get_SelectAction(&selectAction));

            boolean selectActionIsEnabled = false;
            if (selectAction != nullptr)
            {
                // If the select action is disabled we won't render this as a link
                RETURN_IF_FAILED(selectAction->get_IsEnabled(&selectActionIsEnabled));
            }

            ComPtr<IAdaptiveTextElement> adaptiveTextElement;
            RETURN_IF_FAILED(localInline.As(&adaptiveTextElement));

            HString text;
            RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));

            boolean isStrikethrough{false};
            RETURN_IF_FAILED(adaptiveTextRun->get_Strikethrough(&isStrikethrough));

            boolean isItalic{false};
            RETURN_IF_FAILED(adaptiveTextRun->get_Italic(&isItalic));

            boolean isUnderline{};
            RETURN_IF_FAILED(adaptiveTextRun->get_Underline(&isUnderline));

            UINT inlineLength;
            if (selectAction != nullptr && selectActionIsEnabled)
            {
                // If there's a select action, create a hyperlink that triggers the action
                ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
                    XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));

                ComPtr<IAdaptiveActionInvoker> actionInvoker;
                renderContext->get_ActionInvoker(&actionInvoker);

                // Use the selectAction's title as the accessibility name for this link.
                HString actionTitle;
                RETURN_IF_FAILED(selectAction->get_Title(actionTitle.ReleaseAndGetAddressOf()));
                if (actionTitle.IsValid() && !WindowsIsStringEmpty(actionTitle.Get()))
                {
                    ComPtr<IAutomationPropertiesStatics> automationProperties;
                    RETURN_IF_FAILED(GetActivationFactory(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(), &automationProperties));
                    ComPtr<IDependencyObject> linkAsDependencyObject;
                    RETURN_IF_FAILED(hyperlink.As(&linkAsDependencyObject));
                    RETURN_IF_FAILED(automationProperties->SetName(linkAsDependencyObject.Get(), actionTitle.Get()));
                }

                EventRegistrationToken clickToken;
                RETURN_IF_FAILED(
                    hyperlink->add_Click(Callback<ABI::Windows::Foundation::ITypedEventHandler<Hyperlink*, HyperlinkClickEventArgs*>>(
                                             [selectAction, actionInvoker](IInspectable*, IHyperlinkClickEventArgs*) -> HRESULT {
                                                 return actionInvoker->SendActionEvent(selectAction.Get());
                                             })
                                             .Get(),
                                         &clickToken));

                // Add the run text to the hyperlink's inlines
                ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
                RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsSpan));

                ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> hyperlinkInlines;
                RETURN_IF_FAILED(hyperlinkAsSpan->get_Inlines(hyperlinkInlines.GetAddressOf()));
                RETURN_IF_FAILED(AddSingleTextInline(adaptiveTextElement.Get(),
                                                     renderContext,
                                                     renderArgs,
                                                     text.Get(),
                                                     TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
                                                     hyperlinkInlines.Get(),
                                                     &inlineLength));

                ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hyperlinkAsInline;
                RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsInline));

                // Add the hyperlink to the paragraph's inlines
                RETURN_IF_FAILED(xamlInlines->Append(hyperlinkAsInline.Get()));
            }
            else
            {
                // Add the text to the paragraph's inlines
                RETURN_IF_FAILED(AddSingleTextInline(adaptiveTextElement.Get(),
                                                     renderContext,
                                                     renderArgs,
                                                     text.Get(),
                                                     TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, false),
                                                     xamlInlines.Get(),
                                                     &inlineLength));
            }

            boolean highlight;
            RETURN_IF_FAILED(adaptiveTextRun->get_Highlight(&highlight));

            if (highlight)
            {
                ComPtr<ITextHighlighter> textHighlighter;
                RETURN_IF_FAILED(GetHighlighter(adaptiveTextElement.Get(), renderContext, renderArgs, &textHighlighter));

                ComPtr<IVector<TextRange>> ranges;
                RETURN_IF_FAILED(textHighlighter->get_Ranges(&ranges));

                TextRange textRange = {(INT32)currentOffset, (INT32)inlineLength};
                RETURN_IF_FAILED(ranges->Append(textRange));

                RETURN_IF_FAILED(textHighlighters->Append(textHighlighter.Get()));
            }

            currentOffset += inlineLength;
            return S_OK;
        });

        return xamlRichTextBlock.CopyTo(result);
    }
    CATCH_RETURN;
}
