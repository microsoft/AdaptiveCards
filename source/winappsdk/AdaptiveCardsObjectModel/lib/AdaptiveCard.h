// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SharedAdaptiveCard.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveRefresh.h"
#include "AdaptiveAuthentication.h"
#include "AdaptiveRemoteResourceInformation.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class DECLSPEC_UUID("ADF7ECAB-1405-4E42-83B0-ECEFFE7CE728") AdaptiveCard
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveCard);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedAdaptiveCard);

        // IAdaptiveCard
        IFACEMETHODIMP get_InternalId(_Out_ UINT32* id) override;

        IFACEMETHODIMP get_Version(_Outptr_ HSTRING* version) override;
        IFACEMETHODIMP put_Version(_In_ HSTRING version) override;

        IFACEMETHODIMP get_FallbackText(_Outptr_ HSTRING* fallbackText) override;
        IFACEMETHODIMP put_FallbackText(_In_ HSTRING fallbackText) override;

        IFACEMETHODIMP get_BackgroundImage(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveBackgroundImage** backgroundImage) override;
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveBackgroundImage* backgroundImage) override;

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language) override;
        IFACEMETHODIMP put_Language(_In_ HSTRING language) override;

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement** action) override;
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action) override;

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle* style) override;
        IFACEMETHODIMP put_Style(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style) override;

        IFACEMETHODIMP get_Speak(_Outptr_ HSTRING* speak) override;
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak) override;

        IFACEMETHODIMP get_VerticalContentAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment* verticalAlignment) override;
        IFACEMETHODIMP put_VerticalContentAlignment(ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalAlignment) override;

        IFACEMETHODIMP get_Body(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement*>** body) override;

        IFACEMETHODIMP get_Actions(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement*>** actions) override;

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType* elementType) override;

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType* heightType) override;
        IFACEMETHODIMP put_Height(ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType heightType) override;

        IFACEMETHODIMP get_MinHeight(_Out_ UINT32* minHeight) override;
        IFACEMETHODIMP put_MinHeight(UINT32 minHeight) override;

        IFACEMETHODIMP get_Refresh(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveRefresh** refresh) override;
        IFACEMETHODIMP put_Refresh(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveRefresh* refresh) override;

        IFACEMETHODIMP get_Authentication(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveAuthentication** authentication) override;
        IFACEMETHODIMP put_Authentication(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveAuthentication* authentication) override;

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override;

        IFACEMETHODIMP GetResourceInformation(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVectorView<
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRemoteResourceInformation*>** uris) override;

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::AdaptiveCard>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement*>> m_actions;

        Microsoft::WRL::Wrappers::HString m_version;
        Microsoft::WRL::Wrappers::HString m_minVersion;
        Microsoft::WRL::Wrappers::HString m_fallbackText;
        Microsoft::WRL::Wrappers::HString m_speak;
        ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType m_height;
        Microsoft::WRL::Wrappers::HString m_language;
        UINT32 m_minHeight;

        UINT32 m_internalId;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveBackgroundImage> m_backgroundImage;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> m_selectAction;
        ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle m_style;
        ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment m_verticalAlignment;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRefresh m_refresh;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveAuthentication m_authentication;
    };

    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveCard);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonWithParserRegistration(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParserRegistration,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonString(_In_ HSTRING adaptiveJson,
                                      _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonStringWithParserRegistration(
            _In_ HSTRING adaptiveJson,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParserRegistration,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult** parseResult) noexcept;

    private:
        HRESULT _FromJsonString(const std::string& jsonString,
                                _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParserRegistration,
                                _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParserRegistration,
                                _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult** parseResult);
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
}
