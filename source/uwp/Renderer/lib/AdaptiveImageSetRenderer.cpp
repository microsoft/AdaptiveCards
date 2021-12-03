// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveImageSetRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageSetRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                             _In_ IAdaptiveRenderContext* renderContext,
                                             _In_ IAdaptiveRenderArgs* renderArgs,
                                             _COM_Outptr_ IUIElement** imageSetControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImageSet> adaptiveImageSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveImageSet));

        ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateABIClass<IVariableSizedWrapGrid>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

        RETURN_IF_FAILED(xamlGrid->put_Orientation(Orientation_Horizontal));

        ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveImage*>> images;
        RETURN_IF_FAILED(adaptiveImageSet->get_Images(&images));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveImageSetConfig> imageSetConfig;
        RETURN_IF_FAILED(hostConfig->get_ImageSet(&imageSetConfig));

        ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize imageSize;
        RETURN_IF_FAILED(adaptiveImageSet->get_ImageSize(&imageSize));

        if (imageSize == ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize::None)
        {
            RETURN_IF_FAILED(imageSetConfig->get_ImageSize(&imageSize));
        }

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> imageRenderer;
        RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));
        if (imageRenderer != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle;
            RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, xamlGrid.Get(), renderArgs));

            IterateOverVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveImage, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveImage>(
                images.Get(),
                [imageSize, xamlGrid, renderContext, childRenderArgs, imageRenderer, imageSetConfig](IAdaptiveImage* adaptiveImage) {
                    ComPtr<IUIElement> uiImage;
                    ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
                    RETURN_IF_FAILED(localAdaptiveImage->put_Size(imageSize));

                    ComPtr<IAdaptiveCardElement> adaptiveElementImage;
                    RETURN_IF_FAILED(localAdaptiveImage.As(&adaptiveElementImage));
                    RETURN_IF_FAILED(imageRenderer->Render(adaptiveElementImage.Get(), renderContext, childRenderArgs.Get(), &uiImage));

                    ComPtr<IFrameworkElement> imageAsFrameworkElement;
                    RETURN_IF_FAILED(uiImage.As(&imageAsFrameworkElement));

                    UINT32 maxImageHeight;
                    RETURN_IF_FAILED(imageSetConfig->get_MaxImageHeight(&maxImageHeight));
                    RETURN_IF_FAILED(imageAsFrameworkElement->put_MaxHeight(maxImageHeight));

                    ComPtr<IPanel> gridAsPanel;
                    RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

                    XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());
                    return S_OK;
                });
        }
        else
        {
            renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Image").Get());
            *imageSetControl = nullptr;
            return S_OK;
        }

        ComPtr<IFrameworkElement> imageSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&imageSetAsFrameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", imageSetAsFrameworkElement.Get()));

        return xamlGrid.CopyTo(imageSetControl);
    }
    CATCH_RETURN;
}
