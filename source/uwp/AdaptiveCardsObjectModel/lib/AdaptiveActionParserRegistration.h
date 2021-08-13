// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.Uwp.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    constexpr char* c_upwActionParserRegistration = "AB3CC8B0-FF27-4859-A2AA-BCE2E729805";

    class DECLSPEC_UUID("fc95029a-9ec0-4d93-b170-09c99876db20") AdaptiveActionParserRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveActionParserRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::ActionParserRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveActionParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser* Parser) noexcept;
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser** result) noexcept;
        IFACEMETHODIMP Remove(_In_ HSTRING type) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<ActionParserRegistration> GetSharedParserRegistration();

    private:
        HRESULT RegisterDefaultActionParsers(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* registration);

        bool m_isInitializing;
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ActionParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveActionParserRegistration);

    class SharedModelActionParser : public AdaptiveCards::ActionElementParser
    {
    public:
        SharedModelActionParser(_In_ AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration* parserRegistration);

        // AdaptiveCards::ActionElementParser
        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

        HRESULT GetAdaptiveParserRegistration(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration** actionParserRegistration);

    private:
        // This a a weak reference to the UWP level AdaptiveActionParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelActionParser(This Object)->
        //      m_parserRegistration(AdaptiveActionParserRegistration)->
        //          m_sharedParserRegistration(ActionParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        Microsoft::WRL::WeakRef m_parserRegistration;
    };
}
