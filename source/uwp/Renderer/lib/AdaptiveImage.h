#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Image.h"
#include <windows.foundation.h>

AdaptiveNamespaceStart
    class DECLSPEC_UUID("c940ac19-5faa-47f3-9d4b-f4d8e7d6ec1d") AdaptiveImage :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveImage,
            ABI::AdaptiveNamespace::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveImage)

    public:
        AdaptiveImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Image>& sharedImage);

        // IAdaptiveImage
        IFACEMETHODIMP get_Url(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_Url(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ImageStyle* imageStyle);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveNamespace::ImageStyle imageStyle);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::ImageSize* imageSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespace::ImageSize imageSize);

        IFACEMETHODIMP get_AltText(_Out_ HSTRING *text);
        IFACEMETHODIMP put_AltText(_In_ HSTRING text);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HAlignment* hAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveNamespace::HAlignment hAlignment);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::Image>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_url;
        ABI::AdaptiveNamespace::ImageStyle m_imageStyle;
        ABI::AdaptiveNamespace::ImageSize m_imageSize;
        Microsoft::WRL::Wrappers::HString m_altText;
        ABI::AdaptiveNamespace::HAlignment m_horizontalAlignment;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;

        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
    };

    ActivatableClass(AdaptiveImage);
AdaptiveNamespaceEnd