// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveImageSetRenderer.g.cpp"
#include "AdaptiveRenderArgs.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    winrt::Windows::UI::Xaml::UIElement AdaptiveImageSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                                         rtrender::AdaptiveRenderContext const& renderContext,
                                                                         rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveImageSet = cardElement.as<rtom::AdaptiveImageSet>();

            rtxaml::Controls::VariableSizedWrapGrid xamlGrid{};
            xamlGrid.Orientation(rtxaml::Controls::Orientation::Horizontal);

            auto images = adaptiveImageSet.Images();
            auto hostConfig = renderContext.HostConfig();
            auto imageSetConfig = hostConfig.ImageSet();
            auto imageSize = adaptiveImageSet.ImageSize();

            if (imageSize == rtom::ImageSize::None)
            {
                imageSize = imageSetConfig.ImageSize();
            }

            if (const auto imageRenderer = renderContext.ElementRenderers().Get(L"Image"))
            {
                auto containerStyle = renderArgs.ContainerStyle();

                auto childRenderArgs =
                    winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, xamlGrid, renderArgs);

                for (auto adaptiveImage : images)
                {
                    adaptiveImage.Size(imageSize);

                    // TODO: Do I need to cast adaptiveImage to IAdaptiveCardElemenet?
                    auto uiImage = imageRenderer.Render(adaptiveImage, renderContext, childRenderArgs);

                    // TODO: is this the correct way to handle this?
                    if (const auto uiImageAsFrameworkElement = uiImage.try_as<rtxaml::FrameworkElement>())
                    {
                        uiImageAsFrameworkElement.MaxHeight(imageSetConfig.MaxImageHeight());
                        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(uiImageAsFrameworkElement, xamlGrid);
                    }
                }
            }
            else
            {
                renderContext.AddWarning(rtom::WarningStatusCode::NoRendererForType, L"No renderer found for type: Image");
                return nullptr;
            }

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
}
