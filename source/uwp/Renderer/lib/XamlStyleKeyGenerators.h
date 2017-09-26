#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ErrorHandling.h"

const PCWSTR c_StyleSeparator = L".";

namespace AdaptiveCards { namespace Uwp
{
    class XamlStyleKeyGenerators
    {
    public:
        static std::wstring GenerateKeyForTextBlock(ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* textBlock)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock> adaptiveTextBlock(textBlock);
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveTextBlock.As(&adaptiveCardElement));

            std::wstring styleKey = GetElementTypeAsString(CardElementType::TextBlock);
            styleKey.append(c_StyleSeparator);
            styleKey.append(GetTextSizeFromTextBlock(adaptiveTextBlock.Get()).c_str());

            return styleKey;
        }

        static std::wstring GenerateKeyForTextBlockWeight(ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* textBlock)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock> adaptiveTextBlock(textBlock);

            std::wstring styleKey = L"TextWeight";
            styleKey.append(c_StyleSeparator);
            styleKey.append(GetTextWeightFromTextBlock(adaptiveTextBlock.Get()).c_str());

            return styleKey;
        }

        static std::wstring GenerateKeyForTextBlockColor(ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* textBlock)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock> adaptiveTextBlock(textBlock);

            std::wstring styleKey = L"TextColor";
            styleKey.append(c_StyleSeparator);
            styleKey.append(GetTextColorFromTextBlock(adaptiveTextBlock.Get()).c_str());

            return styleKey;
        }

        static std::wstring GenerateKeyForContainer(ABI::AdaptiveCards::Uwp::IAdaptiveContainer* container)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainer> adaptiveContainer(container);

            // TODO: Use GetElementTypeAsString once MSFT:11028246 is fixed
            std::wstring styleKey = L"Container";
            return styleKey;
        }

        static std::wstring GenerateKeyForImage(
            ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
            ABI::AdaptiveCards::Uwp::IAdaptiveImage* image)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveImage> adaptiveImage(image);
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));

            std::wstring styleKey = GetElementTypeAsString(CardElementType::Image);
            styleKey.append(c_StyleSeparator);

            styleKey.append(GetSizeFromImage(hostConfig, adaptiveImage.Get()).c_str());

            return styleKey;
        }

        static std::wstring GenerateKeyForColumnSet(ABI::AdaptiveCards::Uwp::IAdaptiveColumnSet* columnSet)
        {
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveColumnSet> adaptiveColumnSet(columnSet);
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveColumnSet.As(&adaptiveCardElement));

            std::wstring styleKey = GetElementTypeAsString(CardElementType::Image);
            return styleKey;
        }

    private:
        static std::wstring GetElementTypeAsString(_In_ AdaptiveCards::CardElementType elementType)
        {
            std::string elementTypeString = AdaptiveCards::CardElementTypeToString(elementType);
            std::wstring elementTypeWideString(elementTypeString.begin(), elementTypeString.end());
            return elementTypeWideString;
        }

        static std::wstring GetTextSizeFromTextBlock(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* adaptiveTextBlock)
        {
            ABI::AdaptiveCards::Uwp::TextSize textSize;
            THROW_IF_FAILED(adaptiveTextBlock->get_Size(&textSize));
            std::string sizeString = AdaptiveCards::TextSizeToString(static_cast<AdaptiveCards::TextSize>(textSize));
            std::wstring sizeWideString(sizeString.begin(), sizeString.end());
            return sizeWideString;
        }

        static std::wstring GetSizeFromImage(
            ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig, 
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveImage* adaptiveImage)
        {
            ABI::AdaptiveCards::Uwp::ImageSize size;
            THROW_IF_FAILED(adaptiveImage->get_Size(&size));
            
            if (size == ABI::AdaptiveCards::Uwp::ImageSize::None)
            {
                Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveImageConfig> imageConfig;
                THROW_IF_FAILED(hostConfig->get_Image(&imageConfig));
                THROW_IF_FAILED(imageConfig->get_ImageSize(&size));
            }

            std::string sizeString = AdaptiveCards::ImageSizeToString(static_cast<AdaptiveCards::ImageSize>(size));
            std::wstring sizeWideString(sizeString.begin(), sizeString.end());
            return sizeWideString;
        }

        static std::wstring GetTextWeightFromTextBlock(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* adaptiveTextBlock)
        {
            ABI::AdaptiveCards::Uwp::TextWeight textWeight;
            THROW_IF_FAILED(adaptiveTextBlock->get_Weight(&textWeight));
            std::string weightString = AdaptiveCards::TextWeightToString(static_cast<AdaptiveCards::TextWeight>(textWeight));
            std::wstring weightWideString(weightString.begin(), weightString.end());
            return weightWideString;
        }

        static std::wstring GetTextColorFromTextBlock(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock* adaptiveTextBlock)
        {
            ABI::AdaptiveCards::Uwp::ForegroundColor textColor;
            THROW_IF_FAILED(adaptiveTextBlock->get_Color(&textColor));
            std::string colorString = AdaptiveCards::ForegroundColorToString(static_cast<AdaptiveCards::ForegroundColor>(textColor));
            std::wstring colorWideString(colorString.begin(), colorString.end());
            return colorWideString;
        }
    };

}}