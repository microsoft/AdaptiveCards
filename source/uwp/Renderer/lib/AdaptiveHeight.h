#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Height.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("502edea9-72fd-4856-a89e-54565181bed9") AdaptiveHeight :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveHeight>,
            Microsoft::WRL::CloakedIid<ITypePeek>
    {
        AdaptiveRuntime(AdaptiveHeight);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(Height height) noexcept;

        IFACEMETHODIMP get_HeightType(_Out_ ABI::AdaptiveNamespace::HeightType* heightType);
        IFACEMETHODIMP put_HeightType(_In_ ABI::AdaptiveNamespace::HeightType heightType);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Height>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Height m_sharedHeight;
    };

    ActivatableClass(AdaptiveHeight);
AdaptiveNamespaceEnd