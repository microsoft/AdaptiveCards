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
        CustomActionWrapper(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* actionElement);

        void SetId(std::string&& value) override;
        void SetId(const std::string& value) override;

        void SetTitle(std::string&& value) override;
        void SetTitle(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        HRESULT GetWrappedElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** actionElement);

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        std::string GetActionElementId() const;
        void SetActionElementId(const std::string& value);

        std::string GetActionElementTitle() const;
        void SetActionElementTitle(const std::string& value);

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_actionElement;
    };
}
