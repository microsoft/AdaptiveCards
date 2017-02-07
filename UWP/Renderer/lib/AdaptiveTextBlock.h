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
            ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::IAdaptiveTextBlock>
    {
        InspectableClass(L"AdaptiveCards.AdaptiveTextBlock", BaseTrust)

    public:
        AdaptiveTextBlock();

        IFACEMETHODIMP get_Text(HSTRING *text);
        IFACEMETHODIMP put_Text(HSTRING text);

        IFACEMETHODIMP get_TextSize(ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextSize* textSize);
        IFACEMETHODIMP put_TextSize(ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextSize textSize);

        IFACEMETHODIMP get_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextWeight* textWeight);
        IFACEMETHODIMP put_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextWeight textWeight);

        IFACEMETHODIMP get_Wrap(boolean* wrap);
        IFACEMETHODIMP put_Wrap(boolean wrap);

        IFACEMETHODIMP get_IsSubtle(boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle);

        IFACEMETHODIMP Render(ABI::Windows::UI::Xaml::IUIElement** TextBlock);

    private:
        std::unique_ptr<TextBlock> m_TextBlock;
    };

    ActivatableClass(AdaptiveTextBlock);
}
}