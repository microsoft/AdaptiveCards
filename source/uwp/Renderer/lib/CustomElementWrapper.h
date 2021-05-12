// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class CustomElementWrapper : public AdaptiveCards::BaseCardElement
    {
    public:
        CustomElementWrapper(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement);

        bool GetSeparator() const override;
        void SetSeparator(bool value) override;

        Spacing GetSpacing() const override;
        void SetSpacing(Spacing value) override;

        void SetId(std::string&& value) override;
        void SetId(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

        HRESULT GetWrappedElement(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** cardElement);

    private:
        std::string GetCardElementId() const;
        void SetCardElementId(const std::string& value);

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement> m_cardElement;
    };
}
