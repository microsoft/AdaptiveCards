#include "pch.h"
#include "AdaptiveElementRendererRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer {
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
        (*m_registration)[TypeAsRegistrationKey(type)] = localRenderer;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementRendererRegistration::Get(HSTRING type, IAdaptiveElementRenderer** result)
    {
        *result = nullptr;

        RegistrationMap::iterator found = m_registration->find(TypeAsRegistrationKey(type));
        if (found != m_registration->end())
        {
            *result = found->second.Get();
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementRendererRegistration::Remove(_In_ HSTRING type)
    {
        m_registration->erase(TypeAsRegistrationKey(type));
        return S_OK;
    }

    _Use_decl_annotations_
    std::string AdaptiveElementRendererRegistration::TypeAsRegistrationKey(_In_ HSTRING type)
    {
        std::string typeAsKey;
        HStringToUTF8(type, typeAsKey);
        return typeAsKey;
    }
}}
