// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlockRenderer.h"
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
            /* ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
             ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
             RETURN_IF_FAILED(cardElement.As(&adaptiveTextBlock));*/

            /*ComPtr<IAdaptiveTextElement> textBlockAsTextElement;
            RETURN_IF_FAILED(adaptiveTextBlock.As(&textBlockAsTextElement));
            HString text;
            RETURN_IF_FAILED(textBlockAsTextElement->get_Text(text.ReleaseAndGetAddressOf()));*/
            auto adaptiveTextBlock = cardElement.as<rtom::AdaptiveTextBlock>();
            winrt::hstring text = adaptiveTextBlock.Text();

            // If the text is null, return immediately without constructing a text block
            // if (text.Get() == nullptr)
            // TODO: not sure how to check it properly, need to come back here
            if (text.data() == nullptr)
            {
                renderContext.AddError(rtom::ErrorStatusCode::RequiredPropertyMissing,
                                       L"Required property, \"text\", is missing from TextBlock");
                return nullptr;
            }

            /*  ComPtr<ITextBlock> xamlTextBlock =
                  XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

              ComPtr<IAdaptiveTextElement> adaptiveTextElement;
              RETURN_IF_FAILED(adaptiveTextBlock.As(&adaptiveTextElement));

              RETURN_IF_FAILED(
                  StyleXamlTextBlockProperties(adaptiveTextBlock.Get(), renderContext, renderArgs, xamlTextBlock.Get()));

              ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
              RETURN_IF_FAILED(xamlTextBlock->get_Inlines(&inlines));*/
            rtxaml::Controls::TextBlock xamlTextBlock{};
            auto inlines = xamlTextBlock.Inlines();

            // Check if this text block has a style and if so apply the appropriate styling from the host config
            /* ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle textStyle =
                 ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle::Default;

             ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>> textStyleRef;
             RETURN_IF_FAILED(adaptiveTextBlock->get_Style(&textStyleRef));*/

            // TODO: do I need to assign it to default at all? shouldn't it happen by default?
            rtom::TextStyle textStyle = rtom::TextStyle::Default;
            auto textStyleRef = adaptiveTextBlock.Style();
            if (textStyleRef == nullptr)
            {
                textStyleRef = renderContext.TextStyle();
            }
            textStyle = GetValueFromRef(textStyleRef, rtom::TextStyle::Default);

            // if (textStyleRef == nullptr)
            //{
            //    // If there's no style on the text block, check the renderContext to see if we inherit one from our
            //    parent RETURN_IF_FAILED(renderContext->get_TextStyle(&textStyleRef));
            //}

            // if (textStyleRef != nullptr)
            //{
            //    RETURN_IF_FAILED(textStyleRef->get_Value(&textStyle));
            //}

            /*ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ComPtr<IAdaptiveTextStylesConfig> textStylesConfig;
            RETURN_IF_FAILED(hostConfig->get_TextStyles(&textStylesConfig));*/
            auto hostConfig = renderContext.HostConfig();
            auto textStylesConfig = hostConfig.TextStyles();

            if (textStyle == rtom::TextStyle::Heading)
            {
                /* ComPtr<IAdaptiveTextStyleConfig> headingTextStyleConfig;
                 RETURN_IF_FAILED(textStylesConfig->get_Heading(&headingTextStyleConfig));

                 RETURN_IF_FAILED(SetXamlInlinesWithTextStyleConfig(
                     adaptiveTextElement.Get(), renderContext, renderArgs, headingTextStyleConfig.Get(), xamlTextBlock.Get()));*/
                auto headingTextStyleConfig = textStylesConfig.Heading();
                // TODO: no need to cast adaptiveTextBlock right?
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, headingTextStyleConfig, xamlTextBlock);
            }
            else if (textStyle == rtom::TextStyle::ColumnHeader)
            {
                /* ComPtr<IAdaptiveTextStyleConfig> columnHeaderTextStyleConfig;
                 RETURN_IF_FAILED(textStylesConfig->get_ColumnHeader(&columnHeaderTextStyleConfig));

                 RETURN_IF_FAILED(SetXamlInlinesWithTextStyleConfig(adaptiveTextElement.Get(),
                                                                    renderContext,
                                                                    renderArgs,
                                                                    columnHeaderTextStyleConfig.Get(),
                                                                    xamlTextBlock.Get()));*/
                auto columnHeaderTextStyleConfig = textStylesConfig.ColumnHeader();
                // TODO: check if need to cast?
                SetXamlInlinesWithTextStyleConfig(adaptiveTextBlock, renderContext, renderArgs, columnHeaderTextStyleConfig, xamlTextBlock);
            }
            else
            {
                /* RETURN_IF_FAILED(SetXamlInlines(adaptiveTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));*/
                // TODO: check if need to cast?
                SetXamlInlines(adaptiveTextBlock, renderContext, renderArgs, false, inlines);
            }

            // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
            // are flush on the left edge of the card by enabling TrimSideBearings
            /* ComPtr<ITextBlock2> xamlTextBlock2;
             RETURN_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));
             RETURN_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

             ComPtr<IFrameworkElement> frameworkElement;
             RETURN_IF_FAILED(xamlTextBlock.As(&frameworkElement));
             RETURN_IF_FAILED(
                 XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));*/
            xamlTextBlock.OpticalMarginAlignment(rtxaml::OpticalMarginAlignment::TrimSideBearings);
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", xamlTextBlock);

            // If this text block has a heading style, set the corresponding automation property
            if (textStyle == rtom::TextStyle::Heading)
            {
                /*ComPtr<IDependencyObject> textBlockAsDependencyObject;
                RETURN_IF_FAILED(xamlTextBlock.As(&textBlockAsDependencyObject));

                ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
                RETURN_IF_FAILED(
                    GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                         &automationPropertiesStatics));*/

                /* ComPtr<IAutomationPropertiesStatics7> automationPropertiesStatics7;
                 RETURN_IF_FAILED(automationPropertiesStatics.As(&automationPropertiesStatics7));*/

                // Get the heading level to be used from host config
                /*  AutomationHeadingLevel headingLevel;
                  RETURN_IF_FAILED(GetHeadingLevelFromContext(renderContext, &headingLevel));

                  RETURN_IF_FAILED(automationPropertiesStatics7->SetHeadingLevel(textBlockAsDependencyObject.Get(), headingLevel));*/
                auto headingLevel = GetHeadingLevelFromContext(renderContext);
                rtxaml::Automation::AutomationProperties::SetHeadingLevel(xamlTextBlock, headingLevel);
            }

            /* return xamlTextBlock.CopyTo(textBlockControl);*/
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
        /* ComPtr<IAdaptiveHostConfig> hostConfig;
         RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

         ComPtr<IAdaptiveTextBlockConfig> textBlockConfig;
         RETURN_IF_FAILED(hostConfig->get_TextBlock(&textBlockConfig));

         unsigned int levelInt;
         RETURN_IF_FAILED(textBlockConfig->get_HeadingLevel(&levelInt));*/
        auto hostConfig = renderContext.HostConfig();
        // TODO: why is it called textBlock if it's a config? :D
        auto textBlockConfig = hostConfig.TextBlock();
        uint32_t levelInt = textBlockConfig.HeadingLevel();

        switch (levelInt)
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
