// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextBlockRenderer.g.cpp"
#include "AdaptiveRenderContext.h"
#include "TextHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveTextBlockRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveTextBlock = cardElement.as<winrt::AdaptiveTextBlock>();
            winrt::hstring text = adaptiveTextBlock.Text();

            // If the text is null, return immediately without constructing a text block
            if (text.empty())
            {
                renderContext.AddError(winrt::ErrorStatusCode::RequiredPropertyMissing,
                                       L"Required property, \"text\", is missing from TextBlock");
                return nullptr;
            }

            winrt::TextBlock xamlTextBlock{};

            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", xamlTextBlock);
            StyleXamlTextBlockProperties(adaptiveTextBlock, renderContext, renderArgs, xamlTextBlock);
            auto inlines = xamlTextBlock.Inlines();

            // Check if this text block has a style and if so apply the appropriate styling from the host config
            auto textStyleRef = adaptiveTextBlock.Style() == nullptr ? renderContext.TextStyle() : adaptiveTextBlock.Style();
            winrt::TextStyle textStyle = GetValueFromRef(textStyleRef, winrt::TextStyle::Default);

            auto hostConfig = renderContext.HostConfig();
            auto textStylesConfig = hostConfig.TextStyles();

            if (textStyle == winrt::TextStyle::Heading)
            {
                auto headingTextStyleConfig = textStylesConfig.Heading();
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, headingTextStyleConfig, xamlTextBlock);
            }
            else if (textStyle == winrt::TextStyle::ColumnHeader)
            {
                auto columnHeaderTextStyleConfig = textStylesConfig.ColumnHeader();
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, columnHeaderTextStyleConfig, xamlTextBlock);
            }
            else
            {
                SetXamlInlines(adaptiveTextBlock, renderContext, renderArgs, false, inlines);
            }

            // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
            // are flush on the left edge of the card by enabling TrimSideBearings
            xamlTextBlock.OpticalMarginAlignment(winrt::OpticalMarginAlignment::TrimSideBearings);

            // If this text block has a heading style, set the corresponding automation property
            if (textStyle == winrt::TextStyle::Heading)
            {
                winrt::AutomationProperties::SetHeadingLevel(xamlTextBlock, GetHeadingLevelFromContext(renderContext));
            }

            return xamlTextBlock;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }

    winrt::Peers::AutomationHeadingLevel AdaptiveTextBlockRenderer::GetHeadingLevelFromContext(winrt::AdaptiveRenderContext const& renderContext)
    {
        auto textBlockConfig = renderContext.HostConfig().TextBlock();

        switch (textBlockConfig.HeadingLevel())
        {
        case 0:
        case 1:
            return winrt::Peers::AutomationHeadingLevel::Level1;
            break;
        case 2:
            return winrt::Peers::AutomationHeadingLevel::Level2;
            break;
        case 3:
            return winrt::Peers::AutomationHeadingLevel::Level3;
            break;
        case 4:
            return winrt::Peers::AutomationHeadingLevel::Level4;
            break;
        case 5:
            return winrt::Peers::AutomationHeadingLevel::Level5;
            break;
        case 6:
            return winrt::Peers::AutomationHeadingLevel::Level6;
            break;
        case 7:
            return winrt::Peers::AutomationHeadingLevel::Level7;
            break;
        case 8:
            return winrt::Peers::AutomationHeadingLevel::Level8;
            break;
        case 9:
        default:
            return winrt::Peers::AutomationHeadingLevel::Level9;
            break;
        }
    }
}
