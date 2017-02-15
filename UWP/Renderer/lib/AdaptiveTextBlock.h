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
        AdaptiveTextBlock();

        // IAdaptiveTextBlock
        IFACEMETHODIMP get_Text(HSTRING *text);
        IFACEMETHODIMP put_Text(HSTRING text);

        IFACEMETHODIMP get_TextSize(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize);
        IFACEMETHODIMP put_TextSize(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize);

        IFACEMETHODIMP get_TextWeight(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight);
        IFACEMETHODIMP put_TextWeight(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight);

        IFACEMETHODIMP get_TextColor(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextColor* textColor);
        IFACEMETHODIMP put_TextColor(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextColor textColor);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);
        IFACEMETHODIMP put_ElementType(_In_ ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size);

    private:
        std::unique_ptr<AdaptiveCards::TextBlock> m_TextBlock;
    };

    ActivatableClass(AdaptiveTextBlock);
}}