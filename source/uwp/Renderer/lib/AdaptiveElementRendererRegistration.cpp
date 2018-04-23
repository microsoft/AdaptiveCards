#include "pch.h"
#include "AdaptiveElementRendererRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

AdaptiveNamespaceStart
    AdaptiveElementRendererRegistration::AdaptiveElementRendererRegistration()
    {
    }

    HRESULT AdaptiveElementRendererRegistration::RuntimeClassInitialize() noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveElementRendererRegistration::Set(HSTRING type, IAdaptiveElementRenderer* renderer)
    {
        ComPtr<IAdaptiveElementRenderer> localRenderer(renderer);
        (*m_registration)[HStringToUTF8(type)] = localRenderer;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementRendererRegistration::Get(HSTRING type, IAdaptiveElementRenderer** result)
    {
        *result = nullptr;
        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            found->second.CopyTo(result);
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementRendererRegistration::Remove(_In_ HSTRING type)
    {
        m_registration->erase(HStringToUTF8(type));
        return S_OK;
    }
AdaptiveNamespaceEnd
