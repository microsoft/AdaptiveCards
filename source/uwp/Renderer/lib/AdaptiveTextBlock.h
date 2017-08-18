#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "TextBlock.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveTextBlock :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlock,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::TextBlock>& sharedTextBlock);

        // IAdaptiveTextBlock
        IFACEMETHODIMP get_Text(_Out_ HSTRING *text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize);

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor* textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor textColor);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_MaxLines(_Out_ UINT32 *value);
        IFACEMETHODIMP put_MaxLines(_In_ UINT32 value);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment* hAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment hAlignment);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING *speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

    private:
        std::shared_ptr<AdaptiveCards::TextBlock> m_sharedTextBlock;
    };

    ActivatableClass(AdaptiveTextBlock);
}}