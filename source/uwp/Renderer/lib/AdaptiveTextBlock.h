#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "TextBlock.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveTextBlock :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveTextBlock,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveTextBlock, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::TextBlock>& sharedTextBlock);

        // IAdaptiveTextBlock
        IFACEMETHODIMP get_Text(_Out_ HSTRING *text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::Uwp::TextSize* textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::Uwp::TextSize textSize);

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveCards::Uwp::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::Uwp::TextWeight textWeight);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::Uwp::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::Uwp::ForegroundColor textColor);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_MaxLines(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxLines(_In_ UINT32 value);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::Uwp::HAlignment* hAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveCards::Uwp::HAlignment hAlignment);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(boolean* separator);
        IFACEMETHODIMP put_Separator(boolean separator);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

    private:
        std::shared_ptr<AdaptiveCards::TextBlock> m_sharedTextBlock;
    };

    ActivatableClass(AdaptiveTextBlock);
}}