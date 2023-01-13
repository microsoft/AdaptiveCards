// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveImageSetRenderer.g.cpp"
#include "AdaptiveRenderArgs.h"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveImageSetRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                      winrt::AdaptiveRenderContext const& renderContext,
                                                      winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveImageSet = cardElement.as<winrt::AdaptiveImageSet>();

            winrt::VariableSizedWrapGrid xamlGrid{};
            xamlGrid.Orientation(winrt::Orientation::Horizontal);

            auto images = adaptiveImageSet.Images();
            auto hostConfig = renderContext.HostConfig();
            auto imageSetConfig = hostConfig.ImageSet();
            auto imageSize = adaptiveImageSet.ImageSize();

            if (imageSize == winrt::ImageSize::None)
            {
                imageSize = imageSetConfig.ImageSize();
            }

            if (const auto imageRenderer = renderContext.ElementRenderers().Get(L"Image"))
            {
                auto containerStyle = renderArgs.ContainerStyle();

                auto childRenderArgs = winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, xamlGrid, renderArgs);

                for (auto adaptiveImage : images)
                {
                    adaptiveImage.Size(imageSize);

                    auto uiImage = imageRenderer.Render(adaptiveImage, renderContext, childRenderArgs);

                    if (const auto uiImageAsFrameworkElement = uiImage.try_as<winrt::FrameworkElement>())
                    {
                        uiImageAsFrameworkElement.MaxHeight(imageSetConfig.MaxImageHeight());
                        XamlHelpers::AppendXamlElementToPanel(uiImageAsFrameworkElement, xamlGrid);
                    }
                }
            }
            else
            {
                renderContext.AddWarning(winrt::WarningStatusCode::NoRendererForType, L"No renderer found for type: Image");
                return nullptr;
            }

            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", xamlGrid);
            return xamlGrid;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
