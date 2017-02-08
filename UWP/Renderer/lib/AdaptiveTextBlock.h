#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "TextBlock.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveTextBlock :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::FtmBase,
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

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);
        IFACEMETHODIMP put_ElementType(_In_ ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType);

        IFACEMETHODIMP Render(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** TextBlock);

    private:
        std::unique_ptr<AdaptiveCards::TextBlock> m_TextBlock;
    };

    ActivatableClass(AdaptiveTextBlock);
}}