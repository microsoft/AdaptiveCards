// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetRenderer.h"
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
    winrt::Windows::UI::Xaml::UIElement AdaptiveImageSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                                         rtrender::AdaptiveRenderContext const& renderContext,
                                                                         rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveImageSet> adaptiveImageSet;
            RETURN_IF_FAILED(cardElement.As(&adaptiveImageSet));*/

            auto adaptiveImageSet = cardElement.as<rtom::AdaptiveImageSet>();

            /*ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateABIClass<IVariableSizedWrapGrid>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

            RETURN_IF_FAILED(xamlGrid->put_Orientation(Orientation_Horizontal));*/

            rtxaml::Controls::VariableSizedWrapGrid xamlGrid{};
            xamlGrid.Orientation(rtxaml::Controls::Orientation::Horizontal);

            // ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImage*>> images;
            // RETURN_IF_FAILED(adaptiveImageSet->get_Images(&images));

            auto images = adaptiveImageSet.Images();

            /* ComPtr<IAdaptiveHostConfig> hostConfig;
             RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
             ComPtr<IAdaptiveImageSetConfig> imageSetConfig;
             RETURN_IF_FAILED(hostConfig->get_ImageSet(&imageSetConfig));

             ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize imageSize;
             RETURN_IF_FAILED(adaptiveImageSet->get_ImageSize(&imageSize));*/

            auto hostConfig = renderContext.HostConfig();

            auto imageSetConfig = hostConfig.ImageSet();

            auto imageSize = adaptiveImageSet.ImageSize();

            if (imageSize == rtom::ImageSize::None)
            {
                // RETURN_IF_FAILED(imageSetConfig->get_ImageSize(&imageSize));
                imageSize = imageSetConfig.ImageSize();
            }

            /*ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> imageRenderer;
            RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));*/

            auto elementRenderers = renderContext.ElementRenderers();
            auto imageRenderer = elementRenderers.Get(L"Image");

            if (imageRenderer != nullptr)
            {
                /*ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
                RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));*/
                auto containerStyle = renderArgs.ContainerStyle();

                auto childRenderArgs =
                    winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, xamlGrid, renderArgs);

                for (auto adaptiveImage : images)
                {
                    /*ComPtr<IUIElement> uiImage;
                    ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
                    RETURN_IF_FAILED(localAdaptiveImage->put_Size(imageSize));*/
                    adaptiveImage.Size(imageSize);

                    /*ComPtr<IAdaptiveCardElement> adaptiveElementImage;
                    RETURN_IF_FAILED(localAdaptiveImage.As(&adaptiveElementImage));
                    RETURN_IF_FAILED(imageRenderer->Render(adaptiveElementImage.Get(), renderContext, childRenderArgs.Get(), &uiImage));*/
                    // TODO: Do I need to cast adaptiveImage to IAdaptiveCardElemenet?
                    auto uiImage = imageRenderer.Render(adaptiveImage, renderContext, childRenderArgs);

                    /*ComPtr<IFrameworkElement> imageAsFrameworkElement;
                    RETURN_IF_FAILED(uiImage.As(&imageAsFrameworkElement));

                    UINT32 maxImageHeight;
                    RETURN_IF_FAILED(imageSetConfig->get_MaxImageHeight(&maxImageHeight));
                    RETURN_IF_FAILED(imageAsFrameworkElement->put_MaxHeight(maxImageHeight));*/
                    uint32_t maxImageHeight = imageSetConfig.MaxImageHeight();

                    // TODO: is this the correct way to handle this?
                    if (uiImage != nullptr)
                    {
                        /* ComPtr<IPanel> gridAsPanel;
                         RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

                         XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());*/
                        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(uiImage, xamlGrid);
                    }
                }
            }

            /*IterateOverVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImage, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveImage>(
                images.Get(),
                [imageSize, xamlGrid, renderContext, childRenderArgs, imageRenderer, imageSetConfig](IAdaptiveImage* adaptiveImage)
                {
                    ComPtr<IUIElement> uiImage;
                    ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
                    RETURN_IF_FAILED(localAdaptiveImage->put_Size(imageSize));

                    ComPtr<IAdaptiveCardElement> adaptiveElementImage;
                    RETURN_IF_FAILED(localAdaptiveImage.As(&adaptiveElementImage));
                    RETURN_IF_FAILED(
                        imageRenderer->Render(adaptiveElementImage.Get(), renderContext, childRenderArgs.Get(), &uiImage));

                    ComPtr<IFrameworkElement> imageAsFrameworkElement;
                    RETURN_IF_FAILED(uiImage.As(&imageAsFrameworkElement));

                    UINT32 maxImageHeight;
                    RETURN_IF_FAILED(imageSetConfig->get_MaxImageHeight(&maxImageHeight));
                    RETURN_IF_FAILED(imageAsFrameworkElement->put_MaxHeight(maxImageHeight));

                    ComPtr<IPanel> gridAsPanel;
                    RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

                    XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());
                    return S_OK;
                });*/
            else
            {
                renderContext.AddWarning(rtom::WarningStatusCode::NoRendererForType, L"No renderer found for type: Image");
                return nullptr;
            }

           /* ComPtr<IFrameworkElement> imageSetAsFrameworkElement;
            RETURN_IF_FAILED(xamlGrid.As(&imageSetAsFrameworkElement));
            RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                         L"Adaptive.ImageSet",
                                                                         imageSetAsFrameworkElement.Get()));

            return xamlGrid.CopyTo(imageSetControl);*/

            // TODO: Do I need to cast xamlGrid to FrameworkElement?
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", xamlGrid);
            return xamlGrid;
            
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what should we do here?
            return nullptr;
        }
    }
