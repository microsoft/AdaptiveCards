#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Uwp
{
    class DECLSPEC_UUID("fc95029a-9ec0-4d93-b170-09c99876db20") AdaptiveActionParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration>,
        Microsoft::WRL::CloakedIid<ITypePeek>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveActionParserRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveActionParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

        std::shared_ptr<ActionParserRegistration> GetSharedParserRegistration();

    private:
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ActionParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveActionParserRegistration);

    class SharedModelActionParser : public AdaptiveCards::IActionElementParser
    {
    public:
        SharedModelActionParser(AdaptiveCards::Uwp::AdaptiveActionParserRegistration* parserRegistration) :
            m_parserRegistration(parserRegistration)
        {}

        // IBaseCardActionParser
        std::shared_ptr<BaseActionElement> Deserialize(
            std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value);

    private:
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::AdaptiveActionParserRegistration> m_parserRegistration;
    };
}}
