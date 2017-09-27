#include "pch.h"
#include "AdaptiveActionParserRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveActionParserRegistration::AdaptiveActionParserRegistration()
    {
    }

    HRESULT AdaptiveActionParserRegistration::RuntimeClassInitialize() noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveActionParserRegistration::Set(HSTRING type, IAdaptiveActionParser* Parser)
    {
        ComPtr<IAdaptiveActionParser> localParser(Parser);
        (*m_registration)[HStringToUTF8(type)] = localParser;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionParserRegistration::Get(HSTRING type, IAdaptiveActionParser** result)
    {
        *result = nullptr;

        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            *result = found->second.Get();
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionParserRegistration::Remove(_In_ HSTRING type)
    {
        m_registration->erase(HStringToUTF8(type));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionParserRegistrationStaticsImpl::GetDefault(IAdaptiveActionParserRegistration **result)
    {
        return S_OK;
    }

}}
