// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveRichTextBlockRenderer.g.cpp"
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

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveRichTextBlockRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                            rtrender::AdaptiveRenderContext const& renderContext,
                                                            rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // Create the top level rich text block and set it's properties
            /* ComPtr<IRichTextBlock> xamlRichTextBlock = XamlHelpers::CreateABIClass<IRichTextBlock>(
                 HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock));

             ComPtr<IAdaptiveCardElement> localAdaptiveCardElement(cardElement);
             ComPtr<IAdaptiveRichTextBlock> adaptiveRichTextBlock;
             RETURN_IF_FAILED(localAdaptiveCardElement.As(&adaptiveRichTextBlock));*/

            rtxaml::Controls::RichTextBlock xamlRichTextBlock{};

            auto adaptiveRichTextBlock = cardElement.as<rtom::AdaptiveRichTextBlock>();

            // Set the horizontal Alingment
            /* RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveRichTextBlock.Get(), renderContext, xamlRichTextBlock.Get()));*/
            SetHorizontalAlignment(adaptiveRichTextBlock, renderContext, xamlRichTextBlock);

            // Get the highlighters
            /* ComPtr<IRichTextBlock5> xamlRichTextBlock5;
             RETURN_IF_FAILED(xamlRichTextBlock.As(&xamlRichTextBlock5));

             ComPtr<IVector<TextHighlighter*>> textHighlighters;
             RETURN_IF_FAILED(xamlRichTextBlock5->get_TextHighlighters(&textHighlighters));*/

            auto textHighlighters = xamlRichTextBlock.TextHighlighters();

            // Add a paragraph for the inlines
            /*  ComPtr<IVector<Block*>> xamlBlocks;
              RETURN_IF_FAILED(xamlRichTextBlock->get_Blocks(&xamlBlocks));*/

            auto xamlBlocks = xamlRichTextBlock.Blocks();

            /* ComPtr<IParagraph> xamlParagraph =
                 XamlHelpers::CreateABIClass<IParagraph>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Paragraph));

             ComPtr<IBlock> paragraphAsBlock;
             RETURN_IF_FAILED(xamlParagraph.As(&paragraphAsBlock));
             RETURN_IF_FAILED(xamlBlocks->Append(paragraphAsBlock.Get()));*/

            rtxaml::Documents::Paragraph xamlParagraph{};

            // Add the Inlines
            /* ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines;
             RETURN_IF_FAILED(xamlParagraph->get_Inlines(&xamlInlines));

             ComPtr<IVector<IAdaptiveInline*>> adaptiveInlines;
             RETURN_IF_FAILED(adaptiveRichTextBlock->get_Inlines(&adaptiveInlines));

             UINT currentOffset = 0;*/

            uint32_t currentOffset = 0;

            auto xamlInlines = xamlParagraph.Inlines();

            auto adaptiveInlines = adaptiveRichTextBlock.Inlines();

            /* IterateOverVector<IAdaptiveInline>(
                 adaptiveInlines.Get(),
                 [&](IAdaptiveInline* adaptiveInline)*/
            for (auto adaptiveInline : adaptiveInlines)
            {
                // We only support TextRun inlines for now
                /* ComPtr<IAdaptiveInline> localInline(adaptiveInline);
                 ComPtr<IAdaptiveTextRun> adaptiveTextRun;
                 RETURN_IF_FAILED(localInline.As(&adaptiveTextRun));*/
                auto adaptiveTextRun = adaptiveInline.as<rtom::AdaptiveTextRun>();

                /* ComPtr<IAdaptiveActionElement> selectAction;
                 RETURN_IF_FAILED(adaptiveTextRun->get_SelectAction(&selectAction));*/
                auto selectAction = adaptiveTextRun.SelectAction();

                bool selectActionIsEnabled = false;
                if (selectAction != nullptr)
                {
                    // If the select action is disabled we won't render this as a link
                    /*RETURN_IF_FAILED(selectAction->get_IsEnabled(&selectActionIsEnabled));*/
                    selectActionIsEnabled = selectAction.IsEnabled();
                }

                /*ComPtr<IAdaptiveTextElement> adaptiveTextElement;
                RETURN_IF_FAILED(localInline.As(&adaptiveTextElement));

                HString text;
                RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));*/

                // TODO: no need to convert to IAdapativeTextElement right?
                auto adaptiveTextElement = adaptiveInline.as<rtom::IAdaptiveTextElement>();
                winrt::hstring text = adaptiveTextRun.Text();

                // TODO: isStrikeThrough{false} - do we need to keep the default one? getters shouldn't fail, right?
                bool isStrikethrough = adaptiveTextRun.Strikethrough();

                bool isItalic = adaptiveTextRun.Italic();
                // RETURN_IF_FAILED(adaptiveTextRun->get_Italic(&isItalic));

                bool isUnderline = adaptiveTextRun.Underline();
                // RETURN_IF_FAILED(adaptiveTextRun->get_Underline(&isUnderline));

                /* UINT inlineLength;*/
                uint32_t inlineLength;

                if (selectAction != nullptr && selectActionIsEnabled)
                {
                    // If there's a select action, create a hyperlink that triggers the action
                    /*ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
                        XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
                            HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));

                    ComPtr<IAdaptiveActionInvoker> actionInvoker;
                    renderContext->get_ActionInvoker(&actionInvoker);*/

                    rtxaml::Documents::Hyperlink hyperlink{};

                    auto actionInvoker = renderContext.ActionInvoker();

                    // Use the selectAction's title as the accessibility name for this link.
                    /* HString actionTitle;
                     RETURN_IF_FAILED(selectAction->get_Title(actionTitle.ReleaseAndGetAddressOf()));*/

                    auto actionTitle = selectAction.Title();

                    // TODO: is HString.valid and hstring.empty() kinda equal? I don't think so... will HString still return
                    // TODO: valid for empty string?
                    // TODO: how do we do it right for hstrings? .isValid is the same as checking for c_str() not being nullptr?
                    /*  if (!actionTitle.empty() && !WindowsIsStringEmpty(actionTitle.Get()))*/
                    if (!actionTitle.empty())
                    {
                        /*ComPtr<IAutomationPropertiesStatics> automationProperties;
                        RETURN_IF_FAILED(GetActivationFactory(
                            HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                            &automationProperties));
                        ComPtr<IDependencyObject> linkAsDependencyObject;
                        RETURN_IF_FAILED(hyperlink.As(&linkAsDependencyObject));
                        RETURN_IF_FAILED(automationProperties->SetName(linkAsDependencyObject.Get(), actionTitle.Get()));*/
                        rtxaml::Automation::AutomationProperties::SetName(hyperlink, actionTitle);
                    }

                    /* EventRegistrationToken clickToken;
                     RETURN_IF_FAILED(hyperlink->add_Click(
                         Callback<ABI::Windows::Foundation::ITypedEventHandler<Hyperlink*, HyperlinkClickEventArgs*>>(
                             [selectAction, actionInvoker](IInspectable*, IHyperlinkClickEventArgs*) -> HRESULT
                             { return actionInvoker->SendActionEvent(selectAction.Get()); })
                             .Get(),
                         &clickToken));*/
                    hyperlink.Click([selectAction, actionInvoker](winrt::Windows::Foundation::IInspectable const& /* sender */,
                                                                  rtxaml::Documents::HyperlinkClickEventArgs const& /* args*/) -> void
                                    { actionInvoker.SendActionEvent(selectAction); });

                    // Add the run text to the hyperlink's inlines
                   /* ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
                    RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsSpan));*/


                   /* ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> hyperlinkInlines;
                    RETURN_IF_FAILED(hyperlinkAsSpan->get_Inlines(hyperlinkInlines.GetAddressOf()));*/
                    auto hyperlinkInlines = hyperlink.Inlines();
                    inlineLength = AddSingleTextInline(adaptiveTextElement,
                                                       renderContext,
                                                       renderArgs,
                                                       text,
                                                       TextRunStyleParameters{isStrikethrough, isItalic, isUnderline, true},
                                                       hyperlinkInlines);


                    //ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hyperlinkAsInline;
                    //RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsInline));

                    //// Add the hyperlink to the paragraph's inlines
                    //RETURN_IF_FAILED(xamlInlines->Append(hyperlinkAsInline.Get()));
                    xamlInlines.Append(hyperlink);
                }
                else
                {
                    // Add the text to the paragraph's inlines
                    inlineLength = AddSingleTextInline(adaptiveTextElement,
                                                       renderContext,
                                                       renderArgs,
                                                       text,
                                                       TextRunStyleParameters{isStrikethrough, isItalic, isUnderline, false},
                                                       xamlInlines);
                }

                /*boolean highlight;
                RETURN_IF_FAILED(adaptiveTextRun->get_Highlight(&highlight));*/
                bool highlight = adaptiveTextRun.Highlight();

                if (highlight)
                {
                    /*ComPtr<ITextHighlighter> textHighlighter;
                    RETURN_IF_FAILED(GetHighlighter(adaptiveTextElement.Get(), renderContext, renderArgs, &textHighlighter));

                    ComPtr<IVector<TextRange>> ranges;
                    RETURN_IF_FAILED(textHighlighter->get_Ranges(&ranges));

                    TextRange textRange = {(INT32)currentOffset, (INT32)inlineLength};
                    RETURN_IF_FAILED(ranges->Append(textRange));

                    RETURN_IF_FAILED(textHighlighters->Append(textHighlighter.Get()));*/

                    auto textHighlighter = GetHighlighter(adaptiveTextElement, renderContext, renderArgs);
                }

                currentOffset += inlineLength;
            }

            //return xamlRichTextBlock.CopyTo(result);
            return xamlRichTextBlock;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
