#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "BaseInputElement.h"
#include "AdaptiveCardElement.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("E2E42BA6-A0AE-4B01-B161-29AF2F2B302B") AdaptiveInputElementBase : public AdaptiveCardElementBase
    {
    protected:

        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveCards::BaseInputElement>& sharedModel);

        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveCards::BaseInputElement> sharedCardElement);

    private:
        boolean m_isRequired;
    };
}}}