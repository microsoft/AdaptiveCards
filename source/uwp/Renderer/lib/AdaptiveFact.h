#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Fact.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveFact :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveFact,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveFact)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Fact>& sharedFact);

        // IAdaptiveFact
        IFACEMETHODIMP get_Title(_In_ HSTRING* title);
        IFACEMETHODIMP put_Title(_Out_ HSTRING title);

        IFACEMETHODIMP get_Value(_In_ HSTRING* value);
        IFACEMETHODIMP put_Value(_Out_ HSTRING value);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Fact>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        std::shared_ptr<AdaptiveSharedNamespace::Fact> m_sharedFact;
    };

    ActivatableClass(AdaptiveFact);
AdaptiveNamespaceEnd