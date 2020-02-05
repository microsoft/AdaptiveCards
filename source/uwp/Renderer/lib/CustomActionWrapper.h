// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

namespace AdaptiveNamespace
{
    class CustomActionWrapper : public AdaptiveSharedNamespace::BaseActionElement
    {
    public:
        CustomActionWrapper(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* actionElement) :
            AdaptiveSharedNamespace::BaseActionElement(AdaptiveSharedNamespace::ActionType::Custom), m_actionElement(actionElement)
        {
        }

        std::string GetId() const override;
        void SetId(const std::string& value) override;

        std::string GetTitle() const override;
        void SetTitle(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        HRESULT GetWrappedElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** actionElement);

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_actionElement;
    };
}
