// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinUI3.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    constexpr char* c_upwActionParserRegistration = "AB3CC8B0-FF27-4859-A2AA-BCE2E729805";

    class DECLSPEC_UUID("fc95029a-9ec0-4d93-b170-09c99876db20") AdaptiveActionParserRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveActionParserRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::ActionParserRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveActionParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParser* Parser) noexcept;
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParser** result) noexcept;
        IFACEMETHODIMP Remove(_In_ HSTRING type) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<ActionParserRegistration> GetSharedParserRegistration();

    private:
        HRESULT RegisterDefaultActionParsers(ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* registration);

        bool m_isInitializing;
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ActionParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveActionParserRegistration);

    class SharedModelActionParser : public AdaptiveCards::ActionElementParser
    {
    public:
        SharedModelActionParser(_In_ AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration* parserRegistration);

        // AdaptiveCards::ActionElementParser
        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration GetAdaptiveParserRegistration();

    private:
        // This a a weak reference to the UWP level AdaptiveActionParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelActionParser(This Object)->
        //      m_parserRegistration(AdaptiveActionParserRegistration)->
        //          m_sharedParserRegistration(ActionParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        winrt::weak_ref<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration> m_parserRegistration;
    };
}
