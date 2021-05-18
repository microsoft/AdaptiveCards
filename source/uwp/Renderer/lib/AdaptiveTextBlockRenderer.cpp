// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlock.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveRenderContext.h"
#include "AdaptiveElementParserRegistration.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Automation::Peers;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveTextBlockRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlockRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** textBlockControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<IAdaptiveTextElement> textBlockAsTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&textBlockAsTextElement));
        HString text;
        RETURN_IF_FAILED(textBlockAsTextElement->get_Text(text.ReleaseAndGetAddressOf()));

        // If the text is null, return immediately without constructing a text block
        if (text.Get() == nullptr)
        {
            *textBlockControl = nullptr;
            renderContext->AddError(ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode::RequiredPropertyMissing,
                                    HStringReference(L"Required property, \"text\", is missing from TextBlock").Get());
            return S_OK;
        }

        ComPtr<ITextBlock> xamlTextBlock =
            XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        ComPtr<IAdaptiveTextElement> adaptiveTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&adaptiveTextElement));

        RETURN_IF_FAILED(StyleXamlTextBlockProperties(adaptiveTextBlock.Get(), renderContext, renderArgs, xamlTextBlock.Get()));

        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
        RETURN_IF_FAILED(xamlTextBlock->get_Inlines(&inlines));

        // Check if this text block has a style set to heading and if so apply the appropriate styling from the host config
        ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::TextStyle>> textStyleRef;
        RETURN_IF_FAILED(adaptiveTextBlock->get_Style(&textStyleRef));

        ABI::AdaptiveCards::Rendering::Uwp::TextStyle textStyle = ABI::AdaptiveCards::Rendering::Uwp::TextStyle::Default;
        if (textStyleRef != nullptr)
        {
            RETURN_IF_FAILED(textStyleRef->get_Value(&textStyle));
        }

        if (textStyle == ABI::AdaptiveCards::Rendering::Uwp::TextStyle::Heading)
        {
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ComPtr<IAdaptiveTextStylesConfig> textStylesConfig;
            RETURN_IF_FAILED(hostConfig->get_TextStyles(&textStylesConfig));

            ComPtr<IAdaptiveTextStyleConfig> headingTextStyleConfig;
            RETURN_IF_FAILED(textStylesConfig->get_Heading(&headingTextStyleConfig));

            RETURN_IF_FAILED(SetXamlInlinesWithTextStyleConfig(
                adaptiveTextElement.Get(), renderContext, renderArgs, headingTextStyleConfig.Get(), xamlTextBlock.Get()));
        }
        else
        {
            RETURN_IF_FAILED(SetXamlInlines(adaptiveTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));
        }

        // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
        // are flush on the left edge of the card by enabling TrimSideBearings
        ComPtr<ITextBlock2> xamlTextBlock2;
        RETURN_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));
        RETURN_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(xamlTextBlock.As(&frameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));

        // If this text block has a heading style, set the corresponding automation property
        if (textStyle == ABI::AdaptiveCards::Rendering::Uwp::TextStyle::Heading)
        {
            ComPtr<IDependencyObject> textBlockAsDependencyObject;
            RETURN_IF_FAILED(xamlTextBlock.As(&textBlockAsDependencyObject));

            ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
            RETURN_IF_FAILED(
                GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                     &automationPropertiesStatics));

            ComPtr<IAutomationPropertiesStatics7> automationPropertiesStatics7;
            RETURN_IF_FAILED(automationPropertiesStatics.As(&automationPropertiesStatics7));

            // Get the heading level to be used from host config
            AutomationHeadingLevel headingLevel;
            RETURN_IF_FAILED(GetHeadingLevelFromContext(renderContext, &headingLevel));

            RETURN_IF_FAILED(automationPropertiesStatics7->SetHeadingLevel(textBlockAsDependencyObject.Get(), headingLevel));
        }

        return xamlTextBlock.CopyTo(textBlockControl);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlockRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveCards::Rendering::Uwp::FromJson<AdaptiveCards::Rendering::Uwp::AdaptiveTextBlock, AdaptiveCards::TextBlock, AdaptiveCards::TextBlockParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlockRenderer::GetHeadingLevelFromContext(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                                                  ABI::Windows::UI::Xaml::Automation::Peers::AutomationHeadingLevel* headingLevel)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveTextBlockConfig> textBlockConfig;
        RETURN_IF_FAILED(hostConfig->get_TextBlock(&textBlockConfig));

        unsigned int levelInt;
        RETURN_IF_FAILED(textBlockConfig->get_HeadingLevel(&levelInt));

        switch (levelInt)
        {
        case 0:
        case 1:
            *headingLevel = AutomationHeadingLevel_Level1;
            break;
        case 2:
            *headingLevel = AutomationHeadingLevel_Level2;
            break;
        case 3:
            *headingLevel = AutomationHeadingLevel_Level3;
            break;
        case 4:
            *headingLevel = AutomationHeadingLevel_Level4;
            break;
        case 5:
            *headingLevel = AutomationHeadingLevel_Level5;
            break;
        case 6:
            *headingLevel = AutomationHeadingLevel_Level6;
            break;
        case 7:
            *headingLevel = AutomationHeadingLevel_Level7;
            break;
        case 8:
            *headingLevel = AutomationHeadingLevel_Level8;
            break;
        case 9:
        default:
            *headingLevel = AutomationHeadingLevel_Level9;
            break;
        }
        return S_OK;
    }

}
