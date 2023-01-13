// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveRichTextBlockRenderer.g.cpp"
#include "AdaptiveRenderContext.h"
#include "TextHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveRichTextBlockRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                           winrt::AdaptiveRenderContext const& renderContext,
                                                           winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // Create the top level rich text block and set it's properties
            winrt::RichTextBlock xamlRichTextBlock{};

            auto adaptiveRichTextBlock = cardElement.as<winrt::AdaptiveRichTextBlock>();

            // Set the horizontal Alingment
            SetHorizontalAlignment(adaptiveRichTextBlock, renderContext, xamlRichTextBlock);

            // Get the highlighters
            auto textHighlighters = xamlRichTextBlock.TextHighlighters();

            // Add a paragraph for the inlines
            auto xamlBlocks = xamlRichTextBlock.Blocks();

            winrt::Paragraph xamlParagraph{};
            xamlBlocks.Append(xamlParagraph);

            // Add the Inlines
            uint32_t currentOffset = 0;

            auto xamlInlines = xamlParagraph.Inlines();

            auto adaptiveInlines = adaptiveRichTextBlock.Inlines();

            for (auto adaptiveInline : adaptiveInlines)
            {
                // We only support TextRun inlines for now
                auto adaptiveTextRun = adaptiveInline.as<winrt::AdaptiveTextRun>();
                auto selectAction = adaptiveTextRun.SelectAction();

                bool selectActionIsEnabled = false;
                if (selectAction)
                {
                    // If the select action is disabled we won't render this as a link
                    selectActionIsEnabled = selectAction.IsEnabled();
                }

                auto adaptiveTextElement = adaptiveInline.as<winrt::IAdaptiveTextElement>();
                winrt::hstring text = adaptiveTextRun.Text();
                bool isStrikethrough = adaptiveTextRun.Strikethrough();
                bool isItalic = adaptiveTextRun.Italic();
                bool isUnderline = adaptiveTextRun.Underline();
                uint32_t inlineLength{0};

                if (selectAction && selectActionIsEnabled)
                {
                    // If there's a select action, create a hyperlink that triggers the action
                    winrt::Hyperlink hyperlink{};

                    auto actionInvoker = renderContext.ActionInvoker();

                    // Use the selectAction's title as the accessibility name for this link.
                    auto actionTitle = selectAction.Title();

                    if (!actionTitle.empty())
                    {
                        winrt::AutomationProperties::SetName(hyperlink, actionTitle);
                    }

                    hyperlink.Click([selectAction, actionInvoker](winrt::IInspectable const& /* sender */,
                                                                  winrt::HyperlinkClickEventArgs const& /* args*/) -> void
                                    { actionInvoker.SendActionEvent(selectAction); });

                    // Add the run text to the hyperlink's inlines
                    auto hyperlinkInlines = hyperlink.Inlines();

                    inlineLength = AddSingleTextInline(adaptiveTextElement,
                                                       renderContext,
                                                       renderArgs,
                                                       text,
                                                       TextRunStyleParameters{isStrikethrough, isItalic, isUnderline, true},
                                                       hyperlinkInlines);

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

                bool highlight = adaptiveTextRun.Highlight();

                if (highlight)
                {
                    auto textHighlighter = GetHighlighter(adaptiveTextElement, renderContext, renderArgs);
                    textHighlighter.Ranges().Append({(int)currentOffset, (int)inlineLength});
                    textHighlighters.Append(textHighlighter);
                }

                currentOffset += inlineLength;
            }

            return xamlRichTextBlock;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
