#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"
#include "AdaptiveActionParserRegistration.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("fdf8457d-639f-4bbd-9e32-26c14bac3813") AdaptiveElementParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration>,
        Microsoft::WRL::CloakedIid<ITypePeek>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveElementParserRegistration, BaseTrust)

            typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::ElementParserRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveElementParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

        std::shared_ptr<ElementParserRegistration> GetSharedParserRegistration();

    private:
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ElementParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveElementParserRegistration);

    class SharedModelElementParser : public AdaptiveCards::BaseCardElementParser
    {
    public:
        SharedModelElementParser(AdaptiveCards::Rendering::Uwp::AdaptiveElementParserRegistration* parserRegistration) :
            m_parserRegistration(parserRegistration)
        {}

        // IBaseCardElementParser
        std::shared_ptr<BaseCardElement> Deserialize(
            std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value);

    private:
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveElementParserRegistration> m_parserRegistration;
    };

    template<
        typename TAdaptiveCardElement,
        typename TSharedModelElement,
        typename TSharedModelParser>
        HRESULT FromJson(
            ABI::Windows::Data::Json::IJsonObject* jsonObject,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element)
    {
        std::string jsonString;
        JsonObjectToString(jsonObject, jsonString);

        std::shared_ptr<AdaptiveCards::ElementParserRegistration> sharedModelElementParserRegistration;
        ComPtr<AdaptiveElementParserRegistration> elementParserRegistrationImpl = PeekInnards<AdaptiveElementParserRegistration>(elementParserRegistration);
        if (elementParserRegistrationImpl != nullptr)
        {
            sharedModelElementParserRegistration = elementParserRegistrationImpl->GetSharedParserRegistration();
        }
        else
        {
            sharedModelElementParserRegistration = std::make_shared<AdaptiveCards::ElementParserRegistration>();
        }

        std::shared_ptr<AdaptiveCards::ActionParserRegistration> sharedModelActionParserRegistration;
        ComPtr<AdaptiveActionParserRegistration> actionParserRegistrationImpl = PeekInnards<AdaptiveActionParserRegistration>(actionParserRegistration);
        if (actionParserRegistrationImpl != nullptr)
        {
            sharedModelActionParserRegistration = actionParserRegistrationImpl->GetSharedParserRegistration();
        }
        else
        {
            sharedModelActionParserRegistration = std::make_shared<AdaptiveCards::ActionParserRegistration>();
        }

        std::shared_ptr<TSharedModelParser> parser = std::make_shared<TSharedModelParser>();
        std::shared_ptr<BaseCardElement> baseCardElement = parser->DeserializeFromString(sharedModelElementParserRegistration, sharedModelActionParserRegistration, jsonString);

        THROW_IF_FAILED(MakeAndInitialize<TAdaptiveCardElement>(element, std::dynamic_pointer_cast<TSharedModelElement>(baseCardElement)));

        return S_OK;
    }
}}}
