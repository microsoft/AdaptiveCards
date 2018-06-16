#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "TextBlock.h"
#include "AdaptiveCardElement.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveRemoteResourceInformation :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveRemoteResourceInformation>
    {
        AdaptiveRuntime(AdaptiveRemoteResourceInformation)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(RemoteResourceInformation& uriInformation);

        // IAdaptiveRemoteResourceInformation
        IFACEMETHODIMP get_Url(_Out_ HSTRING *url);
        IFACEMETHODIMP put_Url(_In_ HSTRING url);

        IFACEMETHODIMP get_ResourceType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);
        IFACEMETHODIMP put_ResourceType(ABI::AdaptiveNamespace::ElementType elementType);

        IFACEMETHODIMP get_MimeType(_Out_ HSTRING *text);
        IFACEMETHODIMP put_MimeType(_In_ HSTRING text);

    private:
        Microsoft::WRL::Wrappers::HString m_url;
        Microsoft::WRL::Wrappers::HString m_mimeType;
        ABI::AdaptiveNamespace::ElementType m_urlType;
    };

    ActivatableClass(AdaptiveRemoteResourceInformation);
AdaptiveNamespaceEnd