// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveContainer.h"

#include "ActionHelpers.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveContainerRenderer::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveContainerRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** containerControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveContainer> adaptiveContainer;
        RETURN_IF_FAILED(cardElement.As(&adaptiveContainer));

        ComPtr<WholeItemsPanel> containerPanel;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&containerPanel));

        ComPtr<IFrameworkElement> containerPanelAsFrameWorkElement;
        RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFrameWorkElement));

        // Get any RTL setting set on either the current context or on this container. Any value set on the container
        // should be set on the context to apply to all children
        ComPtr<IReference<bool>> previousContextRtl;
        RETURN_IF_FAILED(renderContext->get_Rtl(&previousContextRtl));
        ComPtr<IReference<bool>> currentRtl = previousContextRtl;

        ComPtr<IReference<bool>> containerRtl;
        RETURN_IF_FAILED(adaptiveContainer->get_Rtl(&containerRtl));

        bool updatedRtl = false;
        if (containerRtl != nullptr)
        {
            currentRtl = containerRtl;
            RETURN_IF_FAILED(renderContext->put_Rtl(currentRtl.Get()));
            updatedRtl = true;
        }

        if (currentRtl)
        {
            boolean rtlValue;
            RETURN_IF_FAILED(currentRtl->get_Value(&rtlValue));

            RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_FlowDirection(rtlValue ? FlowDirection_RightToLeft :
                                                                                            FlowDirection_LeftToRight));
        }

        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        ABI::AdaptiveCards::Rendering::Uwp::HeightType containerHeightType{};
        RETURN_IF_FAILED(cardElement->get_Height(&containerHeightType));
        if (containerHeightType == ABI::AdaptiveCards::Rendering::Uwp::HeightType::Auto)
        {
            RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        }

        ComPtr<IAdaptiveContainerBase> containerAsContainerBase;
        RETURN_IF_FAILED(adaptiveContainer.As(&containerAsContainerBase));

        UINT32 containerMinHeight{};
        RETURN_IF_FAILED(containerAsContainerBase->get_MinHeight(&containerMinHeight));
        if (containerMinHeight > 0)
        {
            RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_MinHeight(containerMinHeight));
        }

        ComPtr<IBorder> containerBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle containerStyle;
        RETURN_IF_FAILED(XamlHelpers::HandleStylingAndPadding(
            containerAsContainerBase.Get(), containerBorder.Get(), renderContext, renderArgs, &containerStyle));

        ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get(), renderArgs));

        ComPtr<IPanel> containerPanelAsPanel;
        RETURN_IF_FAILED(containerPanel.As(&containerPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        RETURN_IF_FAILED(adaptiveContainer->get_Items(&childItems));
        RETURN_IF_FAILED(XamlBuilder::BuildPanelChildren(
            childItems.Get(), containerPanelAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {}));

        // If we changed the context's rtl setting, set it back after rendering the children
        if (updatedRtl)
        {
            RETURN_IF_FAILED(renderContext->put_Rtl(previousContextRtl.Get()));
        }

        ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment>> verticalContentAlignmentReference;
        RETURN_IF_FAILED(adaptiveContainer->get_VerticalContentAlignment(&verticalContentAlignmentReference));

        ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment verticalContentAlignment =
            ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment::Top;
        if (verticalContentAlignmentReference != nullptr)
        {
            verticalContentAlignmentReference->get_Value(&verticalContentAlignment);
        }

        XamlHelpers::SetVerticalContentAlignmentToChildren(containerPanel.Get(), verticalContentAlignment);

        // Check if backgroundImage defined
        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        RETURN_IF_FAILED(adaptiveContainer->get_BackgroundImage(&backgroundImage));
        RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
        if (backgroundImageIsValid)
        {
            ComPtr<IGrid> rootElement =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> rootAsPanel;
            RETURN_IF_FAILED(rootElement.As(&rootAsPanel));

            XamlHelpers::ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, newRenderArgs.Get());

            // Add rootElement to containerBorder
            ComPtr<IUIElement> rootAsUIElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsUIElement));
            RETURN_IF_FAILED(containerBorder->put_Child(rootAsUIElement.Get()));

            // Add containerPanel to rootElement
            ComPtr<IFrameworkElement> containerPanelAsFElement;
            RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFElement));
            XamlHelpers::AppendXamlElementToPanel(containerPanelAsFElement.Get(), rootAsPanel.Get(), containerHeightType);
        }
        else
        {
            // instead, directly add containerPanel to containerBorder
            ComPtr<IUIElement> containerPanelAsUIElement;
            RETURN_IF_FAILED(containerPanel.As(&containerPanelAsUIElement));
            RETURN_IF_FAILED(containerBorder->put_Child(containerPanelAsUIElement.Get()));
        }

        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.Container",
                                                                     containerPanelAsFrameWorkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(containerAsContainerBase->get_SelectAction(&selectAction));

        ComPtr<IUIElement> containerBorderAsUIElement;
        RETURN_IF_FAILED(containerBorder.As(&containerBorderAsUIElement));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ActionHelpers::HandleSelectAction(adaptiveCardElement,
                                          selectAction.Get(),
                                          renderContext,
                                          containerBorderAsUIElement.Get(),
                                          XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                          true,
                                          containerControl);
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainerRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveCards::Rendering::Uwp::FromJson<AdaptiveCards::Rendering::Uwp::AdaptiveContainer, AdaptiveCards::Container, AdaptiveCards::ContainerParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
