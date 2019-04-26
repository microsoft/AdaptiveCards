// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

namespace AdaptiveNamespace
{
    class CustomElementWrapper : public AdaptiveSharedNamespace::BaseCardElement
    {
    public:
        CustomElementWrapper(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement) :
            BaseCardElement(AdaptiveSharedNamespace::CardElementType::Custom), m_cardElement(cardElement)
        {
        }

        bool GetSeparator() const override;
        void SetSeparator(const bool value) override;

        Spacing GetSpacing() const override;
        void SetSpacing(const Spacing value) override;

        std::string GetId() const override;
        void SetId(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

        HRESULT GetWrappedElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** cardElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> m_cardElement;
    };
}
