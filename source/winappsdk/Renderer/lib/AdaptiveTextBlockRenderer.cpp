// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextBlockRenderer.g.cpp"
#include "AdaptiveRenderContext.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Automation::Peers;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveTextBlockRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveTextBlock = cardElement.as<rtom::AdaptiveTextBlock>();
            winrt::hstring text = adaptiveTextBlock.Text();

            // If the text is null, return immediately without constructing a text block
            // if (text.Get() == nullptr)
            // TODO: not sure how to check it properly, need to come back here
            if (text.empty())
            {
                renderContext.AddError(rtom::ErrorStatusCode::RequiredPropertyMissing,
                                       L"Required property, \"text\", is missing from TextBlock");
                return nullptr;
            }

            rtxaml::Controls::TextBlock xamlTextBlock{};
            StyleXamlTextBlockProperties(adaptiveTextBlock, renderContext, renderArgs, xamlTextBlock);
            auto inlines = xamlTextBlock.Inlines();

            // Check if this text block has a style and if so apply the appropriate styling from the host config
            auto textStyleRef = adaptiveTextBlock.Style() == nullptr ? renderContext.TextStyle() : adaptiveTextBlock.Style();
            rtom::TextStyle textStyle = GetValueFromRef(textStyleRef, rtom::TextStyle::Default);

            auto hostConfig = renderContext.HostConfig();
            auto textStylesConfig = hostConfig.TextStyles();

            if (textStyle == rtom::TextStyle::Heading)
            {
                auto headingTextStyleConfig = textStylesConfig.Heading();
                // TODO: no need to cast adaptiveTextBlock right?
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, headingTextStyleConfig, xamlTextBlock);
            }
            else if (textStyle == rtom::TextStyle::ColumnHeader)
            {
                auto columnHeaderTextStyleConfig = textStylesConfig.ColumnHeader();
                // TODO: check if need to cast?
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, columnHeaderTextStyleConfig, xamlTextBlock);
            }
            else
            {
                // TODO: check if need to cast?
                SetXamlInlines(adaptiveTextBlock, renderContext, renderArgs, false, inlines);
            }

            // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
            // are flush on the left edge of the card by enabling TrimSideBearings
            xamlTextBlock.OpticalMarginAlignment(rtxaml::OpticalMarginAlignment::TrimSideBearings);
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", xamlTextBlock);

            // If this text block has a heading style, set the corresponding automation property
            if (textStyle == rtom::TextStyle::Heading)
            {
                rtxaml::Automation::AutomationProperties::SetHeadingLevel(xamlTextBlock, GetHeadingLevelFromContext(renderContext));
            }

            return xamlTextBlock;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }

    rtxaml::Automation::Peers::AutomationHeadingLevel
    AdaptiveTextBlockRenderer::GetHeadingLevelFromContext(rtrender::AdaptiveRenderContext const& renderContext)
    {
        auto hostConfig = renderContext.HostConfig();
        // TODO: why is it called textBlock if it's a config? :D
        auto textBlockConfig = hostConfig.TextBlock();

        switch (textBlockConfig.HeadingLevel())
        {
        case 0:
        case 1:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level1;
            break;
        case 2:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level2;
            break;
        case 3:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level3;
            break;
        case 4:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level4;
            break;
        case 5:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level5;
            break;
        case 6:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level6;
            break;
        case 7:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level7;
            break;
        case 8:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level8;
            break;
        case 9:
        default:
            return rtxaml::Automation::Peers::AutomationHeadingLevel::Level9;
            break;
        }
    }
}
