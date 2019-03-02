#include "pch.h"
#include "AdaptiveActionRendererRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    AdaptiveActionRendererRegistration::AdaptiveActionRendererRegistration() {}

    HRESULT AdaptiveActionRendererRegistration::RuntimeClassInitialize() noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionRendererRegistration::Set(_In_ HSTRING type, _In_ IAdaptiveActionRenderer* renderer)
    {
        ComPtr<IAdaptiveActionRenderer> localRenderer(renderer);
        (*m_registration)[HStringToUTF8(type)] = localRenderer;

        return S_OK;
    }

    HRESULT AdaptiveActionRendererRegistration::Get(_In_ HSTRING type, _COM_Outptr_ IAdaptiveActionRenderer** result)
    {
        *result = nullptr;
        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            found->second.CopyTo(result);
        }
        return S_OK;
    }

    HRESULT AdaptiveActionRendererRegistration::Remove(_In_ HSTRING type)
    {
        m_registration->erase(HStringToUTF8(type));
        return S_OK;
    }
}
