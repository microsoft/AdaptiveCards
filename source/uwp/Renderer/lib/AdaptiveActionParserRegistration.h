// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("fc95029a-9ec0-4d93-b170-09c99876db20") AdaptiveActionParserRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveActionParserRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveActionParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveNamespace::IAdaptiveActionParser* Parser) noexcept;
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionParser** result) noexcept;
        IFACEMETHODIMP Remove(_In_ HSTRING type) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<ActionParserRegistration> GetSharedParserRegistration();

    private:
        bool m_isInitializing;
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ActionParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveActionParserRegistration);

    class SharedModelActionParser : public AdaptiveSharedNamespace::ActionElementParser
    {
    public:
        SharedModelActionParser(_In_ AdaptiveNamespace::AdaptiveActionParserRegistration* parserRegistration) :
            m_parserRegistration(parserRegistration)
        {
        }

        // AdaptiveSharedNamespace::ActionElementParser
        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveActionParserRegistration> m_parserRegistration;
    };
}
