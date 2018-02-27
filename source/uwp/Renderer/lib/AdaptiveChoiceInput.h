#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ChoiceInput.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("7263dbfb-cb43-47f9-9022-b43372f529f9") AdaptiveChoiceInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceInput,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveChoiceInput, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ChoiceInput>& sharedChoiceInput);

        // IAdaptiveChoiceInput
        IFACEMETHODIMP get_Title(_In_ HSTRING* title);
        IFACEMETHODIMP put_Title(_Out_ HSTRING title);

        IFACEMETHODIMP get_Value(_In_ HSTRING* value);
        IFACEMETHODIMP put_Value(_Out_ HSTRING value);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ElementType* elementType);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::ChoiceInput>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        std::shared_ptr<AdaptiveCards::ChoiceInput> m_sharedChoiceInput;
    };

    ActivatableClass(AdaptiveChoiceInput);
}}}