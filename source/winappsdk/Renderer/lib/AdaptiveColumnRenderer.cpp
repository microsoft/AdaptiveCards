// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnRenderer.h"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveColumnRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                     rtrender::AdaptiveRenderContext const& renderContext,
                                                     rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumn> adaptiveColumn;
        RETURN_IF_FAILED(cardElement.As(&adaptiveColumn));*/

        auto adaptiveColumn = cardElement.as<rtom::AdaptiveColumn>();

        /* ComPtr<IBorder> columnBorder =
             XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));*/

        rtxaml::Controls::Border columnBorder{};

        /* ComPtr<WholeItemsPanel> columnPanel;
         RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&columnPanel));*/

        auto columnPanel = winrt::make<rtrender::implementation::WholeItemsPanel>();

        /*ComPtr<IUIElement> columnPanelAsUIElement;
        RETURN_IF_FAILED(columnPanel.As(&columnPanelAsUIElement));

        RETURN_IF_FAILED(columnBorder->put_Child(columnPanelAsUIElement.Get()));*/

        columnBorder.Child(columnPanel);

        /*ComPtr<IFrameworkElement> columnPanelAsFrameworkElement;
        RETURN_IF_FAILED(columnPanel.As(&columnPanelAsFrameworkElement));

        ComPtr<IReference<bool>> previousContextRtl;
        RETURN_IF_FAILED(renderContext->get_Rtl(&previousContextRtl));
        ComPtr<IReference<bool>> currentRtl = previousContextRtl;

        ComPtr<IReference<bool>> containerRtl;
        RETURN_IF_FAILED(adaptiveColumn->get_Rtl(&containerRtl));*/

        auto previousContextRtl = renderContext.Rtl();
        auto currentRtl = previousContextRtl;
        auto containerRtl = adaptiveColumn.Rtl();

        bool updatedRtl = false;

        if (containerRtl != nullptr)
        {
            currentRtl = containerRtl;
            renderContext.Rtl(currentRtl);
            updatedRtl = true;
        }

        if (currentRtl != nullptr)
        {
            columnPanel.FlowDirection(currentRtl.Value() ? rtxaml::FlowDirection::RightToLeft : rtxaml::FlowDirection::LeftToRight);
        }

        /* ComPtr<IAdaptiveContainerBase> columnAsContainerBase;
         RETURN_IF_FAILED(adaptiveColumn.As(&columnAsContainerBase));*/
        rtom::ContainerStyle containerStyle{};
        
        if (const auto columnAsContainerBase = adaptiveColumn.try_as<rtom::IAdaptiveContainerBase>())
        {

            XamlHelpers::HandleStylingAndPadding(columnAsContainerBase, columnBorder, renderContext, renderArgs, &containerStyle);
        }

        /*ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
         RETURN_IF_FAILED(
             XamlHelpers::HandleStylingAndPadding(columnAsContainerBase.Get(), columnBorder.Get(), renderContext, renderArgs, &containerStyle));*/

        /*ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));*/

        auto parentElement = renderArgs.ParentElement().as<rtxaml::FrameworkElement>();
        
        auto newRenderArgs =
            winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);
        /* ComPtr<IPanel> columnAsPanel;
            THROW_IF_FAILED(columnPanel.As(&columnAsPanel));*/

        auto childItems = adaptiveColumn.Items();

        /* ComPtr<IVector<IAdaptiveCardElement*>> childItems;
            RETURN_IF_FAILED(adaptiveColumn->get_Items(&childItems));*/
        // Do I need to cast columnPanel to rtxaml::Controls::Panel?
        XamlBuilder::BuildPanelChildren(childItems,
                                        columnPanel.as<rtxaml::Controls::Panel>(),
                                        renderContext,
                                        newRenderArgs,
                                        [](rtxaml::IUIElement) {});
        
        // If we changed the context's rtl setting, set it back after rendering the children
        if (updatedRtl)
        {
            // RETURN_IF_FAILED(renderContext->put_Rtl(previousContextRtl.Get()));
            renderContext.Rtl(previousContextRtl);
        }

        /*  ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>> verticalContentAlignmentReference;
          RETURN_IF_FAILED(adaptiveColumn->get_VerticalContentAlignment(&verticalContentAlignmentReference));*/
        auto verticalContentAlignmentReference = adaptiveColumn.VerticalContentAlignment();

        rtom::VerticalContentAlignment verticalContentAlignment = rtom::VerticalContentAlignment::Top;
        if (verticalContentAlignmentReference != nullptr)
        {
            verticalContentAlignment = verticalContentAlignmentReference.Value();
        }

        XamlHelpers::SetVerticalContentAlignmentToChildren(columnPanel, verticalContentAlignment);

        // Assign vertical alignment to strech so column will stretch and respect vertical content alignment
       /* RETURN_IF_FAILED(columnPanelAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));*/
        columnPanel.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);

        /*RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Column", columnPanelAsFrameworkElement.Get()));*/
        // Do I need to cast columnPanel to FrameworkElement?
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Column", columnPanel);

        uint32_t columnMinHeight = adaptiveColumn.MinHeight();

        //RETURN_IF_FAILED(columnAsContainerBase->get_MinHeight(&columnMinHeight));
        // Do I need to cast adaptiveColumn to rtom::ContainerBase?
        if (columnMinHeight > 0)
        {
            //RETURN_IF_FAILED(columnPanelAsFrameworkElement->put_MinHeight(columnMinHeight));
            columnPanel.MinHeight(columnMinHeight);
        }

        /*ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(columnAsContainerBase->get_SelectAction(&selectAction));*/
        auto selectAction = adaptiveColumn.SelectAction();

        // Define column As UIElement based on the existence of a backgroundImage
       /* ComPtr<IUIElement> columnAsUIElement;
        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        RETURN_IF_FAILED(adaptiveColumn->get_BackgroundImage(&backgroundImage));
        RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));*/

        winrt::com_ptr<rtxaml::UIElement> columnAsUIElement;

        auto backgroundImage = adaptiveColumn.BackgroundImage();

        if (IsBackgroundImageValid(backgroundImage))
        {
           /* ComPtr<IGrid> rootElement =
                XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> rootAsPanel;
            RETURN_IF_FAILED(rootElement.As(&rootAsPanel));*/

            rtxaml::Controls::Grid rootElement{};

           /* XamlHelpers::ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, newRenderArgs.Get());*/

            // No need to cast right? Winrt will call QueryInterface and cast Grid to Panel?
            XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext, newRenderArgs);

            // get HeightType for column
          /*  ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType columnHeightType{};
            RETURN_IF_FAILED(cardElement->get_Height(&columnHeightType));*/

            auto columnHeightType = cardElement.Height();

            // Add columnBorder to rootElement
           /* ComPtr<IFrameworkElement> columnBorderAsFElement;
            RETURN_IF_FAILED(columnBorder.As(&columnBorderAsFElement));
            XamlHelpers::AppendXamlElementToPanel(columnBorderAsFElement.Get(), rootElement, columnHeightType);*/
            XamlHelpers::AppendXamlElementToPanel(columnBorder, rootElement, columnHeightType);

            //columnAsUIElement = winrt::make_self<rtxaml::UIElement>(rootElement);
            rootElement.as(columnAsUIElement);
            //RETURN_IF_FAILED(rootElement.As(&columnAsUIElement));
        }
        else
        {
            //RETURN_IF_FAILED(columnBorder.As(&columnAsUIElement));
            columnBorder.as(columnAsUIElement);
        }

       /* ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/
        auto hostConfig = renderContext.HostConfig();

        ActionHelpers::HandleSelectAction(adaptiveCardElement,
                                          selectAction.Get(),
                                          renderContext,
                                          columnAsUIElement.Get(),
                                          XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                          false,
                                          ColumnControl);
    }
}
