#pragma once

#include "Util.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    template<typename T>
    class BaseRegistration
    {
        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<T>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ T* value)
        {
            ComPtr<T> localValue(value);
            (*m_registration)[TypeAsRegistrationKey(type)] = localValue;

            return S_OK;
        }

        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ T** result)
        {
            *result = nullptr;

            RegistrationMap::iterator found = m_registration->find(TypeAsRegistrationKey(type));
            if (found != m_registration->end())
            {
                *result = found->second.Get();
            }
            return S_OK;
        }

        IFACEMETHODIMP Remove(_In_ HSTRING type)
        {
            m_registration->erase(TypeAsRegistrationKey(type));
            return S_OK;
        }
        std::shared_ptr<RegistrationMap> m_registration;

    private:
        std::string TypeAsRegistrationKey(_In_ HSTRING type)
        {
            std::string typeAsKey;
            HStringToUTF8(type, typeAsKey);
            return typeAsKey;
        }

        
    };
}}