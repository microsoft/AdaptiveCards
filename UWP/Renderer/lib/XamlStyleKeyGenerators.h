#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "ErrorHandling.h"

const PCWSTR c_StyleSeparator = L".";

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlStyleKeyGenerators
    {
    public:
        static std::wstring GenerateKeyForTextBlock(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlock* /*textBlock*/)
        {
            std::wstring styleKey = GetElementTypeAsString(CardElementType::TextBlock);

            // TODO: MSFT:10826544 - Programmatic xaml style generation

            return styleKey;
        }

        static std::wstring GenerateKeyForImage(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage* image)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage> adaptiveImage(image);
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));

            std::wstring styleKey = GetElementTypeAsString(CardElementType::Image);
            styleKey.append(c_StyleSeparator);
            styleKey.append(GetSizeFromCard(adaptiveCardElement.Get()).c_str());

            // TODO: MSFT:10826544 - Programmatic xaml style generation

            return styleKey;
        }

    private:
        static std::wstring GetElementTypeAsString(_In_ AdaptiveCards::CardElementType elementType)
        {
            std::string elementTypeString = AdaptiveCards::CardElementTypeToString(elementType);
            std::wstring elementTypeWideString(elementTypeString.begin(), elementTypeString.end());
            return elementTypeWideString;
        }

        static std::wstring GetSizeFromCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement)
        {
            ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size;
            THROW_IF_FAILED(adaptiveCardElement->get_Size(&size));
            std::string sizeString = AdaptiveCards::SizeToString(static_cast<AdaptiveCards::CardElementSize>(size));
            std::wstring sizeWideString(sizeString.begin(), sizeString.end());
            return sizeWideString;
        }
    };

}}