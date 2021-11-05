// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveContainerRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // TODO: should I still keep try, catch and return nullptr in case of failure?
            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveContainer> adaptiveContainer;
            RETURN_IF_FAILED(cardElement.As(&adaptiveContainer));*/
            rtom::AdaptiveContainer adaptiveContainer = cardElement.as<rtom::AdaptiveContainer>();

            /* ComPtr<WholeItemsPanel> containerPanel;
             RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&containerPanel));*/

            // TODO: revisit wholeitemPanel
            auto containerPanel = winrt::make<rtrender::implementation::WholeItemsPanel>();

            /*   ComPtr<IFrameworkElement> containerPanelAsFrameWorkElement;
               RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFrameWorkElement));*/

            // Get any RTL setting set on either the current context or on this container. Any value set on the
            // container should be set on the context to apply to all children
            /* renderContext.Rtl()
             ComPtr<IReference<bool>> previousContextRtl;
             RETURN_IF_FAILED(renderContext->get_Rtl(&previousContextRtl));*/
            // ComPtr<IReference<bool>> currentRtl = previousContextRtl;
            auto previousContextRtl = renderContext.Rtl();
            auto currentRtl = previousContextRtl;
            auto containerRtl = adaptiveContainer.Rtl();

            /*ComPtr<IReference<bool>> containerRtl;
            RETURN_IF_FAILED(adaptiveContainer->get_Rtl(&containerRtl));*/

            bool updatedRtl = false;
            if (containerRtl != nullptr)
            {
                currentRtl = containerRtl;
                // RETURN_IF_FAILED(renderContext->put_Rtl(currentRtl.Get()));
                renderContext.Rtl(currentRtl);
                updatedRtl = true;
            }

            if (currentRtl)
            {
                boolean rtlValue = currentRtl.GetBoolean();
                containerPanel.FlowDirection(rtlValue ? rtxaml::FlowDirection::RightToLeft : rtxaml::FlowDirection::LeftToRight);
                /*RETURN_IF_FAILED(currentRtl->get_Value(&rtlValue));*/

                /* RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_FlowDirection(rtlValue ?
                   FlowDirection_RightToLeft : FlowDirection_LeftToRight));*/
            }

            // Assign vertical alignment to strech so column will stretch and respect vertical content alignment
            /*ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType containerHeightType{};
            RETURN_IF_FAILED(cardElement->get_Height(&containerHeightType));*/
            auto containerHeightType = cardElement.Height();
            if (containerHeightType == rtom::HeightType::Auto)
            {
                // RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Stretch));
                containerPanel.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);
            }

            /* ComPtr<IAdaptiveContainerBase> containerAsContainerBase;
             RETURN_IF_FAILED(adaptiveContainer.As(&containerAsContainerBase));*/

            // UINT32 containerMinHeight{};
            // RETURN_IF_FAILED(containerAsContainerBase->get_MinHeight(&containerMinHeight));

            uint32_t containerMinHeight = adaptiveContainer.MinHeight();

            if (containerMinHeight > 0)
            {
                /*RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_MinHeight(containerMinHeight));*/
                containerPanel.MinHeight(containerMinHeight);
            }

            /*ComPtr<IBorder> containerBorder =
                XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));*/
            rtxaml::Controls::Border containerBorder{};

            // TODO: Convert to FULL WINRT
            /*ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;*/
            // winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
            /* XamlHelpers::HandleStylingAndPadding(to_wrl(adaptiveContainer.as<rtom::IAdaptiveContainerBase>()).Get(),
                                                  containerBorder.Get(),
                                                  to_wrl(renderContext).Get(),
                                                  to_wrl(renderArgs).Get(),
                                                  &containerStyle);*/
            auto containerStyle = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleStylingAndPadding(adaptiveContainer,
                                                                                                           containerBorder,
                                                                                                           renderContext,
                                                                                                           renderArgs);

            /* ComPtr<IFrameworkElement> parentElement;
             RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));*/
            auto parentElement = renderArgs.ParentElement();
            auto newRenderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);

            /*  ComPtr<IPanel> containerPanelAsPanel;
              RETURN_IF_FAILED(containerPanel.As(&containerPanelAsPanel));
              ComPtr<IVector<IAdaptiveCardElement*>> childItems;
              RETURN_IF_FAILED(adaptiveContainer->get_Items(&childItems));*/
            /*RETURN_IF_FAILED(XamlBuilder::BuildPanelChildren(
                childItems.Get(), containerPanelAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {}));*/
            /*RETURN_IF_FAILED(XamlBuilder::BuildPanelChildren(
                childItems.Get(), containerPanelAsPanel.Get(), renderContext, renderArgs, [](IUIElement*) {}));*/
            auto childItems = adaptiveContainer.Items();
            ::AdaptiveCards::Rendering::WinUI3::XamlBuilder::BuildPanelChildren(
                childItems, containerPanel.as<rtxaml::Controls::Panel>(), renderContext, renderArgs, [](rtxaml::UIElement) {});

            // If we changed the context's rtl setting, set it back after rendering the children
            if (updatedRtl)
            {
                // RETURN_IF_FAILED(renderContext->put_Rtl(previousContextRtl.Get()));
                renderContext.Rtl(previousContextRtl);
            }

            // ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>> verticalContentAlignmentReference;
            // to_wrl(adaptiveContainer)->get_VerticalContentAlignment(&verticalContentAlignmentReference);
            auto verticalContentAlignmentReference = adaptiveContainer.VerticalContentAlignment();
            rtom::VerticalContentAlignment verticalContentAlignment = rtom::VerticalContentAlignment::Top;

            if (verticalContentAlignmentReference != nullptr)
            {
                verticalContentAlignment = verticalContentAlignmentReference.Value();
            }

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetVerticalContentAlignmentToChildren(containerPanel, verticalContentAlignment);

            // Check if backgroundImage defined
            /* ComPtr<IAdaptiveBackgroundImage> backgroundImage;
             BOOL backgroundImageIsValid;
             RETURN_IF_FAILED(adaptiveContainer->get_BackgroundImage(&backgroundImage));
             RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));*/
            auto backgroundImage = adaptiveContainer.BackgroundImage();

            if (IsBackgroundImageValid(backgroundImage))
            {
                /*ComPtr<IGrid> rootElement =
                    XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
                ComPtr<IPanel> rootAsPanel;
                rootElement.As(&rootAsPanel);*/
                rtxaml::Controls::Grid rootElement{};

                // Convert to WINRT
                /*XamlHelpers::ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, newRenderArgs.Get());*/
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext, renderArgs);

                // Add rootElement to containerBorder
                /*ComPtr<IUIElement> rootAsUIElement;
                rootElement.As(&rootAsUIElement);
                containerBorder->put_Child(rootAsUIElement.Get())*/
                containerBorder.Child(rootElement);

                // Add containerPanel to rootElement
                /*ComPtr<IFrameworkElement> containerPanelAsFElement;
                RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFElement));*/
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(containerPanel, rootElement, containerHeightType);
            }
            else
            {
                // instead, directly add containerPanel to containerBorder
                /*ComPtr<IUIElement> containerPanelAsUIElement;
                RETURN_IF_FAILED(containerPanel.As(&containerPanelAsUIElement));
                RETURN_IF_FAILED(containerBorder->put_Child(containerPanelAsUIElement.Get()));*/
                containerBorder.Child(containerPanel);
            }

            /*RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                         L"Adaptive.Container",
                                                                         containerPanelAsFrameWorkElement.Get()));*/
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Container", containerPanel);

            /*ComPtr<IAdaptiveActionElement> selectAction;
            RETURN_IF_FAILED(containerAsContainerBase->get_SelectAction(&selectAction));*/
            auto selectAction = adaptiveContainer.SelectAction();

            /*ComPtr<IUIElement> containerBorderAsUIElement;
            RETURN_IF_FAILED(containerBorder.As(&containerBorderAsUIElement));

            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/

            auto hostConfig = renderContext.HostConfig();

            /*ActionHelpers::HandleSelectAction(adaptiveCardElement,
                                              selectAction.Get(),
                                              renderContext,
                                              containerBorderAsUIElement.Get(),
                                              XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                              true,
                                              containerControl);*/
            return ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::HandleSelectAction(
                cardElement,
                selectAction,
                renderContext,
                containerBorder,
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig),
                true);
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
