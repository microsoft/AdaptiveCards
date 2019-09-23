// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SharedAdaptiveCard.h"
#include "AdaptiveBackgroundImage.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("ADF7ECAB-1405-4E42-83B0-ECEFFE7CE728") AdaptiveCard
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveNamespace::IAdaptiveCard,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveCard);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedAdaptiveCard);

        // IAdaptiveCard
        IFACEMETHODIMP get_Version(_Outptr_ HSTRING* version);
        IFACEMETHODIMP put_Version(_In_ HSTRING version);

        IFACEMETHODIMP get_FallbackText(_Outptr_ HSTRING* fallbackText);
        IFACEMETHODIMP put_FallbackText(_In_ HSTRING fallbackText);

        IFACEMETHODIMP get_BackgroundImage(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveBackgroundImage** backgroundImage);
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::AdaptiveNamespace::IAdaptiveBackgroundImage* backgroundImage);

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language);
        IFACEMETHODIMP put_Language(_In_ HSTRING language);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style);
        IFACEMETHODIMP put_Style(ABI::AdaptiveNamespace::ContainerStyle style);

        IFACEMETHODIMP get_Speak(_Outptr_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

        IFACEMETHODIMP get_VerticalContentAlignment(_Out_ ABI::AdaptiveNamespace::VerticalContentAlignment* verticalAlignment);
        IFACEMETHODIMP put_VerticalContentAlignment(ABI::AdaptiveNamespace::VerticalContentAlignment verticalAlignment);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_Actions(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>** actions);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveNamespace::HeightType* heightType);
        IFACEMETHODIMP put_Height(ABI::AdaptiveNamespace::HeightType heightType);

        IFACEMETHODIMP get_MinHeight(_Out_ UINT32* minHeight);
        IFACEMETHODIMP put_MinHeight(UINT32 minHeight);

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);

        IFACEMETHODIMP GetResourceInformation(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVectorView<ABI::AdaptiveNamespace::AdaptiveRemoteResourceInformation*>** uris);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>> m_actions;

        Microsoft::WRL::Wrappers::HString m_version;
        Microsoft::WRL::Wrappers::HString m_minVersion;
        Microsoft::WRL::Wrappers::HString m_fallbackText;
        Microsoft::WRL::Wrappers::HString m_speak;
        ABI::AdaptiveNamespace::HeightType m_height;
        Microsoft::WRL::Wrappers::HString m_language;
        UINT32 m_minHeight;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveBackgroundImage> m_backgroundImage;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;
        ABI::AdaptiveNamespace::ContainerStyle m_style;
        ABI::AdaptiveNamespace::VerticalContentAlignment m_verticalAlignment;
    };

    class AdaptiveCardStaticsImpl WrlFinal : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveNamespace::IAdaptiveCardStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveCard);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonWithParserRegistration(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                                      _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                                                      _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                                                      _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonString(_In_ HSTRING adaptiveJson,
                                      _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonStringWithParserRegistration(
            _In_ HSTRING adaptiveJson,
            _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

    private:
        HRESULT _FromJsonString(const std::string& jsonString,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult);
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
}
