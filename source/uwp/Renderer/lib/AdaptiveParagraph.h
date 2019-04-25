#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Paragraph.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveParagraph
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveParagraph,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveParagraph);

    public:
        AdaptiveParagraph();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Paragraph>& sharedParagraph) noexcept;

        // IAdaptiveParagraph
        IFACEMETHODIMP get_Inlines(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>** inlines);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Paragraph>& sharedModel) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>> m_inlines;
    };

    ActivatableClass(AdaptiveParagraph);
}
