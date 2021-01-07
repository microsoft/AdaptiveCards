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
        CustomElementWrapper(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement);

        bool GetSeparator() const override;
        void SetSeparator(bool value) override;

        Spacing GetSpacing() const override;
        void SetSpacing(Spacing value) override;

        void SetId(std::string&& value) override;
        void SetId(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

        HRESULT GetWrappedElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** cardElement);

    private:
        std::string GetCardElementId() const;
        void SetCardElementId(const std::string& value);

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> m_cardElement;
    };
}
